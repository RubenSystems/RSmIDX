//
//  FileHelpers.cpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 13/05/2021.
//

#include "FileHelpers.hpp"
#include <sys/stat.h>
#include <sstream>
#include <cstring>

namespace FileHelpers {
	std::string strippingFilenames(const std::string forFullPath) {
		std::string fullDirectory = "";
		std::string word;
		std::istringstream str(forFullPath);
		while(std::getline(str, word, '/')) {
			if (word.find('.') == std::string::npos ) {
				fullDirectory += word + "/";
			}
		}
		
		if(fullDirectory[0] == '/') {
			fullDirectory = std::string(fullDirectory.begin() + 1, fullDirectory.end());
		}
		return fullDirectory;
	}


	bool fileExists(const std::string & filepath) {
		struct stat buffer;
		return (stat (filepath.c_str(), &buffer) == 0);
	}

	void createDirectory(const std::string & forString) {
		std::string fullDirectory = strippingFilenames(forString);
		if(fileExists(fullDirectory)) {
			return;
		}
		
		std::string command = "mkdir -p " + fullDirectory;
		char charArr[command.length() + 1];
		strcpy(charArr, command.c_str());
		
		std::system(charArr);
	}
}
