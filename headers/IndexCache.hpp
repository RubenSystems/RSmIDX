
#include "Index.hpp"
#include <unordered_map>
#include <string>
#include <iostream>

namespace RubenSystems {
	namespace RSmIDX {
		template <class T>
		class IndexCache {
			public:
			IndexCache();
			~IndexCache();
			
			void add(const std::string & id, Index<T> * index) {
				this->cache[id] = index;
			}

			void remove(const std::string & id) {
				auto & item = this->cache[id];
				item->archive();
				//FIXME - I AM NOT CLEANING UP POINTER
				this->cache.erase(id);
			}

			Index<T> * get(const std::string & id) {
				if (this->cache.find(id) == this->cache.end()) {
					throw std::runtime_error("[ERROR] - unable to find index object in cache");
				}
				return this->cache[id];
			}


			private:
				std::unordered_map<std::string, Index<T> *> cache;
		};

		template <class T>
		IndexCache<T>::IndexCache(){}

		template <class T>
		IndexCache<T>::~IndexCache() {
			for (auto & i : (this->cache)) {
				i.second->archive();
				// delete this->cache;
				// this->cache = nullptr;
			}
		}

	}
}
	
