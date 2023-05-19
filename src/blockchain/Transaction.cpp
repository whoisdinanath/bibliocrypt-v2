#include <fstream>
#include <blockchain/Transaction.hpp>

using json = nlohmann::json;
using namespace std;

Transaction::Transaction(vector<int> transaction)
    : transaction_{transaction}
{
    Transaction::calculate_hash_bandc();
};

std::vector<int> Transaction::getEncodedQuery()
{
    return this->transaction_;
}
Transaction::Transaction(json j)
{
    for (int i = 0; i < int(j["encodedTrans"].size()); i++)
    {
        transaction_.push_back(j["encodedTrans"][i].get<int>());
    }
    updated_book_hash_ = j["updated_book_hash"].get<std::string>();
    updated_cert_hash_ = j["updated_cert_hash"].get<std::string>();
}

string Transaction::getUpdatedBookHash()
{
    return updated_book_hash_;
}

string Transaction::getUpdatedCertHash()
{
    return updated_cert_hash_;
}

string &Transaction::operator[](const string &key)
{
    return fields_.at(key);
}

vector<int> &Transaction::transactionn()
{
    return transaction_;
}

vector<string> Transaction::getqueryfromenc()
{
    vector<CryptSource> c1 = getdatac();
    for (CryptSource c : c1)
    {
        string msg = f_decrypted(transaction_, c.public_key);
        if (msg.find("|") != string::npos)
        {
            stringstream s_str(msg);
            vector<string> result;
            while (s_str.good())
            {
                string substr;
                getline(s_str, substr, '|');
                result.push_back(substr);
            }
            result.push_back(c.public_key);
            return result;
        }
    }
    return {};
}

void Transaction::settrans(vector<int> x)
{
    this->transaction_ = x;
}

void Transaction::calculate_hash_bandc()
{
    ifstream data_file("./assets/data.csv"), book_file("./assets/book.csv");
    if (!data_file.is_open() || !book_file.is_open())
    {
        throw runtime_error("file not found");
    }
    string _data = "";
    string data_line = "";
    string _book = "";
    string book_line = "";

    while (getline(data_file, data_line))
    {
        _data += data_line;
    }
    while (getline(book_file, book_line))
    {
        _book += book_line;
    }
    updated_cert_hash_ = sha256(_data);
    updated_book_hash_ = sha256(_book);
    data_file.close();
    book_file.close();
}

json Transaction::toJson()
{

    json j;
    for (int i = 0; i < int(transaction_.size()); i++)
    {
        j["encodedTrans"].push_back(transaction_[i]);
    }
    j["encodedTransSize"] = transaction_.size();
    j["updated_book_hash"] = updated_book_hash_;
    j["updated_cert_hash"] = updated_cert_hash_;
    return j;
}

string Transaction::representation()
{
    int sum = 0;
    for (int x : transaction_)
    {
        sum += x;
    }
    return (to_string(sum) + updated_book_hash_.substr(0, 5) + updated_cert_hash_.substr(0, 5));
}

string Transaction::toJsonString()
{

    return toJson().dump();
}