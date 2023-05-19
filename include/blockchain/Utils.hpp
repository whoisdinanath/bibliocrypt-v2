#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <map>

void log(const std::string &);
void exitWithError(const std::string &);
std::vector<std::vector<std::string>> read_book_data(const std::string filename);
std::vector<std::vector<std::string>> read_user_data(const std::string filename);
std::string truncateString(std::string inputStr);
std::string getName(std::string inputStr, int index);
std::string selectPublicKey();