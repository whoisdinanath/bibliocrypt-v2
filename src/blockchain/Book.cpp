#include <blockchain/Book.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <cryptography/base64.h>

vector<CryptSource> getdatac()
{

    ifstream inputfile;
    // std::cout << "Reading the certificates data..." << std::endl;
    inputfile.open("./assets/data.csv", ios::in);
    if (!inputfile.is_open())
    {
        // std::cout << "Certificates data not found" << std::endl;
        exit(1);
    }
    string line = "";
    getline(inputfile, line);
    line = "";
    vector<CryptSource> cryptdata;
    // std::cout << "Reading the certificates data..." << std::endl;
    while (getline(inputfile, line))
    {
        // std::cout << "Reading the certificates data..." << std::endl;
        // std::cout << line << std::endl;
        if (!line.empty())
        {
            // std::cout << "Reading the certificates data..." << std::endl;
            stringstream inputstring(line);
            string t_ID;
            string t_private_key;
            string t_public_key;
            string t_token;
            string t_ownership_id;

            getline(inputstring, t_ID, ',');
            getline(inputstring, t_private_key, ',');
            getline(inputstring, t_public_key, ',');
            getline(inputstring, t_token, ',');
            getline(inputstring, t_ownership_id, '\n');

            CryptSource data(t_ID, t_private_key, t_public_key, stoi(t_token), t_ownership_id);

            cryptdata.push_back(data);
            line = "";
        }
    }
    inputfile.close();

    return cryptdata;
}

vector<Book> getdatab()
{
    // std::cout << "Reading the book data..." << std::endl;
    ifstream inputfile;
    inputfile.open("./assets/book.csv", ios::in);
    if (!inputfile.is_open())
    {
        // std::cout << "Book data not found" << std::endl;
        exit(1);
    }
    string line = "";
    getline(inputfile, line);
    line = "";
    vector<Book> bookdata;
    // std::cout << "Reading the book data..." << std::endl;
    while (getline(inputfile, line))
    {
        // std::cout << line << std::endl;
        if (!line.empty())
        {
            // std::cout << "Reading the book data..." << line << std::endl;
            stringstream inputstring(line);
            string title;
            string author;
            string isbn;
            string owner;

            getline(inputstring, title, ',');
            getline(inputstring, author, ',');
            getline(inputstring, isbn, ',');
            getline(inputstring, owner, '\n');
            // std::cout << "Reading the book data..." << title << author << isbn << owner << std::endl;
            Book data(title, author, isbn, owner);
            bookdata.push_back(data);
            line = "";
            // std::cout << "Reading the book data... complete" << std::endl;
        }
        // std::cout << "Reading the book data... complete2" << std::endl;
    }
    // std::cout << "Reading the book data... complete3" << std::endl;
    inputfile.close();
    return bookdata;
}

CryptSource::CryptSource(string id, string priv, string pubk, int tokenn, string hash)
{
    this->ownership_id = hash;
    this->ID = id;
    this->private_key = priv;
    this->public_key = pubk;
    this->token = tokenn;
}

Book::Book(string ti, string auth, string is, string own)
{
    this->isbn = is;
    this->author = auth;
    this->title = ti;
    this->ownership = own;
}

long long int encrypttt(double message, int d_0, int n)
{
    int d = d_0;
    long long int encrpyted_text = 1;
    while (d)
    {
        encrpyted_text *= message;
        encrpyted_text %= n;
        d--;
    }
    return encrpyted_text;
}

long long int decrypttt(int encrpyted_text, int e_0, int n)
{
    int e = e_0;
    long long int decrypted = 1;
    while (e)
    {
        decrypted *= encrpyted_text;
        decrypted %= n;
        e--;
    }
    return decrypted;
}

string f_decrypted(vector<int> encoded, string pubkey)
{
    int n;
    int e;
    vector<uint8_t> decoded = base64pp::decode(pubkey);
    long long value2 = *reinterpret_cast<long long *>(decoded.data());
    string s = to_string(value2);
    char index = s.back();
    int last = index - '0';
    int first = stoi(s.substr(0, last));
    int second = floor(stoi(s.substr(last)) / 10);
    n = first;
    e = second;
    string str;
    for (auto &num : encoded)
    {
        str += decrypttt(num, e, n);
    }
    return str;
}

vector<int> f_encrypted(string message, string privkey)
{
    int n;
    int d;
    vector<uint8_t> decoded = base64pp::decode(privkey);
    long long value2 = *reinterpret_cast<long long *>(decoded.data());
    string s = to_string(value2);
    char index = s.back();
    int last = index - '0';
    int first = stoi(s.substr(0, last));
    int second = floor(stoi(s.substr(last)) / 10);
    n = first;
    d = second;
    vector<int> form;
    for (auto letter : message)
    {
        form.push_back(encrypttt((int)letter, d, n));
    }
    return form;
}