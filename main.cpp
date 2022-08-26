#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int r_size;
    int c_size;

    cout << "Please enter number of rows: ";
    cin >> r_size;

    cout << "Please enter number of columns: ";
    cin >> c_size;

    vector<vector<int>> board(r_size, vector<int>(c_size));
}