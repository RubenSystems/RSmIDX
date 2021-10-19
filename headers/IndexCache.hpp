
#include "Index.hpp"
#include "IndexConfig.h"
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
				
				// void add(const std::string & id, Index<T> * index) {

				// 	// this->cache.emplace(id, *index);
				// }

				void remove(const std::string & id) {
					this->cache.at(id)->archive();
				}

				void loadIndex(const std::string & id, T * index) {

					if (this->cache.find(id) == this->cache.end()) {
						// auto x = Index<T>(config);
						this->cache.emplace(id, index );
						this->cache.at(id)->unarchive();
					} 
					
					
				}

				T & get(const std::string & id) {
					if (this->cache.find(id) == this->cache.end()) {
						throw std::runtime_error("[ERROR] - unable to find index object in cache");
					}
					return *(this->cache.at(id));
				}

				bool contains(const std::string & id) {
					return (this->cache.find(id) != this->cache.end());
				}


			private:
				std::unordered_map<std::string, T * > cache;
		};

		template <class T>
		IndexCache<T>::IndexCache(){}

		template <class T>
		IndexCache<T>::~IndexCache() {}


		template <typename T>
		Index<T> * index_ptr(const IndexConfig & config) {return new Index<T>(config);} 
	}

}
	
