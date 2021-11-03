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

		enum IndexType {
			exact = 0,
			sorted = 1
			
		};

		struct IndexConfig {
			IndexConfig(const std::string & filepath, const std::vector<std::pair<std::string, IndexType> > & indexFields, const std::tuple<int,int,int> & lshConfig ) :
			filepath(filepath), indexFields(indexFields), lshConfig(lshConfig) {}

			std::string filepath;
			std::vector<std::pair<std::string, IndexType> > indexFields;
			std::tuple<int, int, int> lshConfig;
			
		};

		
	}
}


#endif /* IndexConfig_h */
