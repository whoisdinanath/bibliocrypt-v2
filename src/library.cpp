#include "library.hpp"

void library_func()
{
    while (1)
    {
        // stateVars::show_error = false;
        if (globalVars::exit_flag)
        {
            exit(0);
        }
        globalVars::m_book_data = read_book_data("./assets/book.csv");
        globalVars::m_user_data = read_user_data("./assets/data.csv");
        std::cout << "Breakpoint 1: Start: "
                  << "---" << std::endl;
        std::cout << "Transaction Pool: " << Chain::m_transactionPool.size() << std::endl;

        time_t now = time(0);
        std::string timestamp = ctime(&now);
        // globalVars::j_request = {
        //     {"method", "GET"},
        //     {"query", "get_pool"},
        // };
        // if (Chain::noNodes > 1)
        // {
        //     TcpClient m_client = TcpClient(globalVars::OTHER_SERVER_IP, globalVars::OTHER_SERVER_PORT);
        //     m_client.sendQuery(globalVars::j_request.dump());
        //     globalVars::response = m_client.receiveResponse();
        //     // check if the response is valid
        //     std::cout << "Response: " << globalVars::response << std::endl;
        //     if (globalVars::response != "")
        //     {
        //         std::cout << "Response received!" << std::endl;
        //         globalVars::j_response = json::parse(globalVars::response);
        //         std::cout << globalVars::j_response.dump() << std::endl;
        //         if (globalVars::j_response["status_code"] == "200")
        //         {
        //             std::cout << "Transaction pool received!" << std::endl;
        //             json j_temp = globalVars::j_response["transactions"];
        //             std::cout << j_temp.dump() << std::endl;
        //             // add the trans to globalVars::m_transactionPool
        //             Chain::m_transactionPool.clear();
        //             for (auto it = j_temp.begin(); it != j_temp.end(); ++it)
        //             {
        //                 std::cout << it->dump() << std::endl;
        //                 std::string trans = it->dump();
        //                 json j2_temp = json::parse(trans);
        //                 Transaction transaction = Transaction(j2_temp);
        //                 Chain::m_transactionPool.push_back(transaction);
        //             }
        //         }
        //     }
        //     m_client.closeClient();
        // }

        if (Chain::m_transactionPool.size() == 4)
        {
            std::string minerPKey = selectPublicKey();
            std::cout << "Miner: " << minerPKey << std::endl;
            if (globalVars::global_user->public_key == minerPKey)
            {
                std::cout << "You are the lucky one!" << std::endl;
                // mine the block
                // this sends the query to get the latest chain from other nodes
                globalVars::j_request = {
                    {"method", "GET"},
                    {"query", "get_chain"},
                };
                if (Chain::noNodes > 1)
                {
                    TcpClient m_client = TcpClient(globalVars::OTHER_SERVER_IP, globalVars::OTHER_SERVER_PORT);
                    m_client = TcpClient(globalVars::OTHER_SERVER_IP, globalVars::OTHER_SERVER_PORT);
                    m_client.sendQuery(globalVars::j_request.dump());
                    globalVars::response = m_client.receiveResponse();
                    globalVars::j_response = json::parse(globalVars::response);
                    std::cout << "Response: " << globalVars::response << std::endl;
                    std::string blockchain_data = globalVars::j_response["chain"].get<std::string>();
                    Blockchain tempChain(0);
                    tempChain.replaceChain(json::parse(blockchain_data));
                    std::cout << "Status" << std::endl;
                    if (globalVars::j_response["status_code"] == "200")
                    {
                        std::cout << "inside the if" << std::endl;
                        if (Chain::BIBLIOCHAIN.getLatestBlock().getHash() != tempChain.getLatestBlock().getHash())
                        {
                            Chain::BIBLIOCHAIN.replaceChain(json::parse(blockchain_data));
                        }
                        else
                        {
                            // code
                        }
                        std::vector<std::string> transQuery;
                        for (auto it = Chain::m_transactionPool.begin(); it != Chain::m_transactionPool.end(); ++it)
                        {
                            transQuery.push_back(it->representation());
                        }
                        MerkleTree m_trans = MerkleTree(transQuery);
                        Chain::BIBLIOCHAIN.addBlock(Chain::BIBLIOCHAIN.getLatestBlock().getHash(), timestamp, globalVars::global_user->public_key, m_trans.root_hash(), Chain::m_transactionPool);
                        Chain::m_transactionPool.clear();

                        // if the error occurs during block mining, it's probably because of the following code

                        globalVars::j_request = {
                            {"method", "POST"},
                            {"query", "add_block"},
                            {"block", Chain::BIBLIOCHAIN.getLatestBlock().toJson()},
                        };
                        // TcpClient m_client = TcpClient(globalVars::OTHER_SERVER_IP, globalVars::OTHER_SERVER_PORT);
                        m_client.sendQuery(globalVars::j_request.dump());
                        globalVars::response = m_client.receiveResponse();
                        globalVars::j_response = json::parse(globalVars::response);
                        if (globalVars::j_response["status_code"] == "200")
                        {
                            std::cout << "Block added!" << std::endl;
                        }
                        else
                        {
                            std::cout << "Error adding block!" << std::endl;
                        }

                        sleep(5);
                        std::cout << "Block mined successfully!" << std::endl;
                    }
                    m_client.closeClient();
                }
                else
                {
                    std::vector<std::string> transQuery;
                    for (auto it = Chain::m_transactionPool.begin(); it != Chain::m_transactionPool.end(); ++it)
                    {
                        transQuery.push_back(it->representation());
                    }
                    MerkleTree m_trans = MerkleTree(transQuery);
                    Chain::BIBLIOCHAIN.addBlock(Chain::BIBLIOCHAIN.getLatestBlock().getHash(), timestamp, globalVars::global_user->public_key, m_trans.root_hash(), Chain::m_transactionPool);
                    Chain::m_transactionPool.clear();

                    sleep(5);
                    std::cout << "Block mined successfully!" << std::endl;
                }
            }
            else
            {
                // wait for the other miner to mine the block
                // auto start_time = std::chrono::high_resolution_clock::now();
                while (!Chain::m_transactionPool.size() == 0)
                {
                    std::cout << "Waiting for the block to be mined..." << std::endl;
                    sleep(1);
                }
            }
        }

        if (Chain::m_transactionPool.size() < 4)
        {
            ifstream smartContract("./src/blockchain/SmartContract.cpp");
            std::string textContract;
            if (!smartContract.is_open())
            {
                std::cout << "Error opening file" << std::endl;
                exit(1);
            }
            std::string line;
            while (getline(smartContract, line))
            {
                textContract += line;
            }
            smartContract.close();
            if (sha256(textContract) == Chain::BIBLIOCHAIN.getBlock(0).getPreviousHash())
            {
                std::cout << "Smart contract is intact!" << std::endl;
                // if required get the chain
                globalVars::j_request = {
                    {"method", "GET"},
                    {"query", "get_chain"},
                };
                // globalVars::client.sendQuery(globalVars::j_request.dump());
                // globalVars::response = globalVars::client.receiveResponse();
                // globalVars::j_response = json::parse(globalVars::response);
                // if (globalVars::j_response["status_code"] == "200")
                // {
                //     json j_temp = globalVars::j_response["chain"];
                //     if (Chain::BIBLIOCHAIN.getLatestBlock().getHash() != tempChain.getLatestBlock().getHash())
                //     {
                //         Chain::BIBLIOCHAIN.replaceChain((globalVars::j_response["chain"]));
                //     }
                //     else
                //     {
                //         // code
                //     }
                // }
                // else
                // {
                //     std::cout << "Error getting the chain!" << std::endl;
                //     exit(1);
                // }
                std::string book_hash, data_hash;
                // std::cout << "Getting the hashes..." << std::endl;
                if (Chain::m_transactionPool.size() == 0 && Chain::BIBLIOCHAIN.getLength() >= 1)
                {
                    // here we get the last block from the chain
                    // std::cout << "Getting the last block from the chain..." << std::endl;
                    Block tempBlock = Chain::BIBLIOCHAIN.getLatestBlock();
                    std::vector<Transaction> tempPool = tempBlock.getTransaction();
                    // get the last transaction
                    Transaction tempTrans = tempPool.back();
                    book_hash = tempTrans.getUpdatedBookHash();
                    data_hash = tempTrans.getUpdatedCertHash();
                }
                else if (Chain::m_transactionPool.size() > 0)
                {
                    // std::cout << "Getting the last transaction from the pool..." << std::endl;
                    Transaction tempTrans = Chain::m_transactionPool.back();
                    book_hash = tempTrans.getUpdatedBookHash();
                    data_hash = tempTrans.getUpdatedCertHash();
                }
                std::cout << "Verifying the hashes..." << std::endl;
                std::ifstream bookFile("./assets/book.csv");
                std::ifstream dataFile("./assets/data.csv");
                if (!bookFile.is_open() || !dataFile.is_open())
                {
                    std::cout << "Error opening file" << std::endl;
                    exit(1);
                }
                // std::cout << "Reading the files..." << std::endl;
                std::string _data = "";
                std::string data_line = "";
                std::string _book = "";
                std::string book_line = "";
                // std::cout << "Calculating the hashes..." << std::endl;
                while (getline(dataFile, data_line))
                {
                    _data += data_line;
                }
                while (getline(bookFile, book_line))
                {
                    _book += book_line;
                }
                bookFile.close();
                dataFile.close();

                std::cout << "Breakpoint Transaction : Check transaction size." << std::endl;
                std::cout << "Size" << Chain::m_transactionPool.size() << std::endl;
                if (Chain::m_transactionPool.size() > 0 || (Chain::m_transactionPool.size() == 0 && Chain::BIBLIOCHAIN.getLength() >= 1))
                {
                    std::cout << data_hash << std::endl;
                    std::cout << book_hash << std::endl;
                    std::cout << sha256(_data) << std::endl
                              << sha256(_book) << std::endl;

                    if (((sha256(_data) != data_hash) || (sha256(_book) != book_hash)) && Chain::noNodes > 1)
                    // if (flag && flag2)
                    {
                        std::cout << "Data has been changed from original one..." << std::endl;
                        globalVars::j_request = {
                            {"method", "GET"},
                            {"query", "get_data"},
                            {"data", {"newNode", false}},
                        };
                        TcpClient m_client = TcpClient(globalVars::OTHER_SERVER_IP, globalVars::OTHER_SERVER_PORT);
                        m_client.sendQuery(globalVars::j_request.dump());
                        globalVars::response = m_client.receiveResponse();
                        globalVars::j_response = json::parse(globalVars::response);
                        std::cout << "Data has been updated..." << std::endl;
                        std::cout << globalVars::j_response << std::endl;
                        std::string user_data = globalVars::j_response["user"].get<std::string>();
                        std::string book_data = globalVars::j_response["book"].get<std::string>();
                        // blockchain data is already in json string format
                        std::string blockchain_data = globalVars::j_response["chain"].get<std::string>();
                        // open the book.csv and data.csv to write the data
                        std::ofstream user_file("./assets/data.csv");
                        std::ofstream book_file("./assets/book.csv");
                        if (!user_file.is_open())
                        {
                            std::cout << "Error opening file" << std::endl;
                            exit(1);
                        }
                        if (!book_file.is_open())
                        {
                            std::cout << "Error opening file" << std::endl;
                            exit(1);
                        }
                        // write the data to the file
                        user_file << user_data;
                        book_file << book_data;
                        Chain::BIBLIOCHAIN.replaceChain(json::parse(blockchain_data));
                        // close the file
                        user_file.close();
                        book_file.close();
                        m_client.closeClient();
                    }
                    else
                    {
                        std::cout << "Data is ok." << std::endl;
                    }
                }
                std::cout << globalVars::QUERY << std::endl;
                std::string QUERY_STR = globalVars::QUERY;
                std::cout << "Breakpoint 4: Query: " << QUERY_STR << std::endl;

                // starts here
                if ((QUERY_STR.substr(0, 3) == "GET") | (QUERY_STR.substr(0, 6) == "DONATE") | (QUERY_STR.substr(0, 4) == "GIVE"))
                {
                    std::cout << "Breakpoint 5.1: Query: " << QUERY_STR << std::endl;
                    QUERY_STR += "|" + globalVars::global_user->public_key + "|" + timestamp;
                    std::vector<int> encodedQuery = globalVars::global_user->encoder(QUERY_STR);
                    std::cout << QUERY_STR << std::endl;
                    for (auto res : encodedQuery)
                    {
                        std::cout << res;
                    }
                    std::cout << std::endl;
                    std::vector<std::string> decrypted = SmartContract::getqueryfromenc(encodedQuery);
                    std::cout << "Breakpoint 5.3: Decrypted Query: " << decrypted[0] << std::endl;
                    bool isvalid = SmartContract::validate_trans(decrypted);
                    std::cout << "isvalid: " << isvalid << std::endl;
                    std::cout << "TRANSACTION: " << QUERY_STR << std::endl;
                    if (isvalid)
                    {
                        std::cout << "Is Valid" << std::endl;
                        SmartContract::update_files(decrypted);
                        Transaction t1{encodedQuery};
                        std::cout << t1.toJson().dump() << std::endl;
                        Chain::m_transactionPool.push_back(t1);
                        if (Chain::noNodes > 1)
                        {
                            std::cout << "Post Transaction to other" << std::endl;
                            TcpClient m_client = TcpClient(globalVars::OTHER_SERVER_IP, globalVars::OTHER_SERVER_PORT);
                            std::cout << "Post Transaction to other" << std::endl;

                            globalVars::j_request = {
                                {"method", "POST"},
                                {"query", "add_transaction"},
                                {"type", "library"},
                                {"transaction", t1.toJson()},
                            };
                            m_client.sendQuery(globalVars::j_request.dump());
                            globalVars::response = m_client.receiveResponse();
                            globalVars::j_response = json::parse(globalVars::response);
                            std::cout << globalVars::j_response["message"].get<std::string>() << std::endl;

                            // ifstream data_file("./assets/data.csv"), book_file("./assets/book.csv");
                            // if (!data_file.is_open() || !book_file.is_open())
                            // {
                            //     throw runtime_error("file not found");
                            // }
                            // ostringstream book_str;
                            // ostringstream data_str;
                            // book_str << book_file.rdbuf();
                            // data_str << data_file.rdbuf();
                            // std::string query_temp = book_str.str() + "|BIBLIOCHAIN|" + data_str.str();
                            // data_file.close();
                            // book_file.close();
                            m_client.closeClient();
                        }
                        // globalVars::m_user_data = read_user_data("./assets/data.csv");
                        // globalVars::m_book_data = read_book_data("./assets/book.csv");
                    }
                    else if (QUERY_STR != "")
                    {

                        std::cerr << "This is not a valid transaction" << std::endl;
                        stateVars::error_message = "This is not a valid transaction";
                        stateVars::show_error = true;
                    }
                    std::memset(globalVars::QUERY, 0, sizeof(globalVars::QUERY));
                    QUERY_STR = "";
                    // ends here
                }
                else if (QUERY_STR != "")
                {

                    std::cerr
                        << "Please insert the query in the format descripted below..." << std::endl;
                    stateVars::error_message = "Please insert the query in the format descripted below...";
                    stateVars::show_error = true;
                }

                std::cout << "Breakpoint 7: Query: " << QUERY_STR << std::endl;
            }
            else
            {
                std::cout << "Smart contract has been tampered with wrong one!" << std::endl;
                stateVars::error_message = "Smart contract has been tampered with wrong one!\nExiting...";
                stateVars::show_error = true;
                sleep(3);
                std::cout << "Exiting..." << std::endl;
                exit(1);
            }
        }
        else
        {
            std::cout << "Transaction pool is full!" << std::endl;
        }
        sleep(1);
    }
}
