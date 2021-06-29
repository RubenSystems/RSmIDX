//
//  HashTable.cpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 06/05/2021.
//

#include "../headers/HashTable.hpp"

#include <fstream>
#include <iostream>

namespace RubenSystems {
	namespace RSmIDX {
		void HashTable::generateProjections(int hashSize, int dimensions) {
			this->hashSize = hashSize;
			this->dimensions = dimensions;
			this->projections = Math::generateProjections(hashSize, dimensions);
		}

		std::vector<std::string> HashTable::get(const Math::Matrix & input) {
			auto hash = this->getHash(input);
			return this->hashTable[hash];
		}

		std::vector<std::string> & HashTable::operator[](const std::string & hash) {
			return this->hashTable[hash];
		}

		std::string HashTable::set(const Math::Matrix & input, std::string item) {
			auto hash = this->getHash(input);
			if (this->hashTable.find(hash) == this->hashTable.end()) {
				this->hashTable[hash].push_back(item);
			} else {
				this->hashTable[hash] = std::vector<std::string>({ item });
			}
			return hash;
		}


		std::string HashTable::getHash(const Math::Matrix & input) {
			std::string key;

			auto values = Math::dot(this->projections, input[0]);
			// for (int i = 0; i < values.size(); i ++) {
			// 	if (values[i] > 0) {
			// 		key += (1 << i);
			// 	}
			// }
			
			
			for(auto & i : values) {
				key.push_back(i > 0 ? '1' : '0');
			}

			return key;
		}
	}
}




