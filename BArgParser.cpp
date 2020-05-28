#include "stdafx.h"
#include "BArgParser.h"
#include "BArgItem.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>



BArgParser::BArgParser(int argc, _TCHAR* argv[])
{
	_argc = argc;
	_argv = argv;
	_helpFlagsLen = 0;
}

BArgParser::BArgParser(int argc, _TCHAR* argv[], std::wstring helpText)
{
	_argc = argc;
	_argv = argv;
	_helpFlagsLen = 0;
	_helpText = helpText;

}

void BArgParser::add(BArgItemBase* argItem)
{
    std::wstring shortNameKey = argItem->shortName;
    _argItems[shortNameKey] = argItem;
    std::wstring helpFlag = (argItem->hasValue? shortNameKey + L" value " : shortNameKey);
    std::wstring longNameKey = argItem->longName;
    if(!longNameKey.empty())
    {
        _argItems[longNameKey] = argItem;
        helpFlag += (argItem->hasValue ? L" " + longNameKey + L" value " : L" " + longNameKey);
    }
    _helpFlags.push_back(helpFlag);
    _helpDescriptions.push_back(argItem->description);
    _helpFlagsLen = std::max<int>(_helpFlagsLen, (int)helpFlag.length());
}

std::wstring BArgParser::help()
{
    std::wstringstream output;
	output << _helpText << std::endl;
    for(unsigned int i=0; i < _helpFlags.size(); i++)
    {
        output << std::left << std::setfill(L' ') << std::setw(_helpFlagsLen) << _helpFlags[i] << L"\t" << _helpDescriptions[i] << std::endl;
    }
    return std::wstring(output.str());
}

bool BArgParser::parse()
{
	TArgItemMap::iterator it;
	_lastArgIndex = 0;
    for(int i = 1; i<_argc; i++)
    {
		std::wstring paramName(_argv[i]);
		it = _argItems.find(paramName);
        if (it != _argItems.end())
        {
			_lastArgIndex =  std::max<int>(_lastArgIndex, i);
            (it->second)->_found = true;
            if((it->second)->hasValue)
            {
                if(++i<_argc)
                {
                    std::wstring paramValue(_argv[i]);
					if ( _argItems.find(paramValue) == _argItems.end()) // paramValue isn't equal to any other paramName
					{
	                    (it->second)->_value = paramValue;
					    _lastArgIndex =  std::max<int>(_lastArgIndex, i);
					}
	                else
		            {
			            std::wcout << "Missing value for parameter : " << paramName << std::endl;
				        return false;
					}
                }
                else
                {
                    std::wcout << "Missing value for parameter : " << paramName << std::endl;
                    return false;
                }
             }
        }
    }
    return true;
}

void BArgParser::getTailArguments(std::vector<std::wstring>& tail)
  {
    tail.clear();
    for(int i = _lastArgIndex + 1; i < _argc; i++)
    {
        tail.push_back(std::wstring(_argv[i]));
    }
  }
