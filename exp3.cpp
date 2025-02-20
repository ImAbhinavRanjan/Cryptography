// Write down a program for the encryption and decryption procedure of Hill Cipher.

#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

// Convert character to numeric value (A/a = 0, ..., Z/z = 25)
int charToNum(char c)
{
    if (isupper(c))
        return c - 'A';
    if (islower(c))
        return c - 'a';
    return -1; // Non-alphabet characters
}

// Convert numeric value to character
char numToChar(int n, bool isUppercase)
{
    return isUppercase ? (n + 'A') : (n + 'a');
}

// Perform matrix multiplication for Hill Cipher
vector<int> matrixMultiply(const vector<vector<int>> &key, const vector<int> &plaintext)
{
    vector<int> result(2, 0);
    result[0] = (key[0][0] * plaintext[0] + key[0][1] * plaintext[1]) % 26;
    result[1] = (key[1][0] * plaintext[0] + key[1][1] * plaintext[1]) % 26;
    return result;
}

// Find modular inverse
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
    throw invalid_argument("Modular inverse does not exist.");
}

// Inverse the key matrix
vector<vector<int>> inverseKeyMatrix(const vector<vector<int>> &key)
{
    int determinant = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    determinant = (determinant % 26 + 26) % 26; // Ensure the determinant is positive
    int determinantInverse = modInverse(determinant, 26);

    vector<vector<int>> inverse(2, vector<int>(2));
    inverse[0][0] = (key[1][1] * determinantInverse) % 26;
    inverse[0][1] = (-key[0][1] * determinantInverse % 26 + 26) % 26;
    inverse[1][0] = (-key[1][0] * determinantInverse % 26 + 26) % 26;
    inverse[1][1] = (key[0][0] * determinantInverse) % 26;

    return inverse;
}

// Encrypt plaintext using Hill Cipher
string hillEncrypt(const string &plaintext, const vector<vector<int>> &key)
{
    string ciphertext = "";
    vector<int> plaintextPair(2, 0);

    for (size_t i = 0; i < plaintext.length(); i += 2)
    {
        for (int j = 0; j < 2; ++j)
        {
            if (isalpha(plaintext[i + j]))
            {
                plaintextPair[j] = charToNum(plaintext[i + j]);
            }
            else
            {
                plaintextPair[j] = -1; // Skip non-alphabet characters
            }
        }

        vector<int> encryptedPair = matrixMultiply(key, plaintextPair);

        for (int j = 0; j < 2; ++j)
        {
            if (plaintextPair[j] == -1)
            {
                ciphertext += plaintext[i + j]; // Append unchanged non-alphabet characters
            }
            else
            {
                bool isUppercase = isupper(plaintext[i + j]);
                ciphertext += numToChar(encryptedPair[j], isUppercase);
            }
        }
    }

    return ciphertext;
}

// Decrypt ciphertext using Hill Cipher
string hillDecrypt(const string &ciphertext, const vector<vector<int>> &key)
{
    string plaintext = "";
    vector<int> ciphertextPair(2, 0);

    vector<vector<int>> inverseKey = inverseKeyMatrix(key);

    for (size_t i = 0; i < ciphertext.length(); i += 2)
    {
        for (int j = 0; j < 2; ++j)
        {
            if (isalpha(ciphertext[i + j]))
            {
                ciphertextPair[j] = charToNum(ciphertext[i + j]);
            }
            else
            {
                ciphertextPair[j] = -1; // Skip non-alphabet characters
            }
        }

        vector<int> decryptedPair = matrixMultiply(inverseKey, ciphertextPair);

        for (int j = 0; j < 2; ++j)
        {
            if (ciphertextPair[j] == -1)
            {
                plaintext += ciphertext[i + j]; // Append unchanged non-alphabet characters
            }
            else
            {
                bool isUppercase = isupper(ciphertext[i + j]);
                plaintext += numToChar(decryptedPair[j], isUppercase);
            }
        }
    }

    return plaintext;
}

// Main function
int main()
{
    vector<vector<int>> key = {
        {5, 17},
        {8, 3}};

    string plaintext;
    cout << "Enter plaintext (alphanumeric, even length): ";
    getline(cin, plaintext);

    if (plaintext.length() % 2 != 0)
    {
        cout << "Error: Plaintext length must be even!" << endl;
        return 1;
    }

    string ciphertext = hillEncrypt(plaintext, key);
    cout << "Encrypted ciphertext: " << ciphertext << endl;

    string decryptedText = hillDecrypt(ciphertext, key);
    cout << "Decrypted plaintext: " << decryptedText << endl;

    return 0;
}
