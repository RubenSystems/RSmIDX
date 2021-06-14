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
			
			auto values = Math::dot(input, Math::transpose(this->projections));
			std::vector<bool> bools;

			for (auto & i : values[0]) {
				bools.push_back((i > 0) ? true : false);
			}



			return std::to_string(this->boolConv(bools));
		}


		int HashTable::boolConv(std::vector<bool> bools) {
			char y = 0;
			for(int i = 0; i < bools.size(); i ++) {
				if (bools[i]) {
					y += (1 << i);
				}
			}
			return y;
		}
	}
}




