//
//  FileHelpers.hpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 13/05/2021.
//

#ifndef FileHelpers_hpp
#define FileHelpers_hpp

#include <stdio.h>
#include <string>

namespace FileHelpers {
	std::string strippingFilenames(const std::string forFullPath);

	bool fileExists(const std::string & filepath);

	void createDirectory(const std::string & forString);
}

#endif /* FileHelpers_hpp */
