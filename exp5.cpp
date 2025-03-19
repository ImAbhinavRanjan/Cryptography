#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

// Function to calculate gcd
template <typename T>
T gcd(T a, T b)
{
    while (b != 0)
    {
        T temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate modular exponentiation
long long modExp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to calculate RSA keys and return parameters
void calculateRSA(int &e, int &d, int &n)
{
    int p, q;
    cout << "Enter two distinct prime numbers p and q: ";
    cin >> p >> q;

    // Calculate n and phi
    n = p * q;
    int phi = (p - 1) * (q - 1);

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    cout << "Enter a value for e (1 < e < " << phi << "): ";
    cin >> e;
    while (gcd(e, phi) != 1)
    {
        cout << "e must be coprime with " << phi << ". Enter a valid e: ";
        cin >> e;
    }

    // Calculate d (multiplicative inverse of e mod phi)
    d = 1;
    while ((d * e) % phi != 1)
    {
        d++;
    }

    cout << "Public key: (" << e << ", " << n << ")\n";
    cout << "Private key: (" << d << ", " << n << ")\n";
}

// Function to perform encryption
void encrypt(int e, int n)
{
    int plaintext;
    cout << "Enter the plaintext (integer): ";
    cin >> plaintext;
    int ciphertext = modExp(plaintext, e, n);
    cout << "Encrypted text: " << ciphertext << "\n";
}

// Function to perform decryption
void decrypt(int d, int n)
{
    int ciphertext;
    cout << "Enter the ciphertext (integer): ";
    cin >> ciphertext;
    int plaintext = modExp(ciphertext, d, n);
    cout << "Decrypted text: " << plaintext << "\n";
}

int main()
{
    int e = 0, d = 0, n = 0;

    // Calculate RSA keys at the start
    calculateRSA(e, d, n);

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
            encrypt(e, n);
            break;
        case 2:
            decrypt(d, n);
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