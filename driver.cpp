#include "Globals.h"
#include "Snapshot.h"

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	Snapshot currentState;

	currentState.InputFile("test.txt");

	currentState.PrintState();

	cout << currentState.testSafeState() << endl;

	int requestVector[resources] = {0, 4, 2, 0};

	currentState.resourceRequest(1, requestVector);

	system("pause");
	return 0;	
}