#include <iostream>
#include <vector>
using namespace std;

void checkIndex(int, int, vector< vector<int> >&);
void checkRow(int, vector< vector<int> >&);

int main()
{

	// Example Matrix: Allocation for 7.3
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  		Col1 Col2 Col3 Col4
	//            A   B    C    D
	//Row 1 : P0  0   0    1    2
	//Row 2 : P1  1   0    0    0
	//Row 3 : P2  1   3    5    4

	vector<int> column(4);

	column[0] = 0;
	column[1] = 0;
	column[2] = 1;
	column[3] = 2;

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
	checkIndex(0, 3, row);

	checkRow(0, row);

	return 0;	
}

void checkIndex(int rowIndex, int columnIndex, vector< vector<int> > &matrix)
{
	cout << "Index (" << rowIndex << "," << columnIndex << ") contains: " << matrix[rowIndex][columnIndex] << endl;
}

void checkRow(int row, vector< vector<int> > &matrix)
{
	for (int i=0; i<matrix[row].size(); i++)
	{
		cout << "Column " << i << " contains:" << matrix[row][i] << endl;
	}
}