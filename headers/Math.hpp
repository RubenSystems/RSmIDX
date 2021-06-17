//
//  Math.hpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 07/06/2021.
//

#ifndef Math_hpp
#define Math_hpp

#include <stdio.h>

#include <vector>
#include <string>
#include <random>



namespace RubenSystems {
	namespace Math {
		typedef std::vector<std::vector<double>> Matrix;

		Matrix generateProjections(int columns, int rows);

		std::vector<double> dot(const Matrix & a, const std::vector<double> & b);

		Matrix transpose(const Matrix & a);

		Matrix vecFromString(const std::string & s);

		std::vector<std::string> splitString (const std::string &s, char delim);

		double cosineSimilarity(const Matrix & a, const Matrix & b);
	
		
		class Random {
			
			public:
				Random();
			
			
				double generate();
				
			private:
				std::default_random_engine generator;
				std::uniform_real_distribution<double> distribution;
		};
	}
}

#endif /* Math_hpp */
