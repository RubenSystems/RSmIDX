//
//  Indexable.h
//  Graphite
//
//  Created by Ruben Ticehurst-James on 06/06/2021.
//

#ifndef Indexable_h
#define Indexable_h

#include "IndexData.h"


namespace RubenSystems {
	namespace RSmIDX {
		class Indexable {

			virtual IndexData data() = 0;

		};
	}
}


#endif /* Indexable_h */
