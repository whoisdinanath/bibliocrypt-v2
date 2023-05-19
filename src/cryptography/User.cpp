#include <iostream>
#include <vector>
#include <random>
#include <cryptography/base64.h>
#include <cmath>
#include <cryptography/sha256.h>
#include <fstream>
#include <networking/Json.hpp>
#include <cryptography/User.hpp>
#include <regex>

using namespace std;

User::User() = default;
User &User::operator=(const User &other)
{
    if (this != &other)
    {
        this->ID = other.ID;
        this->public_key = other.public_key;
        this->private_key = other.private_key;
        this->ownership_id = other.ownership_id;
        this->token = other.token;
        this->p = other.p;
        this->q = other.q;
        this->n = other.n;
        this->phi_n = other.phi_n;
        this->e_0 = other.e_0;
        this->d_0 = other.d_0;
    }
    return *this;
}

User::User(User &other)
{
    ID = other.ID;
    p = other.p;
    q = other.q;
    n = other.n;
    phi_n = other.phi_n;
    e_0 = other.e_0;
    d_0 = other.d_0;
    public_key = other.public_key;
    private_key = other.private_key;
    ownership_id = other.ownership_id;
    token = other.token;
}

int User::gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

bool User::check_prime(const int &num)
{
    vector<unsigned> p_factors;
    for (unsigned i = 2; i <= static_cast<unsigned>(sqrt(num)); i++)
    {
        if (num % i == 0)
        {
            p_factors.push_back(i);
            p_factors.push_back(num / i);
        }
    }
    if (p_factors.size() != 0)
    {
        return false;
    }
    return true;
}

void User::check_validity(string ID)
{
    // THA<3 digit><3 alphabet><3 digit>
    //  check format in single line
    regex pattern("THA[0-9]{3}[A-Z]{3}[0-9]{3}");
    if (!regex_match(ID, pattern))
    {
        throw std::invalid_argument("Invalid ID");
    }
}
bool User::check_if_user_exists(const std::string &target)
{
    std::fstream file("./assets/data.csv", std::ios::in);
    if (!file)
    {
        std::cerr << "Error: could not open file "
                  << "{data.csv}." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        size_t pos = line.find(',');
        if (pos != std::string::npos && line.substr(0, pos) == target)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

int User::gen_prime()
{
    random_device rd;
    uniform_int_distribution<int> range(10, 200);
    int num;
    while (1)
    {
        num = range(rd);
        if (User::check_prime(num))
        {
            break;
        }
    }
    return num;
}

User::User(string s) : ID{s}
{

    User::check_validity(ID);
    p = User::gen_prime();
    while (1)
    {
        q = User::gen_prime();
        if (q != p)
            break;
    }
    User::calculate_n();
    User::calculate_phin();
    User::calculate_e();
    User::calculate_d();
    User::keynidgen();
    token = 5;
    User::writedata();
    User::bin();
    std::cout << "User Created..." << std::endl;
    std::cout << "This is your private key, keep it safe: " << private_key << std::endl;
    std::cout << "This is your public key, share it with your friends: " << public_key << std::endl;
}

void User::bin()
{
    ofstream file("./assets/user.bin", ios::binary | ios::app);
    if (!file)
    {
        std::cerr << "Error: could not open file "
                  << "{user.bin}." << std::endl;
        return;
    }
    file.write((char *)this, sizeof(User));
    file.close();
}

long long int User::encrypt(double message)
{
    int d = d_0;
    long long int encrpyted_text = 1;
    while (d)
    {
        encrpyted_text *= message;
        encrpyted_text %= n;
        d--;
    }
    return encrpyted_text;
}

long long int User::decrypt(int encrpyted_text)
{
    int e = e_0;
    long long int decrypted = 1;
    while (e)
    {
        decrypted *= encrpyted_text;
        decrypted %= n;
        e--;
    }
    return decrypted;
}

vector<int> User::encoder(string message)
{
    vector<int> form;
    for (auto &letter : message)
        form.push_back(User::encrypt((int)letter));
    return form;
}
string User::decoder(vector<int> encoded)
{
    string s;
    for (auto &num : encoded)
        s += User::decrypt(num);
    return s;
}

void User::keynidgen()
{
    int index = (log10(n) + 1);
    string str1 = to_string(n);
    string str2 = to_string(d_0);
    string str3 = to_string(index);
    string str4 = str1 + str2 + str3;
    long long value = std::stoll(str4);
    vector<uint8_t> data(reinterpret_cast<uint8_t *>(&value), reinterpret_cast<uint8_t *>(&value) + sizeof(value));
    private_key = base64pp::encode(data);
    string str5 = to_string(e_0);
    string str6 = to_string(index);
    string str7 = str1 + str5 + str6;
    long long value1 = std::stoll(str7);
    vector<uint8_t> data1(reinterpret_cast<uint8_t *>(&value1), reinterpret_cast<uint8_t *>(&value1) + sizeof(value1));
    public_key = base64pp::encode(data1);
    ownership_id = sha256(public_key);
}

void User::calculate_n()
{
    n = p * q;
}

void User::calculate_phin()
{
    phi_n = (p - 1) * (q - 1);
}

void User::calculate_e()
{
    int e = 2;
    while (1)
    {
        if (User::gcd(e, phi_n) == 1)
            break;
        e++;
    }
    e_0 = e;
}

void User::calculate_d()
{
    int d = 2;
    while (1)
    {
        if ((d * e_0) % phi_n == 1)
            break;
        d++;
    }
    d_0 = d;
}

void User::getter() const
{
    cout << "p : " << p << endl;
    cout << "q : " << q << endl;
    cout << "n : " << n << endl;
    cout << "phi(n) : " << phi_n << endl;
    cout << "e : " << e_0 << endl;
    cout << "d : " << d_0 << endl;
    cout << "ID :" << ID << endl;
    cout << "Public key(Address) : " << public_key << endl;
    cout << "private Key : " << private_key << endl;
    cout << "ownership id :" << ownership_id << endl;
    cout << "Token : " << token << endl;
}

void User::writedata()
{
    ofstream file;
    file.open("./assets/data.csv", ios_base::app);
    if (!file)
    {
        cout << "Error in creating file!!!" << endl;
        return;
    }
    if (file.is_open())
    {
        file << ID << "," << private_key << "," << public_key << "," << token << "," << ownership_id << "\n";
        file.close();
    }
}

void User::setData(string _id, string _publicKey, string _privateKey, int _token, string _ownershipId)
{
    ID = _id;
    private_key = _privateKey;
    public_key = _publicKey;
    token = _token;
    ownership_id = _ownershipId;
}

long long int decrypt(int encrpyted_text, int e_0, int n)
{
    int e = e_0;
    long long int decrypted = 1;
    while (e)
    {
        decrypted *= encrpyted_text;
        decrypted %= n;
        e--;
    }
    return decrypted;
}
string decrypted(vector<int> encoded, string pubkey)
{
    int n;
    int e;
    vector<uint8_t> decoded = base64pp::decode(pubkey);
    long long value2 = *reinterpret_cast<long long *>(decoded.data());
    string s = to_string(value2);
    char index = s.back();
    int last = index - '0';
    int first = stoi(s.substr(0, last));
    int second = floor(stoi(s.substr(last)) / 10);
    n = first;
    e = second;
    string str;
    for (auto &num : encoded)
        str += decrypt(num, e, n);
    return s;
}

json User::toJson()
{
    json j;
    j["ID"] = ID;
    j["private_key"] = private_key;
    j["public_key"] = public_key;
    j["token"] = token;
    j["ownership_id"] = ownership_id;
    return j;
}