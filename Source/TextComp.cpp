#include "Common.hpp"

static void compressFile(const std::string &filePath);
static void decompressFile(const std::string &filePath);

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
        ERROR("No filename provided. Aborting.");

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
        ERROR("Unable to open file: '" << filePath << "' for reading. Aborting.");

    std::string decompressedContent = parseFileContent(filePath);
    BinContainer compressedContent = compressFileContent(decompressedContent);
    std::string destFileName = {};

    std::printf("Input the destination filename: ");
    std::cin >> destFileName;

    bool successInWriting = compressedContent.writeIntoFile(destFileName);

    if (!successInWriting)
        ERROR("Unable to write into file: '" << destFileName << "'. Aborting.");

    INFO("'" << filePath << "' has been compressed into: '" << destFileName << "'.");
}

static void decompressFile(const std::string &filePath)
{
    BinContainer compressedContent = {};
    bool successInReading = compressedContent.readFromFile(filePath);

    if (!successInReading)
        ERROR("Unable to read from file: '" << filePath << "'. Aborting.");

    std::string decompressedText = decompressBinaryToText(compressedContent);
    std::string destFileName = {};

    std::printf("Enter the destination filename: ");
    std::cin >> destFileName;

    std::ofstream destFileStream = std::ofstream(destFileName);

    if (!destFileStream.is_open())
        ERROR("Unable to open file: '" << destFileName << "' for writing. Aborting.");

    destFileStream.write(decompressedText.c_str(), decompressedText.length());
    destFileStream.flush();

    INFO("'" << filePath << "' has been compressed into '" << destFileName << "'.");
}