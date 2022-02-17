#pragma once

#include <cstdint>

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Utils::Serialization
{
	namespace Detail
	{
		template <class T>
		struct VariableInfo;

		template <class T, class C>
		struct VariableInfo<T C::*>
		{
		public:
			using Type  = T;
			using Class = C;
		};

		template <bool S, class A, class B>
		struct Selector
		{
		public:
			using Type = B;
		};

		template <class A, class B>
		struct Selector<true, A, B>
		{
		public:
			using Type = A;
		};

		template <bool S, class A, class B>
		using Select = typename Selector<S, A, B>::Type;
	} // namespace Detail

	template <class T>
	struct Serializer;

	template <class T>
	struct Deserializer;

	template <std::size_t N>
	struct VariableName
	{
	public:
		constexpr VariableName(const char* name) noexcept
		{
			for (std::size_t i = 0; i != N; ++i)
				m_Buf[i] = name[i];
		}
		constexpr operator const char*() const { return m_Buf; }

		char m_Buf[N + 1] {};
	};
	template <std::size_t N>
	VariableName(const char (&)[N]) -> VariableName<N - 1>;

	template <auto T, VariableName N>
	struct Variable
	{
	public:
		using Info    = Detail::VariableInfo<decltype(T)>;
		using Type    = typename Info::Type;
		using Class   = typename Info::Class;
		using PtrType = Type Class::*;

		using Serializer   = Serializer<Type>;
		using Deserializer = Deserializer<Type>;

		static constexpr PtrType     Ptr  = T;
		static constexpr const char* Name = N;
	};

	template <class... Vars>
	struct Variables;

	template <class Var, class... Vars>
	struct Variables<Var, Vars...>
	{
	public:
		using V    = Var;
		using Next = Variables<Vars...>;

		static constexpr std::size_t Count = 1 + sizeof...(Vars);

		template <std::size_t N>
		using Nth = Detail::Select<N == 0, V, typename Next::template Nth<N - 1>>;
	};

	template <>
	struct Variables<>
	{
	public:
		using V    = void;
		using Next = Variables<>;

		static constexpr std::size_t Count = 0;

		template <std::size_t N>
		using Nth = void;
	};

	template <class T, class... Vars>
	concept Serializable = requires
	{
		typename T::Variables;
		std::same_as<typename T::Variables, Variables<Vars...>>;
	};

	enum class EEntryType : std::uint8_t
	{
		Null = 0,
		Object,
		Array,
		String,
		Bool,
		Int,
		UInt,
		Float
	};

	struct Entry;

	struct Object
	{
	public:
		using EntryMap = std::unordered_map<std::string, std::unique_ptr<Entry>>;

	public:
		Object()                       = default;
		Object(const Object& copy)     = default;
		Object(Object&& move) noexcept = default;
		~Object()                      = default;

		Object& operator=(const Object& copy) = default;
		Object& operator=(Object&& move) noexcept = default;

		void set(const std::string& id, const Entry& entry);
		void set(std::string&& id, Entry&& entry);

		Entry*       get(const std::string& id);
		const Entry* get(const std::string& id) const;

		void reserve(std::size_t n);

		auto begin() { return m_Entries.begin(); }
		auto end() { return m_Entries.end(); }
		auto begin() const { return m_Entries.begin(); }
		auto end() const { return m_Entries.end(); }
		auto cbegin() const { return m_Entries.cbegin(); }
		auto cend() const { return m_Entries.cend(); }

	private:
		EntryMap m_Entries;
	};

	struct Array
	{
	public:
		using EntryList = std::vector<std::unique_ptr<Entry>>;

	public:
		Array()                      = default;
		Array(const Array& copy)     = default;
		Array(Array&& move) noexcept = default;
		~Array()                     = default;

		Array& operator=(const Array& copy) = default;
		Array& operator=(Array&& move) noexcept = default;

		void add(const Entry& entry);
		void add(Entry&& entry);

		void set(std::uint64_t index, const Entry& entry);
		void set(std::uint64_t index, Entry&& entry);

		Entry*       get(std::uint64_t index);
		const Entry* get(std::uint64_t index) const;

		auto begin() { return m_Entries.begin(); }
		auto end() { return m_Entries.end(); }
		auto begin() const { return m_Entries.begin(); }
		auto end() const { return m_Entries.end(); }
		auto cbegin() const { return m_Entries.cbegin(); }
		auto cend() const { return m_Entries.cend(); }
		auto rbegin() { return m_Entries.rbegin(); }
		auto rend() { return m_Entries.rend(); }
		auto rbegin() const { return m_Entries.rbegin(); }
		auto rend() const { return m_Entries.rend(); }
		auto crbegin() const { return m_Entries.crbegin(); }
		auto crend() const { return m_Entries.crend(); }

	private:
		EntryList m_Entries;
	};

	struct Entry
	{
	public:
		Entry();
		Entry(const Entry& copy);
		Entry(Entry&& move) noexcept;
		Entry(const Object& value);
		Entry(Object&& value);
		Entry(const Array& value);
		Entry(Array&& value);
		Entry(const std::string& value);
		Entry(std::string&& value);
		Entry(bool value);
		Entry(std::int64_t value);
		Entry(std::uint64_t value);
		Entry(double value);
		~Entry();

		void set();
		void set(const Entry& copy);
		void set(Entry&& move);
		void set(const Object& value);
		void set(Object&& value);
		void set(const Array& value);
		void set(Array&& value);
		void set(const std::string& value);
		void set(std::string&& value);
		void set(bool value);
		void set(std::int64_t value);
		void set(std::uint64_t value);
		void set(double value);

		Entry& operator=(const Entry& copy)
		{
			set(copy);
			return *this;
		}
		Entry& operator=(Entry&& move) noexcept
		{
			set(std::move(move));
			return *this;
		}
		Entry& operator=(const Object& value)
		{
			set(value);
			return *this;
		}
		Entry& operator=(Object&& value)
		{
			set(std::move(value));
			return *this;
		}
		Entry& operator=(const Array& value)
		{
			set(value);
			return *this;
		}
		Entry& operator=(Array&& value)
		{
			set(std::move(value));
			return *this;
		}
		Entry& operator=(const std::string& value)
		{
			set(value);
			return *this;
		}
		Entry& operator=(std::string&& value)
		{
			set(std::move(value));
			return *this;
		}
		Entry& operator=(bool value)
		{
			set(value);
			return *this;
		}
		Entry& operator=(std::int64_t value)
		{
			set(value);
			return *this;
		}
		Entry& operator=(std::uint64_t value)
		{
			set(value);
			return *this;
		}
		Entry& operator=(double value)
		{
			set(value);
			return *this;
		}

		Object*          getObject();
		const Object*    getObject() const;
		Array*           getArray();
		const Array*     getArray() const;
		std::string_view getString() const;
		bool             getBool() const;
		std::int64_t     getInt() const;
		std::uint64_t    getUInt() const;
		double           getFloat() const;

		explicit operator Object*() { return getObject(); }
		explicit operator const Object*() const { return getObject(); }
		explicit operator Array*() { return getArray(); }
		explicit operator const Array*() const { return getArray(); }
		explicit operator std::string_view() const { return getString(); }
		explicit operator bool() const { return getBool(); }
		explicit operator std::int64_t() const { return getInt(); }
		explicit operator std::uint64_t() const { return getUInt(); }
		explicit operator double() const { return getFloat(); }

	private:
		EEntryType m_Type;
		union
		{
			Object        m_Object;
			Array         m_Array;
			std::string   m_String;
			bool          m_Bool;
			std::int64_t  m_Int;
			std::uint64_t m_UInt;
			double        m_Float;
		};
	};

	template <Serializable T>
	void Serialize(const T& value, Entry& entry)
	{
		entry = Serializer<T>()(value);
	}

	template <Serializable T>
	void Deserialize(T& value, const Entry& entry)
	{
		Deserializer<T>()(value, entry);
	}

	template <Serializable T>
	Entry Serialize(const T& value)
	{
		Entry entry;
		Serialize<T>(value, entry);
		return entry;
	}

	template <Serializable T>
	T Deserialize(const Entry& entry)
	{
		T value;
		Deserialize<T>(value, entry);
		return value;
	}

	template <Serializable T>
	struct Serializer<T>
	{
	public:
		using Vars = T::Variables;

	public:
		template <class... Vs>
		Object onEachVar(const T& value, Variables<Vs...> vars)
		{
			Object obj;
			obj.reserve(sizeof...(Vs));
			(obj.set(Vs::Name, Vs::Serializer()(value.*Vs::Ptr)), ...);
			return obj;
		}

		Entry operator()(const T& value)
		{
			return Entry { onEachVar(value, Vars {}) };
		}
	};
} // namespace Utils::Serialization