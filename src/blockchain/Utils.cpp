#include <iostream>
#include <blockchain/Utils.hpp>
#include <filesystem>

void log(const std::string &message)
{
    std::cout << message << std::endl;
}

void exitWithError(const std::string &errorMessage)
{

    std::cout << "Error: ";
    log(errorMessage);
    exit(1);
}

std::vector<std::vector<std::string>> read_user_data(const std::string filename)
{
    std::filesystem::path p(filename);
    if (!std::filesystem::exists(p))
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            std::cout << "Error opening file!" << std::endl;
        }
        if (filename == "./assets/data.csv")
            file << "ID,PRIVATE_KEY,PUBLIC_KEY,TOKEN,OWNERSHIP_ID" << std::endl;

        file.close();
    }

    std::ifstream file(filename);
    std::vector<std::vector<std::string>> userData;
    if (!file.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
    }

    // Loop through file and search for matching row
    std::string line;
    while (std::getline(file, line))
    {
        // Split line into columns using comma as delimiter
        std::string column;
        std::vector<std::string> columns;
        std::istringstream ss(line);
        while (getline(ss, column, ','))
        {
            columns.push_back(column);
        }
        userData.push_back(columns);
    }
    file.close();
    return userData;
}

std::vector<std::vector<std::string>> read_book_data(const std::string filename)
{
    std::filesystem::path p(filename);
    if (!std::filesystem::exists(p))
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            std::cout << "Error opening file!" << std::endl;
        }
        if (filename == "./assets/book.csv")
            file << "TITLE,AUTHOR,ISBN,OWNER_ID" << std::endl;

        file.close();
    }

    std::ifstream file(filename);
    std::vector<std::vector<std::string>> bookData;
    if (!file.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
    }

    // Loop through file and search for matching row
    std::string line;
    while (std::getline(file, line))
    {
        // Split line into columns using comma as delimiter
        std::string column;
        std::vector<std::string> columns;
        std::istringstream ss(line);
        while (getline(ss, column, ','))
        {
            columns.push_back(column);
        }
        bookData.push_back(columns);
    }
    file.close();
    return bookData;
}

std::string truncateString(std::string inputStr)
{
    const int maxLength = 40;
    if (inputStr.length() > maxLength)
    {
        inputStr = inputStr.substr(0, maxLength - 3); // subtract 3 for "..."
        inputStr.append("...");
    }
    return inputStr;
}

std::string getName(std::string inputStr, int index)
{
    std::string name;
    name = inputStr + " " + std::to_string(index);
    return name;
}

std::string selectPublicKey()
{

    std::ifstream file("./assets/data.csv");
    if (!file.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        exit(1);
    }
    std::string line, publicKey;
    int maxToken = 0;
    std::map<std::string, int> tokenToPublicKey;
    getline(file, line); // skip the header
    while (std::getline(file, line))
    {
        // Split line into columns using comma as delimiter
        std::string column;
        std::vector<std::string> columns;
        std::istringstream ss(line);
        while (getline(ss, column, ','))
        {
            columns.push_back(column);
        }

        std::cout << columns[3] << std::endl;

        tokenToPublicKey.insert(std::pair<std::string, int>(columns[2], std::stoi(columns[3])));
        // get the public key by comparing the maximum token
        // get the max value key
        for (auto it = tokenToPublicKey.begin(); it != tokenToPublicKey.end(); ++it)
        {
            if (it->second > maxToken)
            {
                maxToken = it->second;
                publicKey = it->first;
            }
        }
    }
    file.close();
    return publicKey;
}