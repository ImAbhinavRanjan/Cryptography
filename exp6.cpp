#include <iostream>
#include <cmath>
using namespace std;


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

int main()
{
    
    long long p, g;
    cout << "Enter a prime number (p): ";
    cin >> p;
    cout << "Enter a primitive root modulo p (g): ";
    cin >> g;

    
    long long a, b;
    cout << "Enter Alice's private key: ";
    cin >> a;
    cout << "Enter Bob's private key: ";
    cin >> b;

    
    long long A = modExp(g, a, p); 
    long long B = modExp(g, b, p); 

    cout << "Alice's public key (A): " << A << endl;
    cout << "Bob's public key (B): " << B << endl;

    
    long long sharedKeyAlice = modExp(B, a, p); 
    long long sharedKeyBob = modExp(A, b, p);  

    cout << "Shared key computed by Alice: " << sharedKeyAlice << endl;
    cout << "Shared key computed by Bob: " << sharedKeyBob << endl;

    
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
