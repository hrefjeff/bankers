#include <iostream>
#include <vector>
using namespace std;

checkColumn(int i);

int main()
{

	vector<int> column(4);

	column[0] = 0;
	column[1] = 7;
	column[2] = 5;
	column[3] = 0;

	vector< vector <int > > row(1, column);

	for (int i = 0; i< row.size(); i++)
	{
		cout << "Process " << i << ": ";
		for(int j = 0; j<column.size(); j++)
		{
			cout << row[i][j];
		}
		cout << endl;
	}

	// check row 1, index 3
	checkColumn(1, 3);

	return 0;	
}

checkColumn(int rowIndex, int columnIndex, vector<int> * row)
{
	cout << << endl;
}