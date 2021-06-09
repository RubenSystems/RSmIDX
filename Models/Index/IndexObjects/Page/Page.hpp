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

#include "../Indexable.h"


namespace RubenSystems {
	namespace RSmIDX {
		class Page : public Indexable {
			public:
			
				Page() = default;
			
				Page(const std::string & id, std::unordered_map<std::string, std::string> & metadata, const Math::Matrix & embedding);
			
				IndexData data() override;
			
				template <class A>
				void serialize( A & ar ) {
						ar( id, metadata, embedding );
				}

			private:
				std::string id;
				std::unordered_map<std::string, std::string> metadata;
				Math::Matrix embedding;
			

			
				
		};

	}
}


#endif /* Page_hpp */
