#pragma once

#include <string>
#include <map>
#include <vector>

class BArgItemBase;

typedef std::map<std::wstring, BArgItemBase*> TArgItemMap;

class BArgParser
{
public:
    BArgParser(int argc, _TCHAR* argv[]);
    BArgParser(int argc, _TCHAR* argv[], std::wstring helpText);
    void add(BArgItemBase* argItem);
    bool parse();
	void getTailArguments(std::vector<std::wstring>& tail);
	std::wstring help();
private:
    TArgItemMap _argItems;
	int _argc; 
	_TCHAR** _argv;
	int _lastArgIndex;
    std::vector<std::wstring> _helpFlags;
    std::vector<std::wstring> _helpDescriptions;
    int _helpFlagsLen;
	std::wstring _helpText;
};
