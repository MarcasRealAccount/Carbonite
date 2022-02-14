#include "Serialization.h"

namespace Utils::Serialization
{
	void Object::set(const std::string& id, const Entry& entry)
	{
		m_Entries.insert_or_assign(id, std::make_unique<Entry>(entry));
	}

	void Object::set(std::string&& id, Entry&& entry)
	{
		m_Entries.insert_or_assign(std::move(id), std::make_unique<Entry>(std::move(entry)));
	}

	Entry* Object::get(const std::string& id)
	{
		auto itr = m_Entries.find(id);
		return itr != m_Entries.end() ? itr->second.get() : nullptr;
	}

	const Entry* Object::get(const std::string& id) const
	{
		auto itr = m_Entries.find(id);
		return itr != m_Entries.end() ? itr->second.get() : nullptr;
	}

	void Array::add(const Entry& entry)
	{
		m_Entries.push_back(std::make_unique<Entry>(entry));
	}

	void Array::add(Entry&& entry)
	{
		m_Entries.push_back(std::make_unique<Entry>(std::move(entry)));
	}

	void Array::set(std::uint64_t index, const Entry& entry)
	{
		if (index >= m_Entries.size())
			m_Entries.resize(index);
		m_Entries[index] = std::make_unique<Entry>(entry);
	}

	void Array::set(std::uint64_t index, Entry&& entry)
	{
		if (index >= m_Entries.size())
			m_Entries.resize(index);
		m_Entries[index] = std::make_unique<Entry>(std::move(entry));
	}

	Entry* Array::get(std::uint64_t index)
	{
		return index < m_Entries.size() ? m_Entries[index].get() : nullptr;
	}

	const Entry* Array::get(std::uint64_t index) const
	{
		return index < m_Entries.size() ? m_Entries[index].get() : nullptr;
	}

	Entry::Entry()
	    : m_Type(EEntryType::Null), m_UInt(0ULL) {}

	Entry::Entry(const Entry& copy)
	    : m_Type(copy.m_Type), m_UInt(0ULL)
	{
		switch (m_Type)
		{
		case EEntryType::Object:
			m_Object = copy.m_Object;
			break;
		case EEntryType::Array:
			m_Array = copy.m_Array;
			break;
		case EEntryType::String:
			m_String = copy.m_String;
			break;
		case EEntryType::Int:
			m_Int = copy.m_Int;
			break;
		case EEntryType::UInt:
			m_UInt = copy.m_UInt;
			break;
		case EEntryType::Float:
			m_Float = copy.m_Float;
			break;
		default:
			break;
		}
	}

	Entry::Entry(Entry&& move)
	    : m_Type(move.m_Type), m_UInt(0ULL)
	{
		switch (m_Type)
		{
		case EEntryType::Object:
			m_Object = std::move(move.m_Object);
			break;
		case EEntryType::Array:
			m_Array = std::move(move.m_Array);
			break;
		case EEntryType::String:
			m_String = std::move(move.m_String);
			break;
		case EEntryType::Int:
			m_Int = std::move(move.m_Int);
			break;
		case EEntryType::UInt:
			m_UInt = std::move(move.m_UInt);
			break;
		case EEntryType::Float:
			m_Float = std::move(move.m_Float);
			break;
		default:
			break;
		}
		move.m_Type = EEntryType::Null;
		move.m_UInt = 0ULL;
	}

	Entry::Entry(const Object& value)
	    : m_Type(EEntryType::Object), m_Object(value) {}

	Entry::Entry(Object&& value)
	    : m_Type(EEntryType::Object), m_Object(std::move(value)) {}

	Entry::Entry(const Array& value)
	    : m_Type(EEntryType::Array), m_Array(value) {}

	Entry::Entry(Array&& value)
	    : m_Type(EEntryType::Array), m_Array(std::move(value)) {}

	Entry::Entry(const std::string& value)
	    : m_Type(EEntryType::String), m_String(value) {}

	Entry::Entry(std::string&& value)
	    : m_Type(EEntryType::String), m_String(std::move(value)) {}

	Entry::Entry(bool value)
	    : m_Type(EEntryType::Bool), m_Bool(value) {}

	Entry::Entry(std::int64_t value)
	    : m_Type(EEntryType::Int), m_Int(value) {}

	Entry::Entry(std::uint64_t value)
	    : m_Type(EEntryType::UInt), m_UInt(value) {}

	Entry::Entry(double value)
	    : m_Type(EEntryType::Float), m_Float(value) {}

	Entry::~Entry()
	{
		switch (m_Type)
		{
		case EEntryType::Object:
			m_Object.~Object();
			break;
		case EEntryType::Array:
			m_Array.~Array();
			break;
		case EEntryType::String:
			m_String.~basic_string();
			break;
		default:
			break;
		}
	}

	void Entry::set()
	{
		switch (m_Type)
		{
		case EEntryType::Object:
			m_Object.~Object();
			break;
		case EEntryType::Array:
			m_Array.~Array();
			break;
		case EEntryType::String:
			m_String.~basic_string();
			break;
		default:
			break;
		}
		m_Type = EEntryType::Null;
		m_UInt = 0ULL;
	}

	void Entry::set(const Entry& copy)
	{
		set();
		m_Type = copy.m_Type;
		switch (m_Type)
		{
		case EEntryType::Object:
			m_Object = copy.m_Object;
			break;
		case EEntryType::Array:
			m_Array = copy.m_Array;
			break;
		case EEntryType::String:
			m_String = copy.m_String;
			break;
		case EEntryType::Int:
			m_Int = copy.m_Int;
			break;
		case EEntryType::UInt:
			m_UInt = copy.m_UInt;
			break;
		case EEntryType::Float:
			m_Float = copy.m_Float;
			break;
		default:
			break;
		}
	}

	void Entry::set(Entry&& move)
	{
		set();
		m_Type = move.m_Type;
		switch (m_Type)
		{
		case EEntryType::Object:
			m_Object = std::move(move.m_Object);
			break;
		case EEntryType::Array:
			m_Array = std::move(move.m_Array);
			break;
		case EEntryType::String:
			m_String = std::move(move.m_String);
			break;
		case EEntryType::Int:
			m_Int = std::move(move.m_Int);
			break;
		case EEntryType::UInt:
			m_UInt = std::move(move.m_UInt);
			break;
		case EEntryType::Float:
			m_Float = std::move(move.m_Float);
			break;
		default:
			break;
		}
		move.m_Type = EEntryType::Null;
		move.m_UInt = 0ULL;
	}

	void Entry::set(const Object& value)
	{
		set();
		m_Type   = EEntryType::Object;
		m_Object = value;
	}

	void Entry::set(Object&& value)
	{
		set();
		m_Type   = EEntryType::Object;
		m_Object = std::move(value);
	}

	void Entry::set(const Array& value)
	{
		set();
		m_Type  = EEntryType::Array;
		m_Array = value;
	}

	void Entry::set(Array&& value)
	{
		set();
		m_Type  = EEntryType::Array;
		m_Array = std::move(value);
	}

	void Entry::set(const std::string& value)
	{
		set();
		m_Type   = EEntryType::String;
		m_String = value;
	}

	void Entry::set(std::string&& value)
	{
		set();
		m_Type   = EEntryType::String;
		m_String = std::move(value);
	}

	void Entry::set(bool value)
	{
		set();
		m_Type = EEntryType::Bool;
		m_Bool = value;
	}

	void Entry::set(std::int64_t value)
	{
		set();
		m_Type = EEntryType::Int;
		m_Int  = value;
	}

	void Entry::set(std::uint64_t value)
	{
		set();
		m_Type = EEntryType::UInt;
		m_UInt = value;
	}

	void Entry::set(double value)
	{
		set();
		m_Type  = EEntryType::Float;
		m_Float = value;
	}

	Object* Entry::getObject()
	{
		return m_Type == EEntryType::Object ? &m_Object : nullptr;
	}

	const Object* Entry::getObject() const
	{
		return m_Type == EEntryType::Object ? &m_Object : nullptr;
	}

	Array* Entry::getArray()
	{
		return m_Type == EEntryType::Array ? &m_Array : nullptr;
	}

	const Array* Entry::getArray() const
	{
		return m_Type == EEntryType::Array ? &m_Array : nullptr;
	}

	std::string_view Entry::getString() const
	{
		return m_Type == EEntryType::String ? m_String : std::string_view {};
	}

	bool Entry::getBool() const
	{
		return m_Type == EEntryType::Bool && m_Bool;
	}

	std::int64_t Entry::getInt() const
	{
		return m_Type == EEntryType::Int ? m_Int : 0;
	}

	std::uint64_t Entry::getUInt() const
	{
		return m_Type == EEntryType::UInt ? m_UInt : 0ULL;
	}

	double Entry::getFloat() const
	{
		return m_Type == EEntryType::Float ? m_Float : 0.0;
	}
} // namespace Utils::Serialization