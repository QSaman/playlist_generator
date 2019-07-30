#pragma once

#include <vector>
#include <boost/filesystem.hpp>

std::vector<boost::filesystem::path> getFiles(const boost::filesystem::path& parent_dir);
