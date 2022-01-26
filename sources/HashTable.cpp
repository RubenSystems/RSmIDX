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
			this->hashTable[hash].push_back(item);
			// if (this->hashTable.find(hash) == this->hashTable.end()) {
				
			// 	std::cout << "pushback\n";
			// } else {
			// 	this->hashTable[hash] = std::vector<std::string>({ item });
			// 	std::cout << "forward\n";
			// }
			return hash;
		}


		std::string HashTable::getHash(const Math::Matrix & input) {
			std::string hash;
			auto values = Math::dot(this->projections, input[0]);

			for(auto & i : values) {
				hash.push_back(i > 0 ? '1' : '0');
			}
			return hash;
		}
	}
}




