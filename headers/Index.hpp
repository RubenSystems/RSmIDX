//
//  Index.hpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 18/05/2021.
//

#ifndef Index_hpp
#define Index_hpp

#include <stdio.h>


#include "IndexConfig.h"
#include "IndexData.h"
#include "LSH.hpp"

#include <unordered_map>
#include <vector>
#include <queue>


namespace RubenSystems {
	namespace RSmIDX {
		template <class T>
		class Index {
			
			
			public:
				Index(const IndexConfig & config);
				
				//MARK: Direct item manipulation
				T getItem(const std::string & id);
			
				void add(const T & page);
			
				void remove(const std::string id);
			
				//MARK: Vector manipulation
				std::vector<T> getRelated(const Math::Matrix & matrix);
				
				//MARK: Secondary key manipulation
				std::vector<T> getWhere(const std::string & key, const std::string & equalTo);
				
			
				//MARK: archive
				void unarchive();
				
				void archive();
			
				template <class A>
				void serialize(A & archive){ archive(similarityindex, datastore, deletequeue, secondaryInvertedIndex); }
				
			
			private:
				
				//MARK: Config
				IndexConfig config;
			
				//MARK: Storage
				LSH similarityindex;
				std::queue<std::string> deletequeue;

				//MARK: Datastore
				typedef std::tuple<T, std::vector<std::tuple<int, std::string>>> DatastoreInfo;
				std::unordered_map<std::string, DatastoreInfo> datastore;
				
				//MARK: InvertedIndex
				typedef std::unordered_map<std::string, std::vector<std::string>> SingleInvertedIndex;
				typedef std::unordered_map<std::string, SingleInvertedIndex> MultipleInvertedIndex;
				MultipleInvertedIndex secondaryInvertedIndex;
			
				
		};
	}
}


#endif /* Index_hpp */
