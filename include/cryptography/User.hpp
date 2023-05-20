#ifndef CRYPTOGRAPHY_USER_HPP
#define CRYPTOGRAPHY_USER_HPP
#include <iostream>
#include <vector>
#include <networking/Json.hpp>

#include <iostream>
#include <vector>
#include <random>
#include <cryptography/base64.h>
#include <cmath>
#include <cryptography/sha256.h>
#include <fstream>
#include <regex>

using json = nlohmann::json;

long long int decrypt(int encrpyted_text);
std::string decrypted(std::vector<int> encoded, std::string pubkey);

class User
{
public:
    User();
    User &operator=(const User &other);
    explicit User(std::string);
    User(User &user);
    int gen_prime();
    json toJson();
    bool check_prime(const int &num);
    int p, q, n{}, phi_n{}, e_0{}, d_0{};
    std::string ID, public_key, private_key, ownership_id;
    int token;

    void calculate_n();
    void calculate_phin();
    void calculate_d();
    void calculate_e();

    static void check_validity(std::string);
    static bool check_if_user_exists(const std::string &target);

    int gcd(int a, int b);

    std::vector<int> encoder(std::string message);
    std::string decoder(std::vector<int> encoded);

    long long int decrypt(int encrpyted_text);
    long long int encrypt(double message);

    void keynidgen();
    void getter() const;
    void writedata();
    void bin();
    void setData(std::string _id, std::string _publicKey, std::string _privateKey, int _token, std::string _ownershipId);
};

#endif // CRYPTOGRAPHY_USER_HPP