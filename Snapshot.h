#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Snapshot{

	//String vector containing the names of each process
	vector<string> processName;

	//Arrays of int vectors containing info about resource allocation. Note that
	//number of vectors in each array = number of system resources. These arrays
	//are parallel. Example from 7.3:
	//
	//processName[0] = p0
	//resourceAllocation[resource C] at p2 = 5
	//maxDemand[resource A] at p4 = 0
	vector<int> resourceAllocation[resources]; //Resources currently allocated
	vector<int> maxDemand[resources]; //Max resources a process might demand
	vector<int> resourceNeed[resources]; //Remaining needed resources for a process

	//Array of int containing currently available resources (derived by taking
	//the global resourceArray and subtracting the currently allocated resources
	//represented in resourceAllocation
	int availableResources[resources]; //Resources unallocated and available

public:
	Snapshot();
	void InputFile(string file);
	void PrintState();
};

//Constructor
Snapshot::Snapshot() :processName(), resourceAllocation(), maxDemand(), resourceNeed(){}


//Input a list of processes, their max demand and current resource allocation.
//Takes a string parameter of the filename. File format is:
//
//processname
//demandA demandB demandC demandD allocA allocB allocC allocD
//
//Example:
//p0
//0 0 1 2 0 0 1 2
//p1
//1 7 5 0 1 0 0 0
//
//@param Geoff Morris 
void Snapshot::InputFile(string file){
	ifstream inputFile(file);
	string line;
	int alloc = 0;
	int demand = 0;
	int available = 0;

	if (inputFile.is_open()){
		while (!inputFile.eof()){
			getline(inputFile, line);
			processName.push_back(line);

			for (int i = 0; i < resources; i++){
				inputFile >> demand;
				maxDemand[i].push_back(demand);
			}

			for (int j = 0; j < resources; j++){
				inputFile >> alloc;
				resourceAllocation[j].push_back(alloc);
				resourceNeed[j].push_back(maxDemand[j].back() - resourceAllocation[j].back());
			}

			for (int k = 0; k < resources; k++){
				available = resourceArray[k];
				for (int l = 0; l < resourceAllocation[k].size(); l++){
					available = available - resourceAllocation[k].at(l);
				}
				availableResources[k] = available;
			}

			getline(inputFile, line);
		}
		inputFile.close();
	}
	else {
		cout << endl << "Unable to open file" << endl << endl;
		system("pause");
	}
}



//Print to the console the three matrices as well as the available resource array
void Snapshot::PrintState(){
	
	cout << "Max Demand matrix:" << endl;
	cout << left << setw(10) << "Name";
	for (int i = 0; i < resources; i++){
		cout << left << setw(5) << i + 1;
	}
	cout << endl;
	cout << setfill('-') << setw((resources * 5) + 9) << "-" << setfill(' ') << endl;
	for (int i = 0; i < processName.size(); i++){
		cout << left << setw(10) << processName.at(i);
		for (int j = 0; j < resources; j++){
			cout << left << setw(5) << maxDemand[j].at(i);
		}
		cout << endl;
	}

	cout << endl << "Current Allocation matrix:" << endl;
	cout << left << setw(10) << "Name";
	for (int i = 0; i < resources; i++){
		cout << left << setw(5) << i + 1;
	}
	cout << endl;
	cout << setfill('-') << setw((resources * 5) + 9) << "-" << setfill(' ') << endl;
	for (int i = 0; i < processName.size(); i++){
		cout << left << setw(10) << processName.at(i);
		for (int j = 0; j < resources; j++){
			cout << left << setw(5) << resourceAllocation[j].at(i);
		}
		cout << endl;
	}


	cout << endl << "Current Need matrix:" << endl;
	cout << left << setw(10) << "Name";
	for (int i = 0; i < resources; i++){
		cout << left << setw(5) << i + 1;
	}
	cout << endl;
	cout << setfill('-') << setw((resources * 5) + 9) << "-" << setfill(' ') << endl;
	for (int i = 0; i < processName.size(); i++){
		cout << left << setw(10) << processName.at(i);
		for (int j = 0; j < resources; j++){
			cout << left << setw(5) << resourceNeed[j].at(i);
		}
		cout << endl;
	}

	cout << endl << "Current Available Resources:" << endl;
	cout << left << setw(10) << "Name";
	for (int i = 0; i < resources; i++){
		cout << left << setw(5) << i + 1;
	}
	cout << endl;
	cout << setfill('-') << setw((resources * 5) + 9) << "-" << setfill(' ') << endl;
	cout << left << setw(10) << "Total:" ;
	for (int j = 0; j < resources; j++){
		cout << left << setw(5) << availableResources[j];
	}
	cout << endl << endl;


}