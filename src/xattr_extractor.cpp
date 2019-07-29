#include "xattr_extractor.h"
#include <sys/xattr.h>
#include <memory>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <cstdio>

#include "debug.h"

namespace
{
	std::vector<std::string> tokenize(char* c_str, const int len)
	{
		std::vector<std::string> res;
		for (int first = 0; first < len; first += res.back().length() + 1)
			res.push_back(c_str + first);
		
		return res;
	}
}


std::vector<std::string> getXattrNameList(const std::string& file_path)
{
	std::vector<std::string> res;
	auto size = llistxattr(file_path.c_str(), nullptr, 0);
	if (size == 0)
		return res;
	if (size == -1)
	{
		std::cerr << strerror(errno) << std::endl;
		std::exit(errno);
	}
	std::unique_ptr<char[]> buffer(new char[size]);
	size = llistxattr(file_path.c_str(), buffer.get(), size);
	return std::move(tokenize(buffer.get(), size));
}

std::string getXattrValue(const std::string& file_path, const std::string& name)
{
	std::string value;
	auto size = lgetxattr(file_path.c_str(), name.c_str(), nullptr , 0);
	if (size == 0)
		return value;
	if (size == -1)
	{
		if (errno == ENODATA)
			return value;
		std::cerr << strerror(errno) << std::endl;
	}
	std::unique_ptr<char[]> buffer(new char[size]);
	size = lgetxattr(file_path.c_str(), name.c_str(), buffer.get(), size);
	value = std::move(buffer.release());
	return value;
}

int getBalooRating(const std::string& file_path)
{
	auto str = getXattrValue(file_path, "user.baloo.rating");
	if (str.empty())
		return 0;
	int rating = 0;
	auto cnt = sscanf(str.c_str(), "%i", &rating);
	if (cnt !=1 || cnt == EOF)
	{
		std::cerr << "Error in parsing user.baloo.rating" << std::endl;
		std::exit(EOF);
	}
	return rating;
}

std::vector<std::string> getBalloTags(const std::string& file_path)
{
	std::vector<std::string> res;
	auto str = getXattrValue(file_path, "user.xdg.tags");
	if (str.empty())
		return res;
	const auto len = str.length();
	int cur;
	for (int first = 0; first < len; first = cur + 1)
	{
		cur = first + 1;
		for (; cur < len && str[cur] != ','; ++cur);
		res.push_back(str.substr(first, cur - first));
	}
	return res;
}
