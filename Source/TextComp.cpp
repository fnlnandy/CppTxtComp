#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#include "TextComp.hpp"
#include "BinContainer.hpp"

static void compressFile(const std::string &filePath);
static void decompressFile(const std::string &filePath);

extern std::string parseFileContent(const std::string &filePath);
extern BinContainer compressFileContent(const std::string &decodedText);
extern std::string decompressBinaryToText(BinContainer &encodedData);

int main(int argc, char **argv)
{
    argc--, argv++;

    if (argc < 2)
    {
        std::printf("Usage: textcomp [-c|-d] FILE\n");
        exit(0);
    }

    bool isCompMode = true;
    std::string fileName = {};

    for (int i = 0; i < argc; i++)
    {
        if (std::strncmp(argv[i], "-c", 2) == 0)
            isCompMode = true;
        else if (std::strncmp(argv[i], "-d", 2) == 0)
            isCompMode = false;
        else if (std::strncmp(argv[i], "-", 1) != 0)
            fileName = argv[i];
    }

    // Theoritically should never happen.
    if (fileName.empty())
    {
        std::cerr << "[ERROR]: No filename provided. Aborting.\n";
        std::exit(1);
    }

    if (isCompMode)
        compressFile(fileName);
    else
        decompressFile(fileName);

    return 0;
}

static void compressFile(const std::string &filePath)
{
    std::ifstream compressed = std::ifstream(filePath);

    if (!compressed.is_open())
    {
        std::cerr << "[ERROR]: Unable to open file '" << filePath << "' for reading. Aborting.\n";
        std::exit(1);
    }

    std::string decompressedContent = parseFileContent(filePath);
    BinContainer compressedContent = compressFileContent(decompressedContent);
    std::string destFileName = {};

    std::printf("Input the destination filename: ");
    std::cin >> destFileName;

    bool successInWriting = compressedContent.writeIntoFile(destFileName);

    if (!successInWriting)
    {
        std::cerr << "[ERROR]: Unable to write into file '" << destFileName << "'. Aborting.\n";
        std::exit(1);
    }

    std::printf("[INFO]: '%s' has been compressed into: '%s'.\n", filePath.c_str(), destFileName.c_str());
}

static void decompressFile(const std::string &filePath)
{
    BinContainer compressedContent = {};
    bool successInReading = compressedContent.readFromFile(filePath);

    if (!successInReading)
    {
        std::cerr << "[ERROR]: Unable to read from file: '" << filePath << "'. Aborting.\n";
        std::exit(1);
    }

    std::string decompressedText = decompressBinaryToText(compressedContent);
    std::string destFileName = {};

    std::printf("Enter the destination filename: ");
    std::cin >> destFileName;

    std::ofstream destFileStream = std::ofstream(destFileName);

    if (!destFileStream.is_open())
    {
        std::cerr << "[ERROR]: Unable to open file '" << destFileName << "' for writing. Aborting.\n";
        std::exit(1);
    }

    destFileStream.write(decompressedText.c_str(), decompressedText.length());
    destFileStream.flush();

    std::printf("[INFO]: '%s' has been decompressed into '%s'.\n", filePath.c_str(), destFileName.c_str());
}