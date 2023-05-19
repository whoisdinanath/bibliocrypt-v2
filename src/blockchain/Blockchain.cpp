#include <blockchain/BlockChain.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include <ctime>
#include <fstream>
#include <blockchain/MerkleNode.hpp>
#include <ctime>

using json = nlohmann::json;

Blockchain::Blockchain(int genesis)
{
    if (genesis == 0)
    {

        std::vector<int> data = {0, 0, 0, 0};
        std::vector<Transaction> transactions = {data};
        time_t now = time(0);
        std::string timestamp = ctime(&now);
        std::string miner = sha256("BIBEK|ERIC|KRISHNA");
        std::string contract;

        ifstream smartContract("./src/blockchain/SmartContract.cpp");
        if (!smartContract)
        {
            std::cout << "Unable to open file";
            exit(1); // terminate with error
        }
        if (smartContract.is_open())
        {
            std::string line;
            while (getline(smartContract, line))
            {
                contract += line;
            }
            smartContract.close();
        }
        else
        {
            std::cout << "Unable to open file";
        }
        std::string prevHash = sha256(contract);
        std::vector<std::string> transactionQuery = {"BIBEK", "ERIC", "KRISHNA", ""};
        MerkleTree m1(transactionQuery);
        std::string merkleHash = m1.root_hash();
        std::string blockHash = sha256(std::to_string(0) + merkleHash + miner + timestamp);
        std::unique_ptr<Block> genesisBlock = make_unique<Block>(0, blockHash, prevHash, timestamp, miner, merkleHash, transactions);
        this->blockchain.push_back(std::move(genesisBlock));
    }
}

Blockchain::~Blockchain()
{
}
Block Blockchain::getLatestBlock()
{
    return *blockchain.back();
}

Block Blockchain::getBlock(int index)
{
    return *blockchain[index];
}
bool Blockchain::addBlock(std::string prevHash, std::string timestamp, std::string miner, std::string merkleHash, std::vector<Transaction> transactions)
{

    int blockHeight = blockchain.size();
    std::string blockHash = sha256(std::to_string(blockHeight) + prevHash + merkleHash + timestamp + miner);

    std::unique_ptr<Block> newBlock = make_unique<Block>(blockHeight, blockHash, prevHash, timestamp, miner, merkleHash, transactions);
    blockchain.push_back(std::move(newBlock));

    return true;
}

// another probable error
bool Blockchain::addBlock(Block _block)
{
    // checks the succes  and return true/false

    std::unique_ptr<Block> newBlock = make_unique<Block>(_block);
    blockchain.push_back(std::move(newBlock));
    return true;
}

std::string Blockchain::toJsonStr()
{
    json j;
    j["length"] = this->blockchain.size();
    for (int i = 0; i < int(blockchain.size()); i++)
    {
        j["data"][this->blockchain[i]->getIndex()] = this->blockchain[i]->toJson();
    }
    return j.dump();
}

std::string calculateHash(int height, std::string prevHash, std::string merkleHash, std::string timestamp, std::string miner)
{
    return sha256(std::to_string(height) + prevHash + merkleHash + miner + timestamp);
}

// int Blockchain::replaceChain(json chain)
// {
//     if (chain["length"] >= this->blockchain.size())
//     {
//         this->blockchain.clear();
//         for (auto &block : chain["data"])
//         {

//             std::vector<std::string> transactions;
//             for (auto &transaction : block["transactions"])
//             {
//                 std::cout << transaction << std::endl;

//                 transactions.push_back(transaction);
//             }
//             std::unique_ptr<Block> newBlock = make_unique<Block>(block["index"], block["blockHash"], block["prevHash"], block["timestamp"], block["nonce"], block["miner"], block["merkleHash"], transactions);
//             blockchain.push_back(std::move(newBlock));
//         }
//         return 1;
//     }
//     else
//     {
//         return 0;
//     }
// }

int Blockchain::replaceChain(json chain)
{
    std::cout << "Replacing the chain..." << std::endl;
    while (this->blockchain.size() > 0)
    {
        this->blockchain.pop_back();
    }
    std::cout << chain.dump();

    for (int i = 0; i < chain["length"].get<int>(); i++)
    {
        std::cout << "Inside the for loop " << std::endl;
        std::string prevHash = chain["data"][i]["previousHash"].get<std::string>();
        std::cout << "Prev Hash" << std::endl;
        std::string timestamp = chain["data"][i]["timestamp"].get<std::string>();
        std::string miner = chain["data"][i]["minerAddress"].get<std::string>();
        std::string merkleHash = chain["data"][i]["merkleHash"].get<std::string>();
        std::vector<Transaction> transactions;
        std::cout << "Transaction loop" << std::endl;
        for (auto &transaction : chain["data"][i]["transactions"])
        {
            std::cout << "auto transaction loop" << std::endl;
            std::vector<int> encodedTrans;
            for (auto &enc : transaction["encodedTrans"])
            {
                std::cout << "Encoded Trans loop..." << std::endl;
                encodedTrans.push_back(enc.get<int>());
            }
            std::string updated_book_hash = transaction["updated_book_hash"].get<std::string>();
            std::string updated_cert_hash = transaction["updated_cert_hash"].get<std::string>();
            Transaction t1(encodedTrans);
            transactions.push_back(t1);
        }
        this->addBlock(prevHash, timestamp, miner, merkleHash, transactions);
    }
    std::cout << "Blockchain replaced" << std::endl;
    return 1;
}

int Blockchain::getLength()
{
    return this->blockchain.size();
}
