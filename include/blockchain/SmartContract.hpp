#include <blockchain/Book.hpp>
#include <blockchain/Transaction.hpp>

namespace SmartContract
{
    bool isISBNValid(const std::string &isbn);
    vector<string> getqueryfromenc(vector<int> x);
    bool validate_trans(vector<string> decryptedd);
    void update_files(vector<string> decryptedd);
}
// Transaction validateQueryTransaction(std::vector<int>);
