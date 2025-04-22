#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> processKey(const string &key)
{
    vector<int> shifts;
    for (char ch : key)
    {
        if (isupper(ch))
        {
            shifts.push_back(ch - 'A');
        }
        else if (islower(ch))
        {
            shifts.push_back(ch - 'a');
        }
    }
    return shifts;
}

void enc_decr(string text, int mode, string keyraw)
{
    string result = "";
    char start;
    char temp;
    int curr = 0;
    vector<int> key = processKey(keyraw);

    for (int i = 0; i < text.size(); i++)
    {
        temp = text[i];

        if (isupper(temp))
        {
            start = 'A';
            result.push_back(((temp - start + (mode == 0 ? key[curr] : -key[curr] + 26)) % 26) + start);
            curr = (curr + 1) % key.size();
        }
        else if (islower(temp))
        {
            start = 'a';
            result.push_back(((temp - start + (mode == 0 ? key[curr] : -key[curr] + 26)) % 26) + start);
            curr = (curr + 1) % key.size();
        }
        else
        {
            result.push_back(temp);
        }
    }
    cout << result << endl;
}

int main()
{
    string Text;
    int x = 1, y = 1;

    string key;

    while (y == 1)
    {
        cout << "Enter 1 for encryption" << endl;
        cout << "Enter 2 for decryption" << endl;
        cout << "Enter 3 to exit" << endl;
        cin >> x;
        cin.ignore();
        switch (x)
        {
        case 1:
            cout << "Enter Text to be encrypted:";
            getline(cin, Text);
            cout << "Enter key:";
            getline(cin, key);
            enc_decr(Text, 0, key);
            break;

        case 2:
            cout << "Enter Text to be decrypted:" << endl;
            getline(cin, Text);
            cout << "Enter key:";
            getline(cin, key);
            enc_decr(Text, 1, key);
            break;

        case 3:
            y = 0;
            cout << "Thank you!!";
            break;

        default:
            cout << "Invalid Input, Try again" << endl;
        }
    }
    return 0;
}
