#include "HashMap.hpp"
#include "HandleInputOutput.hpp"

int main()
{
    HashMap hm = HashMap();
    bool debug = false;
    bool running = true;

    while (running)
    {
        std::string command;
        std::getline(std::cin, command);
        std::stringstream stream;
        std::string word1;
        std::string word2;
        std::string word3;
        std::string word4;

        stream << command;
        stream >> word1 >> word2 >> word3 >> word4;

        if (word4 != "")
        {
            invalid();
        }

        else if ((word1 == "MAX") and (word2 == "BUCKET") and (word3 == "SIZE"))
        {
            if (debug == true)
            {
                std::cout << hm.maxBucketSize() << std::endl;
            }
            else
            {
                invalid();
            }
        }

        else if (word1 == "CREATE")
        {
            if ((word2 != "") and (word3 != ""))
            {
                int before = hm.size();
                hm.add(word2, word3);
                int after = hm.size();
                if (before == after)
                {
                    std::cout << "EXISTS" << std::endl;
                }
                else
                {
                    std::cout << "CREATED" << std::endl;
                }
            }
            else
            {
                invalid();
            }
        }

        else if (word1 == "LOGIN")
        {
            if ((word2 == "COUNT") and (word3 == ""))
            {
                if (debug == true)
                {
                    std::cout << hm.size() << std::endl;
                }
                else
                {
                    invalid();
                }
            }
            else if ((word2 != "") and (word3 != ""))
            {
                if (hm.value(word2) == word3)
                {
                    std::cout << "SUCCEEDED" << std::endl;
                }
                else
                {
                    std::cout << "FAILED" << std::endl;
                }
            }
        }

        else if (word1 == "REMOVE")
        {
            if (word2 != "" and word3 == "")
            {
                int before = hm.size();
                hm.remove(word2);
                int after = hm.size();
                if (before == after)
                {
                    std::cout << "NONEXISTENT" << std::endl;
                }
                else
                {
                    std::cout << "REMOVED" << std::endl;
                }
            }
            else
            {
                invalid();
            }
        }

        else if (word1 == "CLEAR")
        {
            if (word2 == "" and word3 == "")
            {
                hm = HashMap();
            }
            else
            {
                invalid();
            }
        }

        else if (word1 == "QUIT")
        {
            if (word2 == "" and word3 == "")
            {
                running = false;
                std::cout << "GOODBYE" << std::endl;
            }
            else
            {
                invalid();
            }
        }

        else if (word1 == "DEBUG")
        {
            if (word2 == "ON" and word3 == "")
            {
                if (debug == true)
                {
                    std::cout << "ON ALREADY" << std::endl;
                }
                else 
                {
                    debug = true;
                    std::cout << "ON NOW" << std::endl;
                }
            }
            else if (word2 == "OFF" and word3 == "")
            {
             if (debug == false)
                {
                    std::cout << "OFF ALREADY" << std::endl;
                }
                else 
                {
                    debug = false;
                    std::cout << "OFF NOW" << std::endl;
                }
            }
            else
            {
                invalid();
            }
        }

        else if (word1 == "BUCKET")
        {
            if (word2 == "COUNT" and word3 == "")
            {
                if (debug == true)
                {
                    std::cout << hm.bucketCount() << std::endl;
                }
                else
                {
                    invalid();
                }
            }
            else
            {
                invalid();
            }
        }

        else if (word1 == "LOAD")
        {
            if (word2 == "FACTOR" and word3 == "")
            {
                if (debug == true)
                {
                    std::cout << hm.loadFactor() << std::endl;
                }
                else
                {
                    invalid();
                }
            }
            else
            {
                invalid();
            }
        }

        else
        {
            invalid();
        }
    }




    return 0;
}

