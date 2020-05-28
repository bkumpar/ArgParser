#pragma once
#include <string>
#include <ctime>
#include <BUtils.h>

class BArgParser;

class BArgItemBase
{
	friend class BArgParser;
public:
	BArgItemBase( std::wstring shortName, std::wstring longName, bool hasValue, std::wstring description)
        : shortName(shortName), longName(longName), _found(false),  hasValue(hasValue), description(description){};

	BArgItemBase( std::wstring shortName, bool hasValue, std::wstring description)
		: shortName(shortName), longName(L""), _found(false),  hasValue(hasValue), description(description){};

	bool found() 
	{
		return _found;
	};
    const std::wstring shortName;
    const std::wstring longName;
    const bool hasValue;
    const std::wstring description;
protected:
    bool _found;
	std::wstring _value;
};


template<typename T>
class BArgItem : public BArgItemBase
{
public:
	BArgItem( std::wstring shortName, std::wstring longName, bool hasValue, std::wstring description)
	: BArgItemBase(shortName, longName, hasValue, description){};

	BArgItem( std::wstring shortName, bool hasValue, std::wstring description)
	: BArgItemBase(shortName, hasValue, description){};

	T value()
	{
		T tmp;
		makeFrom(tmp, _value);
		return tmp;
	};


private:
	void makeFrom(std::wstring& value, std::wstring source)
    {
        value = source;
    };

    void makeFrom(int& value, std::wstring source)
    {
        value = std::stoi(source.c_str());
    };

	void makeFrom(time_t& value, std::wstring source)
    {
		HRESULT res = datetime_utils::parseDateTime(source, value);
    };

	void makeFrom(double& value, std::wstring source)
    {
		value = (double)_wtof(source.c_str());
    };


};
