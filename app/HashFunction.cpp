#include "HashFunction.hpp"

unsigned int hashFunction(const std::string& key)
{
    int result = 0;
    for (int n = 0; n < key.size(); n++)
    {
        result = 31*result + key[n];
    }
    return result;
}