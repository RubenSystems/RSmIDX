//
//  IndexData.h
//  Graphite
//
//  Created by Ruben Ticehurst-James on 06/06/2021.
//

#ifndef IndexData_h
#define IndexData_h

#include "../Helpers/Math/Math.hpp"
#include <string>
#include <unordered_map>


namespace RubenSystems {
	namespace RSmIDX {
		struct IndexData {
			std::string uid;
			std::unordered_map<std::string, std::string> metadata;
			Math::Matrix matrix;
		};
	}
}



#endif /* IndexData_h */
