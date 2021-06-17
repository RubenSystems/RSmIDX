//
//  LSH.cpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 08/05/2021.
//

#include "../headers/LSH.hpp"
#include <fstream>
#include <unordered_set>
#include <thread>
#include <iostream>

namespace RubenSystems {
	namespace RSmIDX{
		LSH::LSH(int noTables, int hashSize, int dimensions) : noTables(noTables), hashSize(hashSize), dimensions(dimensions) { }


		void LSH::populate() {
			for(int i = 0; i < this->noTables; i++){
				HashTable x;
				x.generateProjections(hashSize, dimensions);
				this->tables.push_back(x);
			}
		}

		std::vector<std::tuple<int, std::string>> LSH::set(const Math::Matrix & embedding, const std::string & id) {
			std::lock_guard<std::mutex> lock (this->threadGuard);
			std::vector<std::tuple<int, std::string>> lookupTable;
			
			for(int i = 0; i < this->tables.size(); i ++) {
				std::string hashKey = this->tables[i].set(embedding, id);

				lookupTable.push_back(std::make_tuple(i, hashKey));
			}
			return lookupTable;
		}

		std::vector<std::string> LSH::get(const Math::Matrix & input) {
			std::lock_guard<std::mutex> lock (this->threadGuard);
			std::unordered_set<std::string> ids;
			
			for(auto & table : this->tables) {
				auto result = table.get(input);
				for (auto & id : result) {
					ids.insert(id);
				}
			}
			return std::vector(ids.begin(), ids.end());
		}


		void LSH::remove(const std::string & itemId, const std::vector<std::tuple<int, std::string>> & itemLocations) {
			std::lock_guard<std::mutex> lock (this->threadGuard);
			for (auto & location : itemLocations) {
				auto & bucket = this->tables[std::get<0>(location)][std::get<1>(location)];
				for(int i = 0; i < bucket.size(); i++) {
					if (bucket[i] == itemId) {
						bucket.erase(bucket.begin() + i);
						return;
					}
				}
			}
		}
	}
}



