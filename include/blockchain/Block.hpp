#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <vector>
#include <networking/Json.hpp>
#include <blockchain/Transaction.hpp>

using json = nlohmann::json;

class Block
{
    int m_index;
    std::string m_blockHash;
    std::string m_previousHash;
    std::string m_timestamp;
    // std::string m_timestamp;
    std::string m_minerAddress;
    std::string m_merkleHash;
    std::vector<Transaction> m_transactions;

public:
    Block(int index, std::string m_blockHash, std::string m_previousHash, std::string m_timestamp, std::string m_minerAddress, std::string m_merkleHash, std::vector<Transaction> m_transactions);
    Block(json _block);
    std::string getHash(void);
    std::string getPreviousHash(void);
    std::string getTimestamp(void);
    std::string getMerkleHash();
    int getIndex(void);
    std::string getMinerAddress(void);
    std::vector<Transaction> getTransaction();
    void toString(void);
    json toJson(void);
};

#endif