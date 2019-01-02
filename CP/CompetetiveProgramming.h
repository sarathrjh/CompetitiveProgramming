#pragma once

#include "resource.h"
#include <string>

class CopyConstEx
{
public:
	CopyConstEx() : mVal(0), mAge(0), mName("")
	{

	}

	CopyConstEx(const CopyConstEx& copyObj)
	{
		if (&copyObj != nullptr)
		{
			mVal = copyObj.mVal;
			mAge = copyObj.mAge;
			mName = copyObj.mName;
		}
	}
private:
	int mVal;
	std::string mName;
	int mAge;
};