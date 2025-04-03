// Implement a program that performs encryption and decryption for the given message using RC4.
#include <iostream>
#include <string>
using namespace std;

// Function to swap two values
void swap(unsigned char &a, unsigned char &b)
{
    unsigned char temp = a;
    a = b;
    b = temp;
}

// KSA function to initialize and shuffle S-box
void KSA(string key, unsigned char S[])
{
    int key_length = key.length();
    // Step 1: Initialize S-box with 0 to 255
    for (int i = 0; i < 256; i++)
    {
        S[i] = i;
    }
    // Step 2: Shuffle S-box based on key
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % key_length]) % 256;
        swap(S[i], S[j]);
    }
}

// PRGA function to generate keystream and encrypt/decrypt
string RC4(string key, string plaintext)
{
    unsigned char S[256];
    KSA(key, S);

    int i = 0, j = 0;
    string ciphertext = "";
    // Generate keystream and XOR with plaintext
    for (int k = 0; k < plaintext.length(); k++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        int t = (S[i] + S[j]) % 256;
        unsigned char keystream = S[t];
        ciphertext += plaintext[k] ^ keystream; // XOR operation
    }
    return ciphertext;
}

int main()
{
    string key, plaintext, result;
    cout << "Enter your secret key: ";
    getline(cin, key);
    cout << "Enter your plaintext: ";
    getline(cin, plaintext);

    cout << "Plaintext: " << plaintext << endl;

    // Encrypton
    string encrypted = RC4(key, plaintext);
    cout << "Encrypted text: " << encrypted << endl; // Direct characters print

    // Decryption
    string decrypted = RC4(key, encrypted);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
