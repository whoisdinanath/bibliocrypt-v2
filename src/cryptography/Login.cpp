#include <cryptography/Login.hpp>
#include <cryptography/User.hpp>

bool login(std::string _userID, std::string _password)
{
    std::cout << "Password: " << _password << std::endl;
    // Open file
    std::ifstream file("./assets/user.bin", std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "Error opening file  !" << std::endl;
        return 1;
    }
    User temp_user;
    while (file.read((char *)&temp_user, sizeof(User)))
    {
        std::cout << "Password: " << temp_user.private_key << std::endl;
        if (temp_user.ID == _userID && temp_user.private_key == _password)
        {
            globalVars::global_user->ID = temp_user.ID;
            globalVars::global_user->private_key = temp_user.private_key;
            globalVars::global_user->public_key = temp_user.public_key;
            globalVars::global_user->token = temp_user.token;
            globalVars::global_user->n = temp_user.n;
            globalVars::global_user->e_0 = temp_user.e_0;
            globalVars::global_user->d_0 = temp_user.d_0;
            globalVars::global_user->phi_n = temp_user.phi_n;
            globalVars::global_user->p = temp_user.p;
            globalVars::global_user->q = temp_user.q;

            return true;
        }
        else
        {
            std::cout << "Error: Invalid username or password!" << std::endl;
            return false;
        }
    }

    // Loop through file and search for matching row
    // std::string line;
    // while (std::getline(file, line))
    // {
    //     // Split line into columns using comma as delimiter
    //     std::string column;
    //     std::vector<std::string> columns;
    //     std::istringstream ss(line);
    //     while (getline(ss, column, ','))
    //     {
    //         columns.push_back(column);
    //     }

    //     // Check if line has 5 columns
    //     if (columns.size() != 5)
    //     {
    //         std::cout << "Invalid line: " << line << std::endl;
    //         continue;
    //     }

    //     // Check first column for search string
    //     if (columns[0] == _userID)
    //     {
    //         // Check third column for match string
    //         if (columns[1] == _password)
    //         {
    //             // Set user data
    //             globalVars::global_user->setData(columns[0], columns[2], columns[3], std::stoi(columns[3]), columns[4]);
    //             return true;
    //         }
    //     }
    // }

    // Close file
    file.close();
    return false;
}