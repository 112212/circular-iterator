#include "CircularIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
using std::cout;
using std::endl;
int main() {
	// std::vector<int> vec;
	std::array<int,20> vec;
	
	for(int i=0; i < 20; i++) {
		// vec.push_back(i);
		vec[i] = i;
	}

	// function is: CircularIterator<C> make_circular_iterator(C &container, int tail, int head)
	// CircularIterator<std::vector<int>> send(vec, 15, 2);
	auto circular = make_circular_iterator(vec, 15, 2);
	
	
	std::cout << "dist: " << std::distance(circular.begin(), circular.end()) << "\n";
	std::cout << "dist: " << circular.end() - circular.begin() << "\n";
	std::cout << "sort: \n";
	std::sort(circular.begin(), circular.end());
	std::cout << "------\n";
	auto itlb = std::lower_bound(circular.begin(), circular.end(), 1);
	std::cout << "[" << itlb.GetIndex() << "] " << *itlb << "\n";

	/*
	for(int &t : send) {
		// t = 0;
	}
	*/
	
	for(int t : circular) {
		cout << "iter: " << t << endl;
	}
	
	
	for(auto it = circular.begin(); it != circular.end(); it++) {
		cout << "iter2: [" << it.GetIndex() << "] " << *it << endl;
	}
	
	return 0;
}
