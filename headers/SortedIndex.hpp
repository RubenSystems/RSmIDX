#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <tuple>
enum GetOperator {
	GREATER, LESS
};

class SortedIndex {
	public:
		SortedIndex(){}
		~SortedIndex(){}



		void insert(const std::string & type, const std::tuple<std::string, double> & item) {
			auto & vec = this->index[type];
			auto index = this->search(type, std::get<1>(item));
			vec.insert(vec.begin() + index, item);
		}
		

		std::vector<std::tuple<std::string, double>> get(const std::string & type, GetOperator getType, double item) {
			int index = this->search(type, item);
			auto & currentVec = this->index[type];



			switch (getType) {
				case GREATER:
					return std::vector<std::tuple<std::string, double>>(currentVec.begin() + index, currentVec.end());
				case LESS: 
					return std::vector<std::tuple<std::string, double>>(currentVec.begin(), currentVec.begin() + index);
			}
		}

		void remove(const std::string & type, const std::string & id, double value) {
			int index = this->search(type , value);
			std::cout << "-" << index << "-" << std::endl;
			for(int i = index; i >= 0; i --) {
				if (std::get<0>(this->index[type][i]) == id) {
					this->index[type].erase(this->index[type].begin() + i);
				}
			}
		} 

		template <class A>
		void serialize(A & archive) {
			archive(index);
		}

		
	
	private : 
		std::unordered_map<std::string, std::vector<std::tuple<std::string, double>>> index;


		

		int search(const std::string & type, double num) {
			int mid;
			int low = 0;
			int high = this->index[type].size() ;

			auto & arr = this->index[type];
			while (low < high) {
				mid = low + (high - low) / 2;

				if (num >= std::get<1>(arr[mid])) {
					low = mid + 1;
				} else {
					high = mid;
				}
			}

			if(low < this->index[type].size() && std::get<1>(arr[low]) <= num) {
				low++;
			}

			// Return the upper_bound index
			return low;
		}
};

