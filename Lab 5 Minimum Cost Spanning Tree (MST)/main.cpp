#include <iostream>
#include "MST.h"

using namespace std;

int main() {

	MST prime;
	prime.read();

	cout << "Number of vertices is " << prime.getVertexCount() << endl;
	cout << "Number of edges is " << prime.getEdgeCount() << endl;
	cout << "The Matrix is:" << endl;
	prime.printGraph();

	cout << endl << endl;
	cout << "Begin MST 1 starting at Vertex 0" << endl;
	prime.MSTbuilder(0);

	MST dime;
	dime.read();
	cout << endl << endl;
	cout << "Begin MST 2 starting at Vertex 4" << endl;
	dime.MSTbuilder(4);

	MST lime;
	lime.read();
	cout << endl << endl;
	cout << "Begin MST 3 starting at Vertex 2" << endl;
	lime.MSTbuilder(2);


	return 0;
}
