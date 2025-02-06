// Write down a program for the encryption and decryption procedure of Caesar Cipher.

#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

void enc_decr(string text, int mode, int key)
{
    string result = "";
    char start;
    char temp;
    if (mode == 0)
    {
        for (int i = 0; i < text.size(); i++)
        {
            temp = text[i];

            if (isupper(temp))
            {
                start = 'A';
                result.push_back(((temp - start + key) % 26) + start);
            }
            else if (islower(temp))
            {
                start = 'a';
                result.push_back(((temp - start + key) % 26) + start);
            }
            else
            {
                result.push_back(temp);
            }
        }
        cout << result << endl;
    }

    else
    {
        for (int i = 0; i < text.size(); i++)
        {
            temp = text[i];

            if (isupper(temp))
            {
                start = 'A';
                result.push_back(((temp - start - key + 26) % 26) + start);
            }
            else if (islower(temp))
            {
                start = 'a';
                result.push_back(((temp - start - key + 26) % 26) + start);
            }
            else
            {
                result.push_back(temp);
            }
        }
        cout << result << endl;
    }
}

int main()
{
    string Text;
    int x = 1, y = 1;

    int key;
    while (y == 1)
    {
        cout << "Enter a key between 0 and 25:" << endl;
        cin >> key;
        if (key >= 0 && key <= 25)
            y = 2;
        else
            cout << "Invalid  Key" << endl;
    }
    y = 1;

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
            enc_decr(Text, 0, key);
            break;

        case 2:
            cout << "Enter Text to be decrypted:" << endl;
            getline(cin, Text);
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