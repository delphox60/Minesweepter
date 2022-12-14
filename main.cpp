#include <iostream>
#include <vector>
#include <random>
#include <cstring>

using namespace std;

vector<vector<int>> board;
vector<vector<bool>> is_opened;
vector<vector<bool>> is_marked;
int r_size;
int c_size;

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

void init_board(int n_of_mines)
{
    for (int i = 0; i < r_size; i++)
    {
        for (int j = 0; j < c_size; j++)
        {
            board[i][j] = 0;
        }
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 99);

    for (int i = 0; i < n_of_mines; i++)
    {
        int random_x = dis(gen) % r_size;
        int random_y = dis(gen) % c_size;

        if (board[random_x][random_y] < 0)
        {
            continue;
        }

        board[random_x][random_y] = -1;

        for (int i = 0; i < 8; i++)
        {
            int nx = random_x + dx[i];
            int ny = random_y + dy[i];

            if (nx < 0 || nx >= r_size || ny < 0 || ny >= c_size)
            {
                continue;
            }

            if (board[nx][ny] < 0)
            {
                continue;
            }

            board[nx][ny]++;
        }
    }
}

void print_board()
{
    for (int i = 0; i < r_size; i++)
    {
        for (int j = 0; j < c_size; j++)
        {
            if (is_opened[i][j])
            {
                cout << board[i][j] << ' ';
                continue;
            }
            else if (is_marked[i][j])
            {
                cout << "V" << ' ';
                continue;
            }
            cout << "." << ' ';
        }
        cout << endl;
    }
}

void fail()
{
    for (int i = 0; i < r_size; i++)
    {
        for (int j = 0; j < c_size; j++)
        {
            if (board[i][j] < 0)
            {
                cout << "X" << ' ';
                continue;
            }
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "That block is mine." << endl;
    cout << "Game over" << endl;
}

int main()
{
    int n_of_mines;

    cout << "Please enter number of rows: ";
    cin >> r_size;

    cout << "Please enter number of columns: ";
    cin >> c_size;

    board = vector<vector<int>>(r_size, vector<int>(c_size, 0));
    is_opened = vector<vector<bool>>(r_size, vector<bool>(c_size, false));
    is_marked = vector<vector<bool>>(r_size, vector<bool>(c_size, false));

    cout << "Please enter number of mines: ";
    cin >> n_of_mines;

    init_board(n_of_mines);

    int n_of_check = 0;

    while (true)
    {
        print_board();
        cout << "# of mines remaining: " << (n_of_mines - n_of_check) << endl;

        string command;

        cout << "Enter command (o: open / m: mark): ";
        cin >> command;

        int input_x;
        int input_y;

        cin >> input_x >> input_y;

        if (command == "o")
        {
            if (board[input_x][input_y] < 0)
            {
                fail();
                break;
            }

            is_opened[input_x][input_y] = true;
            continue;
        }

        if (command == "m")
        {
            is_marked[input_x][input_y] = true;
            continue;
        }

        cout << "Invalid command. Try again." << endl;
    }
}