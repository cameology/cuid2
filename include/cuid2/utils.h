#ifndef CUID2_UTILS_H
#define CUID2_UTILS_H


#include <string>
#include <random>
#include <vector>

#include <openssl/evp.h>


namespace cuid2 {
    char                        alpha();
    int                         counter();
    int                         epochInNano();
    std::mt19937&               random();
    std::string                 fingerprint(const std::string& input = "");
    std::string                 entropy(const int& length = 4);
    std::string                 hash(const std::string& input);
    std::string                 base36Encode(const std::string& input);
    std::vector<unsigned char>  sha512(const std::string& input);
}

#endif