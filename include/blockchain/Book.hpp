#ifndef BOOK_HPP
#define BOOK_HPP
#include <iostream>
#include <vector>
using namespace std;

class CryptSource
{
public:
    string ID;
    string private_key;
    string public_key;
    int token;
    string ownership_id;
    CryptSource(string id, string priv, string pub, int token, string ownership);
};
class Book
{
public:
    std::string title;
    std::string author;
    std::string isbn;
    std::string ownership;
    Book(std::string, std::string, std::string, std::string);
};

std::vector<CryptSource> getdatac();
std::vector<Book> getdatab();

long long int encrypttt(double message, int d_0, int n);
long long int decrypttt(int encrpyted_text, int e_0, int n);
std::string f_decrypted(std::vector<int> encoded, std::string pubkey);
std::vector<int> f_encrypted(std::string message, std::string privkey);

#endif
