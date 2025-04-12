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
    std::string                 fingerprint(std::string input = "");
    std::string                 entropy(int length);
    std::string                 hash(std::string input);
    BIGNUM*                     toBignum(int value);
    std::string                 base36Encode(const BIGNUM* input);
    std::vector<unsigned char>  sha512(const std::string& input);
}

#endif