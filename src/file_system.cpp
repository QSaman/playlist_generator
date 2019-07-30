#include "file_system.h"
#include <string>
#include <iostream>

std::vector<boost::filesystem::path> getFiles(const boost::filesystem::path& parent_dir)
{
	std::vector<boost::filesystem::path> res;
	if (!boost::filesystem::exists(parent_dir) && !boost::filesystem::is_directory(parent_dir))
	{
		std::cerr << parent_dir.string() << " is no a valid direcotry" << std::endl;
	}
	return res;
}
