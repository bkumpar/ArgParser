#include "stdafx.h"
#include "BArgItem.h"

BArgItem::BArgItem( std::wstring shortName, 
                   std::wstring longName,
                    bool hasValue, 
                    std::wstring description)
        : shortName(shortName), 
        longName(longName), 
        found(false),
        hasValue(hasValue), 
        description(description)

{

}

BArgItem::BArgItem( std::wstring shortName,
                    bool hasValue,
                    std::wstring description)
        : shortName(shortName), 
        longName(L""), 
        found(false),
        hasValue(hasValue), 
        description(description)
{


}

