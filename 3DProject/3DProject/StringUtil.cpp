#include "stdafx.h"
#include "StringUtil.h"


std::string GetFileNameFromPath(const std::string& filePath)
{
	int lastSlashIndex = filePath.find_last_of('/');
	if (lastSlashIndex == -1)
	{
		lastSlashIndex = filePath.find_last_of('\\');
		if (lastSlashIndex == -1)
		{
			return filePath;
		}
		else
		{
			return filePath.substr(lastSlashIndex + 1, filePath.size());
		}
	}
	else
	{
		return filePath.substr(lastSlashIndex + 1, filePath.size());
	}
}

std::string GetPathWithoutFileName(const std::string& filePath)
{
	int lastSlashIndex = filePath.find_last_of('/');
	if (lastSlashIndex == -1)
	{
		lastSlashIndex = filePath.find_last_of('\\');
		if (lastSlashIndex == -1)
		{
			return filePath;
		}
	}

	return filePath.substr(0, lastSlashIndex + 1);
}