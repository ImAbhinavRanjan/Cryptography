#include <iostream>
#include <cmath>
using namespace std;

// Function to compute modular exponentiation
long long modExp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1) // If exp is odd
            result = (result * base) % mod;
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod;
    }
    return result;
}

int main()
{
    // Public parameters
    long long p, g;
    cout << "Enter a prime number (p): ";
    cin >> p;
    cout << "Enter a primitive root modulo p (g): ";
    cin >> g;

    // Private keys for Alice and Bob
    long long a, b;
    cout << "Enter Alice's private key: ";
    cin >> a;
    cout << "Enter Bob's private key: ";
    cin >> b;

    // Calculate public keys
    long long A = modExp(g, a, p); // Alice's public key
    long long B = modExp(g, b, p); // Bob's public key

    cout << "Alice's public key (A): " << A << endl;
    cout << "Bob's public key (B): " << B << endl;

    // Calculate shared secret keys
    long long sharedKeyAlice = modExp(B, a, p); // Alice computes shared key
    long long sharedKeyBob = modExp(A, b, p);   // Bob computes shared key

    cout << "Shared key computed by Alice: " << sharedKeyAlice << endl;
    cout << "Shared key computed by Bob: " << sharedKeyBob << endl;

    // Verify if both keys match
    if (sharedKeyAlice == sharedKeyBob)
    {
        cout << "Key exchange successful! Shared secret key: " << sharedKeyAlice << endl;
    }
    else
    {
        cout << "Key exchange failed! Keys do not match." << endl;
    }

    return 0;
}
