#include "CircularBufferIndex.hpp"

#include <iostream>
using std::cout;
using std::endl;
int main() {
	CircularBufferIndex send(10);
	for(int i=0; i < 20; i++) {
		cout << "pushing: " << send.push() << endl;
	}

	for(int i=0; i < 10; i++) {
		cout << "\tpopping: " << send.pop() << endl;
	}
	for(int i=0; i < 20; i++) {
		cout << "pushing: " << send.push() << endl;
	}

	for(int t : send) {
		cout << "\titer: " << t << endl;
	}
	return 0;
}
