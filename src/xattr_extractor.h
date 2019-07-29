#pragma once

#include <vector>
#include <string>

std::vector<std::string> getXattrNameList(const std::string& file_path);
std::string getXattrValue(const std::string& file_path, const std::string& name);
int getBalooRating(const std::string& file_path);
std::vector<std::string> getBalloTags(const std::string& file_path);
