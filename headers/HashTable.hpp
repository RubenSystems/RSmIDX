//
//  HashTable.hpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 06/05/2021.
//

#ifndef HashTable_hpp
#define HashTable_hpp

#include <stdio.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>


#include "Math.hpp"

namespace RubenSystems {
	namespace RSmIDX {
		class HashTable {
			
			public:
				void generateProjections(int hashSize, int dimensions);
				
				std::vector<std::string> get(const Math::Matrix & input);
			
				std::vector<std::string> & operator[] (const std::string & hash);
			
				std::string set(const Math::Matrix & input, std::string item);
			
				template <class A>
				void serialize( A & ar ) {
					ar (hashSize, dimensions, hashTable, projections);
				}
			
			private:
			
				std::string getHash(const Math::Matrix & input);
				int boolConv(std::vector<bool> bools);
			
				int hashSize;
				int dimensions;
				Math::Matrix projections;
				std::unordered_map<std::string, std::vector<std::string>> hashTable;
				
			
		};
	}
}


#endif /* HashTable_hpp */
