//
//  IndexConfig.h
//  Graphite
//
//  Created by Ruben Ticehurst-James on 19/05/2021.
//

#ifndef IndexConfig_h
#define IndexConfig_h

namespace RubenSystems {
	namespace RSmIDX {
		//MARK: Config
		struct IndexConfig {
			std::string filepath;
			int size;
			std::vector<std::string> indexFields;
			std::tuple<int, int, int> lshConfig;
			
		};
	}
}


#endif /* IndexConfig_h */
