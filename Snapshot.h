/****************************************************
    Names       : Geoffrey Morris & Jeffrey Allen
    Date        : CS420 Spring 2014
    Assignment  : Banker's Algorithm
    Description : 
    Due Date    : November 20, 2014
*****************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Snapshot
{
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
	vector<bool> finishArray;

	//Array of int containing currently available resources (derived by taking
	//the global resourceArray and subtracting the currently allocated resources
	//represented in resourceAllocation
	int availableResources[resources]; //Resources unallocated and available

public:
	Snapshot();
	void InputFile(string file);
	void PrintState();
	bool testSafeState();
	void resourceRequest(int processIndex, int request []);
};

//##########################IMPLEMENTATION##################################################

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Writer(s): Geoffrey Morris
  Purpose  : Overloaded Constructor for minBinaryHeap
  Incoming : Desired size of new heap
  Outgoing : N/A
  Return   : N/A
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Snapshot::Snapshot() :processName(), resourceAllocation(), maxDemand(), resourceNeed(){}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Writer(s): Geoffrey Morris
  Purpose  : Automation of process input
  Incoming : Takes a string parameter of the filename
  			 Which has a list of processes, 
  			 their max demand and current resource allocation.
  Outgoing : N/A
  Return   : N/A

  ---------File format is--------

	processname
	maxA maxB maxC maxD allocA allocB allocC allocD

	Example:
	p0
	0 0 1 2 0 0 1 2
	p1
	1 7 5 0 1 0 0 0
  -------------------------------

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Writer(s): Geoffrey Morris
  Purpose  : Print to the console the three matrices as well as the available resource array
  Incoming : N/A
  Outgoing : Shows the current state of the system
  Return   : N/A
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Writer(s): Geoffrey Morris & Jeffrey Allen
  Purpose  : Tests to see if the system is safe.
  Incoming : N/A
  Outgoing : decision of whether or not state is safe
  Return   : bool
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
bool Snapshot::testSafeState()
{

	// initialize finish array
	vector<bool> finishArray(processName.size(),false);
	bool finish = false;
	bool foundGreater = false;
	bool updatedArray = true;

	// make work array
	int work [resources];

	// make the resource copy array
	for (int i=0; i<resources; i++)
		work[i] = availableResources[i];

	// step through finish, finish value here means we checked everythang
	while (finish == false && updatedArray == true)
	{
		cout << endl << "At beginning of 'finish' array" << endl;
		updatedArray = false;

		// Loop through finish array
		for (int i = 0; i<finishArray.size(); i++)
		{
			cout << "Starting process " << processName.at(i) << endl;
			// a) if the finish array at [i] is false, that means there's work to do.
			if (finishArray.at(i) == false)
			{
				finish = false;
				cout << "Process " << processName.at(i) << " is false; testing resources" << endl;
				foundGreater = false;
				// go through the resource list
				for (int j=0; j<resources; j++)
				{

					// b) check if need[i] <= work, if work exceeds the need, we found a potential deadlock
					if (!(resourceNeed[j].at(i) <= work[j]))
					{
						foundGreater = true;
						cout << "Resource " << j << " is greater than available" << endl;
						cout << "Going to next process" << endl;
						break;
					} 
					cout << "Resource " << j << " is ok" << endl;

				}
			
				// if a need did not exceed work array
				if (foundGreater == false)
				{
					cout << "Resources are all ok; running process" << endl;
					// update the "work" array: work = work + allocation
					for (int k=0; k<resources; k++)
						work[k] = work[k] + resourceAllocation[k].at(i);

					// set finish[i] == true
					finishArray[i] =  true;

					updatedArray = true;

					cout << "Process " << processName.at(i) << " is done and set to true" << endl;
					cout << "Restarting..." << endl << endl;

					break;
				}

			// otherwise, set boolean value to true
			} else {

				cout << "Process " << processName.at(i) << " is true" << endl;
				finish = true;

			}
		}

	// go back to checking finish array
	}

	if (finish == true)
		return true;

	// if unsafe
	else if (finish == false && updatedArray == false)
		return false;

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Writer(s): Geoffrey Morris & Jeffrey Allen
  Purpose  : Asks if the resource can be requested
  Incoming : a process, a vector which specifies the resources the process is requesting
  Outgoing : A decision of whether the process request is ok
  Return   : N/A
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Snapshot::resourceRequest(int processIndex, int request [])
{
	bool goAheadAndWURK;

	// Check to see if the request is valid.
	for (int k = 0; k < resources; k++){
		if (request[k] > resourceArray[k])
		{
			cout << "You're requesting more than is available in the system." << endl;
			cout << "In other words, you bit off more than you can chew." << endl;
			return;
		}
	}

	for (int i=0; i<resources; i++)
	{
		if (request[i] <= resourceNeed[i].at(processIndex))
		{
			if(request[i] <= availableResources[i])
			{
				goAheadAndWURK = true;
			}
		}
	}	

	if (goAheadAndWURK)
	{
		for (int j=0; j<resources; j++)
		{	
			availableResources[j] = availableResources[j] - request[j];
			resourceAllocation[j].at(processIndex) = resourceAllocation[j].at(processIndex) + request[j];
			resourceNeed[j].at(processIndex) = resourceNeed[j].at(processIndex) - request[j]; 
		}
	}

	if (testSafeState())
	{
		cout << endl << "We're cool." << endl << endl;

	} else {

		cout << endl << "RUN! RUN FOR YOUR LIVES! YOU'RE NOT SAFE!!!" << endl;
		cout << "This request is NOT SAFE!!!!!! Reverting back to a safe state . . ." << endl << endl;

		//undo all the changes
		for (int j=0; j<resources; j++)
		{	
			availableResources[j] = availableResources[j] + request[j];
			resourceAllocation[j].at(processIndex) = resourceAllocation[j].at(processIndex) - request[j];
			resourceNeed[j].at(processIndex) = resourceNeed[j].at(processIndex) + request[j]; 
		}
	}

}