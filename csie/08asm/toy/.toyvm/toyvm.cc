#include <fstream>
#include <exception>
#include <iostream>

#include "Toy.h"

using namespace std;
using namespace toy;

int main(int argc, char **argv)
{
	if (argc != 2) {
		cerr << "usage: " << argv[0] << " toy-binary" << endl;
		return 1;
	}
	try {
		ifstream fin;
		fin.open(argv[1]);
		Toy<short> toy(fin);

		size_t steps = toy.run(20971520);
		cerr << steps << endl;

		// toy.dump_R();

		fin.close();
	} catch (exception &e) {
		cerr << e.what() << endl;
	}
	return 0;	
}
