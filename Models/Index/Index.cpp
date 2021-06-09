//
//  Index.cpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 18/05/2021.
//

#include "Index.hpp"

#include <fstream>

#include "../../Functionality/Libraries/cereal/archives/binary.hpp"

#include "../../Functionality/Libraries/cereal/types/unordered_map.hpp"
#include "../../Functionality/Libraries/cereal/types/vector.hpp"
#include "../../Functionality/Libraries/cereal/types/memory.hpp"
#include "../../Functionality/Libraries/cereal/types/string.hpp"
#include "../../Functionality/Libraries/cereal/types/tuple.hpp"
#include "../../Functionality/Libraries/cereal/types/optional.hpp"
#include "../../Functionality/Libraries/cereal/types/queue.hpp"


#include "../../Functionality/FileHelpers/FileHelpers.hpp"

namespace RubenSystems {
	namespace RSmIDX{
	
		template <class T>
		Index<T>::Index (const IndexConfig & config) :
			config(config),
			similarityindex(std::get<0>(config.lshConfig), std::get<1>(config.lshConfig), std::get<2>(config.lshConfig)) {}

		//MARK: Direct item manipulation
		template <class T>
		T Index<T>::getItem(const std::string & id) {
			return std::get<0>(this->datastore[id]);
		}

		template <class T>
		void Index<T>::add(const T & item) {
			IndexData data = item.data();
			auto placedSlots = this->similarityindex.set(data.matrix, data.uid);
			this->datastore.emplace(data.uid, std::make_tuple(item, placedSlots));
			this->deletequeue.push(data.uid);
			
			for (auto & i : this->config.indexFields) {
				auto key = data.metadata.at(i);
				this->secondaryInvertedIndex[i][key].push_back(data.uid);
			}
			
			//check if delete queue is too big, if so delete item
			if (this->deletequeue.size > this->config.size) {
				auto first = this->deletequeue.front();
				this->deletequeue.pop();
				this->remove(first);
			}
		}

		template <class T>
		void Index<T>::remove(const std::string id) {
			if (this->datastore.find(id) != this->datastore.end()){
				auto item = this->datastore[id];
				IndexData itemData = item.data();
				this->lsh.remove(id, std::get<1>(item));
				
				for (auto & i : this->indexFields) {
					auto key = itemData.metadata.at(i);
					auto & values = this->secondaryInvertedIndex[i][key];
					auto it = std::find(values.begin(), values.end(), itemData.uid);
						// If element was found
					if (it != values.end()) {
						int index = (int)(it - values.begin());
						values.erase(values.begin() + index);
					}
				}
				this->datastore.erase(id);
			}
		}

		//MARK: Vector manipulation
		template <class T>
		std::vector<T> Index<T>::getRelated(const Math::Matrix & matrix) {
			std::vector<std::string> ids = this->lsh.get(matrix);
			std::vector<std::pair< T, double >> unorderedItems;
			std::vector<T> items;
			
			for(auto & i : ids) {
				auto item = this->datastore[i];
				IndexData itemData = item.data();
				unorderedItems.push_back(item, Math::cosineSimilarity(matrix, itemData.matrix));
			}
			
			std::sort(unorderedItems.begin(), unorderedItems.end(), [](std::pair< T, double > a, std::pair< T, double > b) -> bool{
				return  std::get<1>(a) > std::get<1>(b);
			});
			for (auto & i : unorderedItems) {
				items.push_back(i);
			}
			
			return items;
		}


		//MARK: Secondary key manipulation
		template <class T>
		std::vector<T> Index<T>::getWhere(const std::string & key, const std::string & equalTo) {
			return this->secondaryInvertedIndex[key][equalTo];
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
				this->lshIndex.populate();
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

