#include <iostream>
// #include <boost/date_time/posix_time/posix_time.hpp>
#include <blockchain/Block.hpp>

#include <cryptography/sha256.h>

using json = nlohmann::json;

Block::Block(int index, std::string blockHash, std::string previousHash, std::string time, std::string minerAddress, std::string merkleHash, std::vector<Transaction> transaction)
{
    this->m_index = index;
    this->m_previousHash = previousHash;

    // boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    // std::string time = boost::posix_time::to_simple_string(now);
    this->m_timestamp = time;
    this->m_minerAddress = minerAddress;
    this->m_merkleHash = merkleHash;
    this->m_transactions = transaction;
    this->m_blockHash = blockHash;
}

Block::Block(json _block)
{
    this->m_index = _block["index"];
    this->m_previousHash = _block["previousHash"];
    this->m_timestamp = _block["timestamp"];
    this->m_minerAddress = _block["minerAddress"];
    this->m_merkleHash = _block["merkleHash"];
    this->m_blockHash = _block["blockHash"];
    for (auto &t : _block["transactions"])
    {
        Transaction transaction = Transaction(t);
        this->m_transactions.push_back(transaction);
    }
}

std::string Block::getHash()
{
    return this->m_blockHash;
}

std::string Block::getMinerAddress()
{
    return this->m_minerAddress;
}

std::string Block::getPreviousHash()
{
    return this->m_previousHash;
}
std::string Block::getMerkleHash()
{
    return this->m_merkleHash;
}
std::string Block::getTimestamp()
{
    return this->m_timestamp;
}
int Block::getIndex()
{
    return this->m_index;
}

void Block::toString()
{
    std::string dataStr = "";
    //

    std::cout << "Block Hash: " << m_blockHash << std::endl;
    std::cout << "Previous Hash: " << m_previousHash << std::endl;
    std::cout << "Timestamp: " << m_timestamp;
    std::cout << "Miner Address: " << m_minerAddress << std::endl;
    std::cout << "Merkle Hash: " << m_merkleHash << std::endl;
    std::cout << "Transactions: " << std::endl;
    for (int i = 0; i < int(m_transactions.size()); i++)
    {
        std::cout << "Transaction " << i << ": " << std::endl;
        std::cout << m_transactions[i].toJsonString();
    }
}

std::vector<Transaction> Block::getTransaction()
{
    return this->m_transactions;
}

// error probably here
json Block::toJson()
{
    json j;
    for (auto &t : m_transactions)
    {
        j["transactions"].push_back(t.toJson());
    }
    j["index"] = m_index;
    j["blockHash"] = m_blockHash;
    j["previousHash"] = m_previousHash;
    j["timestamp"] = m_timestamp;
    j["minerAddress"] = m_minerAddress;
    j["merkleHash"] = m_merkleHash;
    return j;
}