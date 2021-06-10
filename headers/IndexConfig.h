//
//  IndexConfig.h
//  Graphite
//
//  Created by Ruben Ticehurst-James on 19/05/2021.
//

#ifndef IndexConfig_h
#define IndexConfig_h

#include <string>
#include <tuple>
#include <vector>

namespace RubenSystems {
	namespace RSmIDX {
		//MARK: Config
		struct IndexConfig {
			IndexConfig(const std::string & filepath, int size, const std::vector<std::string> & indexFields, const std::tuple<int,int,int> & lshConfig ) :
			filepath(filepath), size(size), indexFields(indexFields), lshConfig(lshConfig) {}

			std::string filepath;
			int size;
			std::vector<std::string> indexFields;
			std::tuple<int, int, int> lshConfig;
			
		};
	}
}


#endif /* IndexConfig_h */
