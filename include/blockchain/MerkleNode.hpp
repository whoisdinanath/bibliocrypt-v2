#ifndef MERKLENODE_HPP
#define MERKLENODE_HPP

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cryptography/sha256.h>

// std::string concat(const std::string &left, const std::string &right) noexcept
// {
//     return left + right;
// }

class MerkleTree
{
public:
    template <typename T>
    explicit MerkleTree(const std::vector<T> &values)
    {
        if (values.empty())
        {
            throw std::invalid_argument("Cannot create a Merkle tree with no values");
        }

        // Create the leaf nodes
        for (const T &value : values)
        {
            leaves.emplace_back(Leaf{sha256(value), value});
        }

        // Create the intermediate and root nodes
        while (leaves.size() > 1)
        {
            std::vector<Node> new_nodes;
            for (size_t i = 0; i < leaves.size(); i += 2)
            {

                Node node;
                // above line gives no matching function for call to 'merkle::MerkleTree::Node::Node()' error

                if (i + 1 < leaves.size())
                {
                    // Concatenate the hashes of the two children and hash the result
                    node.hash = sha256(leaves[i].hash + leaves[i + 1].hash);
                    node.left = std::make_shared<Node>(leaves[i]);
                    node.right = std::make_shared<Node>(leaves[i + 1]);
                    // std::cout << "Node hash is " << node.hash << std::endl;
                }
                else
                {
                    // Only one child, so just copy it
                    node = Node(leaves[i]);
                }
                new_nodes.push_back(node);
            }
            leaves = std::move(new_nodes);
        }

        // The root node should now be the only element in the leaves vector
        root = std::make_shared<Node>(leaves[0]);
    }

    // add every node and leaf nodes hashes to a vector and return it
    std::vector<std::string> get_all_hashes() const
    {
        std::vector<std::string> hashes;
        std::function<void(const std::shared_ptr<Node> &)> traverse = [&](const std::shared_ptr<Node> &node)
        {
            hashes.push_back(node->hash);
            if (node->left)
            {
                traverse(node->left);
            }
            if (node->right)
            {
                traverse(node->right);
            }
        };
        traverse(root);
        return hashes;
    }

    // check if the value is present in the tree using get_all_hashes()
    bool contains(const std::string &value) const
    {
        std::string hash = sha256(value);
        std::vector<std::string> hashes = get_all_hashes();
        for (const std::string &h : hashes)
        {
            if (h == hash)
            {
                return true;
            }
        }
        return false;
    }

    std::string root_hash() const
    {
        return root->hash;
    }

private:
    struct Leaf
    {
        std::string hash;
        std::string value;
    };

    struct Node
    {
        std::string hash;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        explicit Node(const Leaf &leaf)
            : hash(leaf.hash), left(nullptr), right(nullptr) {}
        Node() : hash(), left(), right() {}
    };

    std::shared_ptr<Node> root;
    std::vector<Node> leaves;
};

// int main()
// {
//     std::vector<std::string> transactions = {"a", "b", "c", "d"};
//     MerkleTree m(transactions);

//     User u1("Hello");
// }

#endif // MERKLENODE_HPP
