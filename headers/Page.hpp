//
//  Page.hpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 01/05/2021.
//

#ifndef Page_hpp
#define Page_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "IndexData.h"


namespace RubenSystems {
	namespace RSmIDX {
		class Page {
			public:
			
				Page() = default;
			
				Page(const std::string & id, const std::unordered_map<std::string, std::string> & metadata, const Math::Matrix & embedding);
			
				IndexData data() const;
			
				template <class A>
				void serialize( A & ar ) {
						ar( id, metadata, embedding );
				}

				std::unordered_map<std::string, std::string> & getMetadata();



			private:
				std::string id;
				std::unordered_map<std::string, std::string> metadata;
				Math::Matrix embedding;
			

			
				
		};

	}
}


#endif /* Page_hpp */
