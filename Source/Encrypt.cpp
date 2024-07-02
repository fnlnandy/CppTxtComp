#include "Common.hpp"

std::string transitionEncryption(const std::string &prevState)
{
    //! @brief LUT for the encryption.
    const Dict<char, char> encryptionDict =
        {
            {'a', 'z'},
            {'b', 'y'},
            {'c', 'x'},
            {'d', 'w'},
            {'e', 'v'},
            {'f', 'u'},
            {'g', 't'},
            {'h', 's'},
            {'i', 'r'},
            {'j', 'q'},
            {'k', 'p'},
            {'l', 'o'},
            {'m', 'n'},
        };
    std::string newState = prevState;

    for (uint i = 0; i < newState.length(); ++i)
    {
        for (auto it = encryptionDict.begin(); it != encryptionDict.end(); ++it)
        {
            if (it->first == newState[i])
            {
                newState[i] = it->second;
                break;
            }
            else if (it->second == newState[i])
            {
                newState[i] = it->first;
                break;
            }
        }
    }

    return newState;
}

std::string parseFileContent(const std::string &filePath)
{
    std::ifstream src = std::ifstream(filePath);

    if (!src.is_open())
    {
        ERROR("Unable to open file: '" << filePath << "'. Aborting.");
    }

    std::stringstream ss = {};
    ss << src.rdbuf();

    return ss.str();
}