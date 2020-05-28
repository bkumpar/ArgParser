// ArgParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "BArgParser.h"
#include "BArgItem.h"
#include <BUtils.h>

using namespace datetime_utils;

int _tmain(int argc, _TCHAR* argv[])
{

    BArgParser bap(argc, argv, L"usage: argparser [options] filename(s)" ) ;
    BArgItem<void> arg1(L"-h", false, L"Shows help and exit");
    bap.add(&arg1);
    BArgItem<int> arg2(L"-tsec", L"--seconds", true, L"Set time in seconds");
    bap.add(&arg2);
    BArgItem<int> arg3(L"-tm", L"--minutes", true, L"Set time in minutes");
    bap.add(&arg3);
    BArgItem<void> arg4(L"-x", L"--exit", false, L"Do nothing and exit");
    bap.add(&arg4);
    BArgItem<time_t> arg5(L"-dt", L"--datetime", true, L"Set date and time");
    bap.add(&arg5);
    if(!bap.parse())
	{
		return 0;
	}

    if(arg1.found())
	{
		std::wcout << bap.help() << std::endl;
		return 0;
	}
   if(arg2.found())
	{
		int time_s =  arg2.value();
		int time_min =  arg3.value();
        std::wcout << L"Set time to " << time_min*60+time_s << "[sec]" << std::endl;
	}

    if(arg4.found())
        std::wcout << L"Exit!" << std::endl;

    if(arg5.found())
	{
		std::wstring fmt(L"%Y-%m-%d %H:%M:%S");
		std::wcout << L"Timestamp:" <<  format(arg5.value(), fmt ) << std::endl;
	}
	std::vector<std::wstring> fileNames;
	bap.getTailArguments(fileNames);
	if(fileNames.size()>0)
	{
		std::wcout << L"File name(s):" << std::endl;
		for(size_t i=0; i<fileNames.size(); i++)
		{
			std::wcout << L"\t- " << fileNames[i] << std::endl;
		}
	}
	else
	{
		std::wcout << L"Missing file name(s)!" << std::endl;
	}
    return 0;
}

