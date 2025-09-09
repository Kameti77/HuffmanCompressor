#ifndef ICOMPRESSOR_H
#define ICOMPRESSOR_H

#include <string>

class ICompressor {
public:
    virtual ~ICompressor() = default;

    // Pure virtual methods for polymorphism
 
    // Compress input file into output file
    virtual void compress(const std::string& inputFile, const std::string& outputFile) = 0;

    // Decompress input file into output file
    virtual void decompress(const std::string& inputFile, const std::string& outputFile) = 0;
};

#endif

