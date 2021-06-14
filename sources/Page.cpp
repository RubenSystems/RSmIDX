//
//  Page.cpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 01/05/2021.
//

#include "../headers/Page.hpp"


namespace RubenSystems {
	namespace RSmIDX {
		Page::Page(const std::string & id, const std::unordered_map<std::string, std::string> & metadata, const Math::Matrix & embedding) :
			id(id),
			metadata(metadata),
			embedding(embedding) {}

		IndexData Page::data() const{
			return {id, metadata, embedding};
		}
	}
}
