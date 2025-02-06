// Write down a program for the encryption and decryption procedure of Affine Cipher.

#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int GCD(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return GCD(b, a % b);
}

int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }
    return -1;
}

void enc_decr(string text, int mode, int a, int b)
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
                result.push_back((((a * (temp - start)) + b) % 26) + start);
            }
            else if (islower(temp))
            {
                start = 'a';
                result.push_back((((a * (temp - start)) + b) % 26) + start);
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
        int inverse = modInverse(a, 26);
        for (int i = 0; i < text.size(); i++)
        {
            temp = text[i];

            if (isupper(temp))
            {
                start = 'A';
                result.push_back(((inverse * ((temp - start) - b + 26)) % 26) + start);
            }
            else if (islower(temp))
            {
                start = 'a';
                result.push_back(((inverse * ((temp - start) - b + 26)) % 26) + start);
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

    int a, b;
    while (y == 1)
    {
        cout << "Enter a key (it must be co-prime with 26):";
        cin >> a;
        if (GCD(a, 26) == 1)
            y = 2;
        else
            cout << "Invalid  Key" << endl;
    }

    cout << "Enter a second key:";
    cin >> b;
    y = 1;

    cout << "Enter 1 for encryption" << endl;
    cout << "Enter 2 for decryption" << endl;
    cout << "Enter 3 to exit" << endl;

    while (y == 1)
    {
        cin >> x;
        cin.ignore();
        switch (x)
        {
        case 1:
            cout << "Enter Text to be encrypted:";
            getline(cin, Text);
            enc_decr(Text, 0, a, b);
            break;

        case 2:
            cout << "Enter Text to be decrypted:";
            getline(cin, Text);
            enc_decr(Text, 1, a, b);
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