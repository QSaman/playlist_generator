#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <fstream>

std::vector<std::string> fileTypes = {"video", "image", "audio"};

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage:\n" << argv[0] << " path_to_apache_mime_file path_to_embedded_cpp_file" << std::endl;
		return 1;
	}
	std::string mime_file = argv[1];
	std::string cpp_file = argv[2];

	std::ifstream fin;
    fin.exceptions(std::ifstream::badbit);
    fin.open(mime_file);
	std::ofstream fout;
	fout.exceptions(std::ofstream::badbit);
	fout.open(cpp_file);

	fout << "#include <unordered_map>\n#include<string>\n" << std::endl;
	fout << "std::unordered_map<std::string, std::string> extension2Type = {" << std::endl;
	
	std::string line;
    while (std::getline(fin, line))
    {
        if (line.empty())
            continue;
        unsigned i;
        for (i = 0; i < line.length() && std::isspace(line[i]); ++i);
        line = line.substr(i);
        if (line[0] == '#')
            continue;
		std::istringstream iss(line);
		std::string mime, extension;
        iss >> mime;
        auto pos = mime.find('/');
        if (pos == mime.npos)
		{
			std::cerr << "Cannot parse " << mime << std::endl;
			std::exit(1);
		}
		std::string type = mime.substr(0, pos);
        if (std::find(fileTypes.begin(), fileTypes.end(), type) == fileTypes.end())
	        continue;
        while (iss >> extension)
	        fout << "\t{\"" << extension << "\", \"" << type << "\"}," << std::endl;

    }
    fout << "};" << std::endl;
}
