// Implement a program that performs encryption and decryption for the given message using Rail Fence Cipher.

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void encrypt(string PT, int row)
{
    int col = PT.size();
    vector<vector<char>> mat(row, vector<char>(col, ' '));
    string CT = "";
    int direction = -1;
    for (int r = 0, c = 0; c < col; c++, r += direction)
    {
        mat[r][c] = PT[c];
        if (r == row - 1 || r == 0)
            direction *= -1;
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (mat[i][j] != ' ')
            {
                CT.push_back(mat[i][j]);
            }
        }
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    cout << CT;
}

// Function to perform decryption
void decrypt(string CT, int row)
{
    int col = CT.size();
    vector<vector<char>> mat(row, vector<char>(col, ' '));
    string PT = "";
    int direction = -1;
    int curr = 0;

    for (int r = 0, c = 0; c < col; c++, r += direction)
    {
        mat[r][c] = '*';
        if (r == row - 1 || r == 0)
            direction *= -1;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (mat[i][j] == '*')
            {
                mat[i][j] = CT[curr];
                curr++;
            }
        }
        cout << endl;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    for (int r = 0, c = 0; c < col; c++, r += direction)
    {
        PT.push_back(mat[r][c]);
        if (r == row - 1 || r == 0)
            direction *= -1;
    }

    cout << PT;
}

int main()
{

    string PT;
    int n;
    string CT;

    int choice = 0;
    while (choice != 3)
    {
        cout << "\nMenu:\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Enter Plain Text:" << endl;
            getline(cin, PT);
            cout << "Enter Size of Rail fence:" << endl;
            cin >> n;
            encrypt(PT, n);
            break;
        case 2:
            cout << "Enter the cipher text:" << endl;
            getline(cin, CT);
            cout << "Enter size of Rail fence:" << endl;
            cin >> n;
            decrypt(CT, n);
            break;
        case 3:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    }

    return 0;
}
