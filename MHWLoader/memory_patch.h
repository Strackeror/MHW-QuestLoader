#pragma once
#include <string>
#include <vector>

typedef unsigned char byte;

std::vector<byte*> scanmem(const std::vector<byte>& bytes);

std::vector<byte*> scanmem(const std::vector<byte>& bytes,
                           const std::vector<byte>& mask);

std::vector<byte> parseHex(const std::string& aob);

std::tuple<std::vector<byte>, std::vector<byte>> parseBinary(
    const std::string& aob);
