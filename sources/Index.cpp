//
//  Index.cpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 18/05/2021.
//

#include "../headers/Index.hpp"

#include <fstream>
#include "../Libraries/cereal/archives/binary.hpp"

#include "../Libraries/cereal/types/unordered_map.hpp"
#include "../Libraries/cereal/types/vector.hpp"
#include "../Libraries/cereal/types/memory.hpp"
#include "../Libraries/cereal/types/string.hpp"
#include "../Libraries/cereal/types/tuple.hpp"
#include "../Libraries/cereal/types/optional.hpp"
#include "../Libraries/cereal/types/queue.hpp"
#include <iostream>

#include "../headers/FileHelpers.hpp"

namespace RubenSystems {
	namespace RSmIDX{


		// FIXME: does not yet suppourt multiple calles, will result in multiple index placements increasing redundant space. 
		template <class T>
		void Index<T>::indexData(const std::string & id, const std::unordered_map<std::string, std::string> & newData) {
			for (auto & i : this->config.indexFields) {
				if (newData.find(i.first) != newData.end()){
					auto key = newData.at(i.first);
					switch (i.second) {
						case exact:

							this->secondaryInvertedIndex[i.first][key].push_back(id);
							break;

						case sorted:
							this->sortedIndex.insert(i.first, {id, std::stod(key)});
							break; 
					}
					
				}
			}
		}

		template <class T>
		std::vector<T> Index<T>::getComparitor(const std::string & key, GetOperator getType, double item) {
			auto items = this->sortedIndex.get(key, getType, item);
			std::vector<T> results;
			for(auto & i : items) {
				results.push_back(std::get<0>(this->datastore[std::get<0>(i)]));
			}
			return results;
		}
			
	
		template <class T>
		Index<T>::Index (const IndexConfig & config) :
			config(config),
			similarityindex(std::get<0>(config.lshConfig), std::get<1>(config.lshConfig), std::get<2>(config.lshConfig)) {}

		//MARK: Direct item manipulation
		template <class T>
		T Index<T>::getItem(const std::string & id) {
			if (this->datastore.find(id) != this->datastore.end()) {
				return std::get<0>(this->datastore[id]);
			} else {
				throw std::runtime_error("[error] - item does not exist");
			}
		}

		template <class T>
		void Index<T>::add(const T & item) {
			IndexData data = item.data();
			if (this->datastore.find(data.uid) != this->datastore.end()){
				throw std::runtime_error("[log] - attempted to insert item with used uid, rehash.\n");
				return;
			}

			
			auto placedSlots = this->similarityindex.set(data.matrix, data.uid);
			this->datastore.emplace(data.uid, std::make_tuple(item, placedSlots));
			
			this->indexData(data.uid, data.metadata);
			/*for (auto & i : this->config.indexFields) {
				if (data.metadata.find(i) != data.metadata.end()){
					auto key = data.metadata.at(i);
					this->secondaryInvertedIndex[i][key].push_back(data.uid);
				}
			}*/
		}
		
		template <class T>
		void Index<T>::update(const std::string & id, const std::unordered_map<std::string, std::string> & newData) {
			for(auto & i : newData) {
				std::get<0>(this->datastore[id]).metadata[i.first] = i.second;
			}
			this->indexData(id, newData);
		}


		template <class T>
		void Index<T>::remove(const std::string id) {
			if (this->datastore.find(id) != this->datastore.end()){
				auto item = this->datastore[id];
				IndexData itemData = std::get<0>(item).data();
				this->similarityindex.remove(id, std::get<1>(item));
				
				// IndexClearup
				for (auto & i : this->config.indexFields) {
					if (itemData.metadata.find(i.first) != itemData.metadata.end()) {
						auto key = itemData.metadata.at(i.first);

						switch (i.second) {
							case exact: {
								auto & values = this->secondaryInvertedIndex[i.first][key];
									auto it = std::find(values.begin(), values.end(), itemData.uid);
										// If element was found
									if (it != values.end()) {
										int index = (int)(it - values.begin());
										values.erase(values.begin() + index);
									}
								}	

								break;
							case sorted: 
								break;
						}
					} 
					
					
				}
				this->datastore.erase(id);
			}
		}

		//MARK: Vector manipulation
		template <class T>
		std::vector<std::pair<T, double >> Index<T>::getSimilar(const Math::Matrix & matrix) {
			std::vector<std::string> ids = this->similarityindex.get(matrix);
			std::vector<std::pair< DatastoreInfo<T>, double >> unorderedItems;
			std::vector<std::pair< T, double >> items;
			

			if (ids.empty()) {
				return items;
			}

			for(auto & i : ids) {
				auto item = this->datastore[i];
				IndexData itemData = std::get<0>(item).data();
				unorderedItems.push_back({item, Math::cosineSimilarity(matrix, itemData.matrix)});
			}
			
			std::sort(unorderedItems.begin(), unorderedItems.end(), [](std::pair< DatastoreInfo<T>, double > a, std::pair< DatastoreInfo<T>, double > b) -> bool{
				return std::get<1>(a) > std::get<1>(b);
			});
			for (auto & i : unorderedItems) {
				items.push_back( {std::get<0>(std::get<0>(i)), std::get<1>(i)} );
			}
			
			return items;
		}


		//MARK: Secondary key manipulation
		template <class T>
		std::vector<T> Index<T>::getWhere(const std::string & key, const std::string & equalTo) {
			auto ids = this->secondaryInvertedIndex[key][equalTo];
			std::vector<T> objects;
			for (auto & i : ids) {
				objects.push_back(std::get<0>(this->datastore[i]));
			}
			return objects;
		}



		//MARK: archive
	
		template <class T>
		void Index<T>::unarchive() {
			auto filepath = this->config.filepath + ".gdx";
			if (FileHelpers::fileExists(filepath)) {
				std::ifstream is (filepath, std::ios::binary);
				cereal::BinaryInputArchive unarchiver(is);

				unarchiver(*this);
			} else {
				this->similarityindex.populate();
			}
			
		}

		template <class T>
		void Index<T>::archive() {
			auto filepath = this->config.filepath + ".gdx";
			if (!FileHelpers::fileExists(filepath)) {
				FileHelpers::createDirectory(filepath);
			}
			std::ofstream os (filepath, std::ios::binary);
			cereal::BinaryOutputArchive archiver(os);
			archiver(*this);
		}

	}
}

