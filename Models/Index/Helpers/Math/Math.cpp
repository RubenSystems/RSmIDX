//
//  Math.cpp
//  Graphite
//
//  Created by Ruben Ticehurst-James on 07/06/2021.
//

#include "Math.hpp"
#include <sstream>

namespace RubenSystems {
	namespace Math {
		Random randomGenerator;

		Random::Random (){
			this->distribution = std::uniform_real_distribution<double>(-1, 1);
		}

		double Random::generate() {
			return this->distribution(generator);
		}
	
	
		Matrix generateProjections(int columns, int rows) {
			Matrix projections;
			
			{
				for(int i = 0; i < rows; i ++) {
					std::vector<double> x;
					for(int c = 0; c < columns; c++) {
						x.push_back(randomGenerator.generate());
					}
					projections.push_back(x);
				}
			}
			
			return projections;
		}

		Matrix dot(const Matrix & a, const Matrix & b) {
			Matrix result;
			
			int newColumns = (int)a.size();
			int newRows = (int)b[0].size();
			
			result = Matrix(newColumns, std::vector<double>(newRows, 0));
			
			for(int i = 0; i < a.size(); i++) {
				for (int j = 0; j < b[0].size(); j++) {
					for (int k = 0; k < b.size(); k++) {
						result[i][j] += a[i][k] * b[k][j];
					}
				}
			}
			
			return result;
		}

		Matrix transpose(const Matrix & a) {
			Matrix transpose;
			
			transpose = Matrix(a[0].size(), std::vector<double>(a.size(), 0));
			
			for(int i = 0; i < a.size(); i++) {
				for (int c = 0; c < a[0].size(); c++){
					transpose[c][i] = a[i][c];
				}
			}
			return transpose;
		}

		Matrix vecFromString(const std::string & s) {
			auto numbers = splitString(s, ',');
			Matrix m;
			
			m.push_back(std::vector<double> ({}));
			
			for (auto & i : numbers) {
				m[0].push_back(std::stod(i));
			}
			
			return m;
		}

		std::vector<std::string> splitString (const std::string &s, char delim) {
			std::vector<std::string> result;
			std::stringstream ss (s);
			std::string item;

			while (getline (ss, item, delim)) {
				result.push_back (item);
			}

			return result;
		}

		double cosineSimilarity(const Matrix & a, const Matrix & b) {
			std::vector<double> A = a[0], B = b[0];
			double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
			for(unsigned int i = 0u; i < A.size(); ++i) {
				dot += A[i] * B[i] ;
				denom_a += A[i] * A[i] ;
				denom_b += B[i] * B[i] ;
			}
			return dot / (sqrt(denom_a) * sqrt(denom_b)) ;
		}

	}
}
