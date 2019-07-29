#include <iostream>
#include "xattr_extractor.h"

#include "resources.h"

int main()
{
	std::cout << "Hello World!" << std::endl;

	std::cout << "mp4: " << extension2Type["mp4"] << std::endl;
	std::cout << "mkv: " << extension2Type["mkv"] << std::endl;
	std::cout << "jpg: " << extension2Type["jpg"] << std::endl;
}
