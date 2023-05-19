#ifndef __BLOCKCHAIN_HPP__
#define __BLOCKCHAIN_HPP__
#include <vector>
#include <memory>
#include <iostream>
#include <ctime>
#include <blockchain/Block.hpp>
#include <cryptography/sha256.h>
#include <networking/Json.hpp>
#include <blockchain/Transaction.hpp>
#include <cryptography/User.hpp>
#include <blockchain/MerkleNode.hpp>

using json = nlohmann::json;

class Blockchain
{
public:
    Blockchain(int genesis = 0);
    Block getBlock(int index);
    Block getLatestBlock();
    bool addBlock(std::string prevHash, std::string timestamp, std::string miner, std::string merkleHash, std::vector<Transaction> transactions);
    std::string toJsonStr();
    bool addBlock(Block block);
    int replaceChain(json chain);
    std::string calculateHash(int height, std::string prevHash, std::string merkleHash, std::string timestamp, std::string miner);
    int getLength();
    ~Blockchain();

private:
    std::vector<std::unique_ptr<Block>> blockchain;
};

// std::string getBlockHash(std::string prevHash, std::string merkleHash, std::string timestamp, std::string miner)
// {
//     return sha256(prevHash + merkleHash + miner + timestamp);
// }

#endif // __BLOCKCHAIN_HPP__