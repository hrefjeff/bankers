#include "Globals.h"
#include "Snapshot.h"

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	bool safeState = false; //Does what it says on the tin; state is safe or unsafe
	Snapshot currentState; //Declare a snapshot object of the current system state
	int command = 0;
	string file;
	int requestVector[resources] = { 0, 4, 2, 0 }; //default request for resources

	do{
		system("cls");
		cout << "1. Take snapshot of current state" << endl;
		cout << "2. Print snapshot of current state" << endl;
		cout << "3. Test for safe state" << endl;
		cout << "4. Request resources (0,4,2,0)" << endl;
		cout << "5. Quit" << endl;
		cout << "Choose an option: ";
		cin >> command;

		switch (command){

			case 1:{
				cout << endl << "Type file name: ";
				cin >> file;
				currentState.InputFile(file); //Build the current state from an input file
				break;
			}

			case 2:{
				currentState.PrintState(); //Print the current state to the console
				system("pause");
				break;
			}

			case 3:{
				safeState = currentState.testSafeState();
				if (safeState){
					cout << endl << "State is SAFE" << endl << endl;
					system("pause");
					break;
				}
				else{
					cout << endl << "State is UNSAFE" << endl << endl;
					system("pause");
					break;
				}
			}

			case 4:{
				currentState.resourceRequest(1, requestVector);
				system("pause");
				break;
			}
		}
	}while (command != 5);

	return 0;	
}