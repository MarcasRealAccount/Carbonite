#pragma once

#include <cstdint>

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Utils::Serialization
{
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
		Object()                   = default;
		Object(const Object& copy) = default;
		Object(Object&& move)      = default;
		~Object()                  = default;

		Object& operator=(const Object& copy) = default;
		Object& operator=(Object&& move) = default;

		void set(const std::string& id, const Entry& entry);
		void set(std::string&& id, Entry&& entry);

		Entry*       get(const std::string& id);
		const Entry* get(const std::string& id) const;

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
		Array()                  = default;
		Array(const Array& copy) = default;
		Array(Array&& copy)      = default;
		~Array()                 = default;

		Array& operator=(const Array& copy) = default;
		Array& operator=(Array&& move) = default;

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
		Entry(Entry&& move);
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
		Entry& operator=(Entry&& move)
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

		explicit operator Object*() const { return getObject(); }
		explicit operator Array*() const { return getArray(); }
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

	template <class T>
	void Serialize(const T& value, Entry& entry);

	template <class T>
	void Deserialize(T& value, const Entry& entry);

	template <class T>
	Entry Serialize(const T& value)
	{
		Entry entry;
		Serialize<T>(value, entry);
		return entry;
	}

	template <class T>
	T Deserialize(const Entry& entry)
	{
		T value;
		Deserialize<T>(value, entry);
		return value;
	}
} // namespace Utils::Serialization