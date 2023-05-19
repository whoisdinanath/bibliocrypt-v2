#ifndef TRANSOBJ_TRANSACTION_H
#define TRANSOBJ_TRANSACTION_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <blockchain/Book.hpp>
#include <sstream>
#include <networking/Json.hpp>
#include <cryptography/sha256.h>
using namespace std;
using json = nlohmann::json;

class Transaction
{
private:
    vector<int> transaction_;
    string updated_book_hash_;
    string updated_cert_hash_;
    unordered_map<string, string> fields_{{"b", updated_book_hash_}, {"c", updated_cert_hash_}};

public:
    Transaction(json j);
    Transaction(vector<int> transaction);
    string &operator[](const string &key);
    vector<int> &transactionn();
    void settrans(vector<int>);
    vector<string> getqueryfromenc();
    vector<int> getEncodedQuery();
    void calculate_hash_bandc();
    json toJson();
    string toJsonString();
    string representation();
    string getUpdatedBookHash();
    string getUpdatedCertHash();
};

#endif // TRANSOBJ_TRANSACTION_H
