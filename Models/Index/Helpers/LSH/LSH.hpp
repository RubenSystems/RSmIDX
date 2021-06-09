//
//  LSH.hpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 08/05/2021.
//

#ifndef LSH_hpp
#define LSH_hpp

#include <stdio.h>
#include "../HashTable/HashTable.hpp"
#include <mutex>


namespace RubenSystems {
	namespace RSmIDX {
		class LSH {
			public:
			
				LSH(int noTables, int hashSize, int dimensions);
				
				void populate();
			
				std::vector<std::tuple<int, std::string>> set(const Math::Matrix & embedding, const std::string & id);
			
				std::vector<std::string> get(const Math::Matrix & input);
			
				void remove(const std::string & itemId, const std::vector<std::tuple<int, std::string>> & itemLocations);
			
				template <class A>
				void serialize(A & archive) {
					archive(tables);
				}
			
			private:
				std::mutex threadGuard;
				int noTables, hashSize, dimensions;
				std::vector<HashTable> tables;

		};
	}

}


#endif /* LSH_hpp */
