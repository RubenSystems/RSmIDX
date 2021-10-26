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
#include <tuple>


namespace RubenSystems {
	namespace RSmIDX {

		//Typedefs for storage
		template <typename T>
		using DatastoreInfo = std::tuple<T, std::vector<std::tuple<int, std::string>>> ;
		using SingleInvertedIndex = std::unordered_map<std::string, std::vector<std::string>> ;
		using MultipleInvertedIndex = std::unordered_map<std::string, SingleInvertedIndex> ;

		template <class T>
		class Index {
			
			
			public:
				Index(const IndexConfig & config);
				
				//MARK: Direct item manipulation
				T getItem(const std::string & id);
			
				void add(const T & page);

				void update(const std::string & id, const std::unordered_map<std::string, std::string> & newData);
			
				void remove(const std::string id);
			
				//MARK: Vector manipulation
				std::vector<std::pair<T, double >> getSimilar(const Math::Matrix & matrix);
				
				//MARK: Secondary key manipulation
				std::vector<T> getWhere(const std::string & key, const std::string & equalTo);
				
			
				//MARK: archive
				void unarchive();
				
				void archive();
			
				template <class A>
				void serialize(A & archive){ archive(similarityindex, datastore, secondaryInvertedIndex); }
				

			private:
				
				//MARK: Config
				IndexConfig config;
			
				//MARK: Storage
				LSH similarityindex;

				//MARK: Datastore
				
				std::unordered_map<std::string, DatastoreInfo<T>> datastore;
				
				//MARK: InvertedIndex
				MultipleInvertedIndex secondaryInvertedIndex;

				void indexData(const std::string & id, const std::unordered_map<std::string, std::string> & newData);
			

				
		};
	}
}


#endif /* Index_hpp */
