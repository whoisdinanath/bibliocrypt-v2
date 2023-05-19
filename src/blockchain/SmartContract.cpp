#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cryptography/sha256.h>
#include <string>

#include <blockchain/SmartContract.hpp>

using namespace std;

bool SmartContract::isISBNValid(const std::string &isbn)
{

    std::string stripped;
    for (char c : isbn)
    {
        if (c >= '0' && c <= '9')
        {
            stripped += c;
        }
    }
    if (stripped.length() != 13)
    {
        return false;
    }

    int sum = 0;
    for (int i = 0; i < 12; i++)
    {
        int digit = stripped[i] - '0';
        sum += (i % 2 == 0) ? digit : 3 * digit;
    }
    int checkDigit = (10 - (sum % 10)) % 10;
    int actualCheckDigit = stripped[12] - '0';
    return (checkDigit == actualCheckDigit);
}

vector<string> SmartContract::getqueryfromenc(vector<int> x)
{
    std::cout << "Breaking the encryption..." << std::endl;
    vector<CryptSource> c1 = getdatac();

    for (CryptSource c : c1)
    {
        std::cout << "Inside the loop..." << std::endl;

        string msg = f_decrypted(x, c.public_key);
        std::cout << c.public_key << std::endl;
        std::cout << "Decrypted message: " << msg << std::endl;
        if (msg.find(c.public_key) != string::npos)
        {
            std::cout << "Found the public key..." << std::endl;

            stringstream s_str(msg);
            vector<string> result;
            while (s_str.good())
            {
                std::cout << "decrypting the query..." << std::endl;
                string substr;
                getline(s_str, substr, '|');
                result.push_back(substr);
                std::cout << substr << std::endl;
            }

            result.push_back(c.public_key);

            std::cout << "Decrypted query: " << std::endl;
            for (auto i : result)
            {
                std::cout << i << std::endl;
            }
            return result;
        }
    }

    return {};
}

bool SmartContract::validate_trans(vector<string> decryptedd)
{
    vector<CryptSource> c1 = getdatac();
    vector<Book> b1 = getdatab();
    bool first = false;
    bool second = false;
    if (decryptedd[0] == "GET")
    {
        // print debug points and respective values
        std::cout << "Inside the GET..." << std::endl;
        std::cout << "decryptedd[4]: " << decryptedd[4] << std::endl;
        for (auto k : c1)
        {
            std::cout << "Inside the loop..." << std::endl;
            std::cout << "k.public_key: " << k.public_key << std::endl;
            if (k.public_key == decryptedd[4] && k.token >= 1)
            {
                std::cout << "Inside the if..." << std::endl;
                std::cout << "k.public_key: " << k.public_key << std::endl;
                first = true;
            }
        }
        for (auto p : b1)
        {
            std::cout << "Inside the loop..." << std::endl;
            std::cout << "p.isbn: " << p.isbn << std::endl;
            std::cout << "p.isbn: " << decryptedd[1] << std::endl;
            std::cout << "p.ownership: " << (p.ownership) << std::endl;
            if (p.isbn == decryptedd[1] && p.ownership == "00000000")
            {
                std::cout << "Inside the if..." << std::endl;
                std::cout << "p.isbn: " << p.isbn << std::endl;
                second = true;
            }
        }
    }
    else if (decryptedd[0] == "GIVE")
    {

        for (auto p : b1)
        {
            std::cout << "Inside the loop..." << std::endl;
            std::cout << "p.isbn: " << p.isbn << std::endl;
            if (p.isbn == decryptedd[1] && p.ownership == sha256(decryptedd[4]))
            {
                std::cout << "Inside the if..." << std::endl;
                std::cout << "p.isbn: " << p.isbn << std::endl;
                std::cout << "p.ownership: " << p.ownership << std::endl;
                first = true;
                second = true;
            }
        }
    }
    else if (decryptedd[0] == "DONATE")
    {
        if (isISBNValid(decryptedd[1]))
        {
            first = true;
            second = true;
        }
        if (b1.size() > 0)
        {
            for (auto p : b1)
            {
                if (p.isbn == decryptedd[1])
                {
                    second = false;
                }
            }
        }
    }
    return (first && second);
}

void SmartContract::update_files(vector<string> decryptedd)
{
    vector<CryptSource> p = getdatac();
    if (decryptedd[0] == "GET")
    {
        fstream temp;
        temp.open("./assets/temp.csv", ios::out | ios::in | ios::trunc);
        temp << "ID,PRIVATE_KEY,PUBLIC_KEY,TOKEN,OWNERSHIP_ID" << std::endl;
        vector<CryptSource> cc = getdatac();
        for (auto p : cc)
        {
            if (decryptedd[4] == p.public_key)
            {
                int digit = int(p.token);
                digit -= 1;
                temp << p.ID << "," << p.private_key << "," << p.public_key << "," << digit << "," << p.ownership_id << endl;
            }
            else
            {
                temp << p.ID << "," << p.private_key << "," << p.public_key << "," << p.token << "," << p.ownership_id << endl;
            }
        }
        remove("./assets/data.csv");
        rename("./assets/temp.csv", "./assets/data.csv");
        temp.close();
        fstream temp2;
        temp2.open("./assets/temp2.csv", ios::out | ios::in | ios::trunc);
        temp2 << "TITLE,AUTHOR,ISBN,OWNER_ID" << std::endl;
        vector<Book> cc2 = getdatab();
        for (auto p : cc2)
        {
            if (decryptedd[1] == p.isbn)
            {
                string ownership = sha256(decryptedd[4]);
                temp2 << p.title << "," << p.author << "," << p.isbn << "," << ownership << endl;
            }
            else
            {
                temp2 << p.title << "," << p.author << "," << p.isbn << "," << p.ownership << endl;
            }
        }
        remove("./assets/book.csv");
        rename("./assets/temp2.csv", "./assets/book.csv");
        temp2.close();
    }
    else if (decryptedd[0] == "GIVE")
    {
        fstream temp;
        temp.open("./assets/temp.csv", ios::out | ios::in | ios::trunc);
        temp << "ID,PRIVATE_KEY,PUBLIC_KEY,TOKEN,OWNERSHIP_ID" << std::endl;
        vector<CryptSource> cc = getdatac();
        for (auto p : cc)
        {
            if (decryptedd[4] == p.public_key)
            {
                int digit = int(p.token);
                digit += 1;
                temp << p.ID << "," << p.private_key << "," << p.public_key << "," << digit << "," << p.ownership_id << endl;
            }
            else
            {
                temp << p.ID << "," << p.private_key << "," << p.public_key << "," << p.token << "," << p.ownership_id << endl;
            }
        }
        remove("./assets/data.csv");
        rename("./assets/temp.csv", "./assets/data.csv");
        temp.close();
        fstream temp2;
        temp2.open("./assets/temp2.csv", ios::out | ios::in | ios::trunc);
        temp2 << "TITLE,AUTHOR,ISBN,OWNER_ID" << std::endl;
        vector<Book> cc2 = getdatab();
        for (auto p : cc2)
        {
            if (decryptedd[1] == p.isbn)
            {

                temp2 << p.title << "," << p.author << "," << p.isbn << ","
                      << "00000000" << endl;
            }
            else
            {
                temp2 << p.title << "," << p.author << "," << p.isbn << "," << p.ownership << endl;
            }
        }
        remove("./assets/book.csv");
        rename("./assets/temp2.csv", "./assets/book.csv");
        temp2.close();
    }
    else if (decryptedd[0] == "DONATE")
    {
        fstream temp;
        temp.open("./assets/temp.csv", ios::out | ios::in | ios::trunc);
        temp << "ID,PRIVATE_KEY,PUBLIC_KEY,TOKEN,OWNERSHIP_ID" << std::endl;
        vector<CryptSource> cc = getdatac();
        for (auto p : cc)
        {
            if (decryptedd[4] == p.public_key)
            {
                int digit = int(p.token);
                digit += 1;
                temp << p.ID << "," << p.private_key << "," << p.public_key << "," << digit << "," << p.ownership_id << endl;
            }
            else
            {
                temp << p.ID << "," << p.private_key << "," << p.public_key << "," << p.token << "," << p.ownership_id << endl;
            }
        }
        remove("./assets/data.csv");
        rename("./assets/temp.csv", "./assets/data.csv");
        temp.close();
        fstream bookFile;
        bookFile.open("./assets/book.csv", ios::out | ios::in | ios::app | ios::ate);

        std::stringstream ss;
        ss << std::string(decryptedd[2]) << "," << std::string(decryptedd[3]) << "," << std::string(decryptedd[1]) << ","
           << "00000000" << endl;
        bookFile << ss.str();
        // close
        bookFile.close();
    }
}
