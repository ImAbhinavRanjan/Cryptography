// Write down a program for the encryption and decryption procedure of Row Transposition Cipher.

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

string encrypt(const string &plaintext, const string &key)
{
    int rows = (plaintext.size() + key.size() - 1) / key.size(); // Calculate rows required
    vector<vector<char>> grid(rows, vector<char>(key.size(), ' '));

    // Fill the grid with plaintext
    int k = 0;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < key.size(); ++j)
        {
            if (k < plaintext.size())
            {
                grid[i][j] = plaintext[k++];
            }
        }
    }

    // Generate key order
    vector<pair<int, int>> keyOrder;
    for (int i = 0; i < key.size(); ++i)
    {
        keyOrder.push_back({key[i] - '0', i}); // Convert key to integers
    }
    sort(keyOrder.begin(), keyOrder.end());

    // Read columns in key order to generate ciphertext
    string ciphertext;
    for (const auto &[_, col] : keyOrder)
    {
        for (int i = 0; i < rows; ++i)
        {
            ciphertext += grid[i][col];
        }
    }

    return ciphertext;
}

string decrypt(const string &ciphertext, const string &key)
{
    int rows = (ciphertext.size() + key.size() - 1) / key.size();
    vector<vector<char>> grid(rows, vector<char>(key.size(), ' '));

    // Generate key order
    vector<pair<int, int>> keyOrder;
    for (int i = 0; i < key.size(); ++i)
    {
        keyOrder.push_back({key[i] - '0', i}); // Convert key to integers
    }
    sort(keyOrder.begin(), keyOrder.end());

    // Fill the grid column-wise in key order
    int k = 0;
    for (const auto &[_, col] : keyOrder)
    {
        for (int i = 0; i < rows; ++i)
        {
            grid[i][col] = ciphertext[k++];
        }
    }

    // Read the grid row-wise to reconstruct plaintext
    string plaintext;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < key.size(); ++j)
        {
            plaintext += grid[i][j];
        }
    }

    return plaintext;
}

bool isKeyValid(const string &plaintext, const string &key)
{
    if (key.empty())
        return false;

    set<char> uniqueChars(key.begin(), key.end());
    if (uniqueChars.size() != key.size())
    {
        cout << "Key contains duplicate characters. Please enter a valid key." << endl;
        return false;
    }

    for (char ch : key)
    {
        if (!isdigit(ch))
        {
            cout << "Key must only contain numeric characters." << endl;
            return false;
        }
    }

    return true;
}

int main()
{
    int choice;
    string plaintext, key, result;

    cout << "Enter 1 for Encryption, 2 for Decryption: ";
    cin >> choice;
    cin.ignore(); // Clear input buffer

    switch (choice)
    {
    case 1:
        cout << "Enter plaintext: ";
        getline(cin, plaintext);

        do
        {
            cout << "Enter key: ";
            getline(cin, key);

            if (!isKeyValid(plaintext, key))
            {
                cout << "Invalid key. Please try again." << endl;
            }
        } while (!isKeyValid(plaintext, key));

        result = encrypt(plaintext, key);
        cout << "Encrypted text for round 1: " << result << endl;
        result = encrypt(result, key);
        cout << "Encrypted text for round 2: " << result << endl;
        break;

    case 2:
        cout << "Enter ciphertext: ";
        getline(cin, plaintext);

        do
        {
            cout << "Enter key: ";
            getline(cin, key);

            if (!isKeyValid(plaintext, key))
            {
                cout << "Invalid key. Please try again." << endl;
            }
        } while (!isKeyValid(plaintext, key));

        result = decrypt(plaintext, key);
        cout << "Decrypted text for round 1: " << result << endl;
        result = decrypt(result, key);
        cout << "Decrypted text for round 2: " << result << endl;
        break;

    default:
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
