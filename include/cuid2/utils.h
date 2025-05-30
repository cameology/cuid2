#ifndef CUID2_UTILS_H
#define CUID2_UTILS_H


#include <string>
#include <random>
#include <vector>

#include <openssl/evp.h>

#include <cuid2/contants.h>


namespace cuid2 {
    /**
     *  @brief Get a random alpha character in lowercase
     *  @return `Char` lowercase alpha
     */
    char alpha();

    /**
     *  @brief Get incremented random int
     *  @return `Int` in random
     */
    int counter();

    /**
     *  @brief Get time as an integer number of nanoseconds since the epoch
     *  @return `Int` of nanoseconds since epoch
     */
    int epochInNano();

    /**
     *  @brief Get system/machine fingerprinting
     *  @param `input std::string` An optional parameter that contains data to be included in the fingerprint.
     *  @return `std::string` The hashed value of the input combined with
     *              PID, System Info, and Environment Variables
     */
    std::string fingerprint(const std::string& input = "", const int& length = cuid2::BIG_LENGTH);
    
    /**
     *  @brief Creates a random string of specified length using a base36 encoding
     *  @param `length int` The desired length of the output string (defaults to 4)
     *  @return `std::string` The generated random string
     */
    std::string entropy(const int& length = 4);
    
    /**
     *  @brief Creates a hash value for a given string using the SHA-512 algorithm (prefers SHA3) and returns
     *          it in base36 encoding format after dropping the first character.
     *  @param `input std::string` text or string need to be hashed
     *  @return `std::string` Base36 encoding of the SHA-512 hash of the input
     */
    std::string hash(const std::string& input);
    
    /**
     *  @brief Encodes a positive integer into a base36 string
     *  @param `input BigNum` to be encoded as a base36 string.
     *          The `input` must in BigNum value typed in string.
     *  @return `std::string` A string that represents the base36 encoded input integer.
     *
     */
    std::string base36Encode(const std::string& input);
    
    /**
     *  @brief Hash the given string using SHA3-512 algorithm
     *  @param `input std::string` text or string need to be hashed
     *  @return `std::vector<unsigned char>` Raw bytes of unsigned char wrapped in vector
     */
    std::vector<unsigned char> sha512(const std::string& input);
}

#endif