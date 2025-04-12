#include "cuid2/utils.h"

#include <random>
#include <cmath>
#include <vector>
#include <chrono>
#include <stdexcept>

#include <unistd.h>
#include <sys/utsname.h>
#include <cstdlib>

#include <openssl/evp.h>
#include <openssl/sha.h>

#include "cuid2/contants.h"



std::mt19937& cuid2::random() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    return gen;
}


char cuid2::alpha() {
    std::uniform_int_distribution distribute(0, 25);

    return 'a' + distribute(cuid2::random());
}


int cuid2::counter() {
    return std::floor(cuid2::random()() * cuid2::INITIAL_COUNT_MAX);
}


int cuid2::epochInNano() {
    auto now        = std::chrono::system_clock::now();
    auto duration   = now.time_since_epoch();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}


std::string cuid2::fingerprint(std::string input) {
    std::string fingerprint = input;

    if (input == "") {
        // Process ID
        pid_t process_id = getpid();
        fingerprint += std::to_string(process_id) + "|";

        // System Info
        struct utsname sys_info;
        if (uname(&sys_info) == 0) {
            fingerprint += std::string(sys_info.sysname) + "|";
            fingerprint += std::string(sys_info.nodename) + "|";
            fingerprint += std::string(sys_info.release) + "|";
            fingerprint += std::string(sys_info.version) + "|";
            fingerprint += std::string(sys_info.machine) + "|";
        }

        // Take PATH variable
        const char* path_env = getenv("PATH");
        if (path_env != nullptr) {
            fingerprint += std::string(path_env);
        }
    }

    fingerprint = cuid2::hash(fingerprint + cuid2::entropy(cuid2::BIG_LENGTH));
    return fingerprint.substr(0, cuid2::BIG_LENGTH);
}


std::string cuid2::entropy(int length = 4) {
    std::string entropy = "";

    if (length < 1) {
        throw std::runtime_error("Cannot create entropy without a length >= 1");
    }

    while (entropy.length() < length) {
        entropy += std::floor(cuid2::random()() * 36);
    }
    
    return entropy;
}


std::string cuid2::hash(std::string input) {
    auto hash       = cuid2::sha512(input);
    auto hashedNum  = BN_bin2bn(hash.data(), hash.size(), nullptr);

    if (!hashedNum) {
        throw std::runtime_error("Failed to convert hash to integer");
    }

    auto base36 = cuid2::base36Encode(hashedNum);
    return base36.substr(1, base36.size() - 1);
}


std::string cuid2::base36Encode(const BIGNUM* input) {
    if (BN_is_negative(input) || BN_is_zero(input)) {
        throw std::runtime_error("Cannot encode negative integers");
    }

    std::string encoded    = "";
    std::string alphaNum   = "0123456789abcdefghijklmnopqrstuvwxyz";

    // BIGNUM Vars
    BN_CTX* ctx         = BN_CTX_new();
    BIGNUM* length      = BN_new();
    BIGNUM* number      = BN_dup(input);
    BIGNUM* quotient    = BN_new();
    BIGNUM* remainder   = BN_new();

    // Fill them value
    BN_set_word(length, alphaNum.size());

    while (!BN_is_zero(number)) {
        BN_div(quotient, remainder, number, length, ctx);

        // Get remainder value
        int mod = BN_get_word(remainder);
        if (mod < 0 || mod >= (int) alphaNum.size()) {
            throw std::runtime_error("Modulus out of range");
        }
        
        // Prepend character
        encoded = alphaNum[mod] + encoded;
        
        // update number
        BN_copy(number, quotient);
    }

    // Free memories
    BN_CTX_free(ctx);
    BN_free(length);
    BN_free(number);
    BN_free(quotient);
    BN_free(remainder);

    return encoded;
}


std::vector<unsigned char> cuid2::sha512(const std::string& input) {
    std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
    unsigned int len = 0;

    EVP_MD_CTX* context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, EVP_sha3_512(), nullptr);
    EVP_DigestUpdate(context, input.c_str(), input.size());
    EVP_DigestFinal_ex(context, hash.data(), &len);

    hash.resize(len);
    return hash;
}


BIGNUM* cuid2::toBignum(int value) {
    BIGNUM* bignum = BN_new();
    BN_set_word(bignum, abs(value));

    return bignum;
}
