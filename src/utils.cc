#include "cuid2/utils.h"

#include <string>
#include <random>
#include <vector>
#include <chrono>
#include <stdexcept>
#include <unistd.h>

#include <sys/utsname.h>

#include <openssl/evp.h>
#include <openssl/sha.h>

#include "cuid2/contants.h"



std::mt19937& randInt() {
    static auto rd  = std::random_device();
    static auto gen = std::mt19937(rd());

    return gen;
}


char cuid2::alpha() {
    auto distribute = std::uniform_int_distribution(0, 25);

    return 'a' + distribute(randInt());
}


int cuid2::counter() {
    return std::floor(randInt()() * cuid2::INITIAL_COUNT_MAX) + 1;
}


int cuid2::epochInNano() {
    auto now        = std::chrono::system_clock::now();
    auto duration   = now.time_since_epoch();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}


std::string cuid2::fingerprint(const std::string& input) {
    auto fingerprint = input;

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


std::string cuid2::entropy(const int& length) {
    using namespace std::string_literals;

    auto entropy    = ""s;
    auto distribute = std::uniform_int_distribution(0, 25);

    if (length < 1) {
        throw std::runtime_error("Cannot create entropy without a length >= 1");
    }

    while (entropy.length() < length) {
        entropy += cuid2::base36Encode(
            std::to_string(distribute(randInt()))
        );
    }

    return entropy;
}


std::string cuid2::hash(const std::string& input) {
    auto hash   = cuid2::sha512(input);
    auto bin    = BN_bin2bn(hash.data(), hash.size(), nullptr);
    auto dec    = BN_bn2dec(bin);

    auto base36 = cuid2::base36Encode(std::string(dec));

    // Free memories
    BN_free(bin);
    OPENSSL_free(dec);

    return base36.substr(1, base36.size() - 1);
}


std::string cuid2::base36Encode(const std::string& input) {
    using namespace std::string_literals;

    auto encoded    = ""s;
    auto alphaNum   = "0123456789abcdefghijklmnopqrstuvwxyz"s;

    // BIGNUM Vars
    auto ctx         = BN_CTX_new();
    auto length      = BN_new();
    auto number      = BN_new();
    auto quotient    = BN_new();
    auto remainder   = BN_new();

    // Fill them value
    BN_dec2bn(&number, input.c_str());
    BN_set_word(length, alphaNum.size());

    if (BN_is_zero(number)) {
        return "0";
    }

    // Make number always positive
    if (BN_is_negative(number)) {
        BN_set_negative(number, 0);
    }

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
    auto hash    = std::vector<unsigned char>(EVP_MAX_MD_SIZE);
    auto len     = (unsigned int) 0;
    auto context = EVP_MD_CTX_new();

    EVP_DigestInit_ex(context, EVP_sha3_512(), nullptr);
    EVP_DigestUpdate(context, input.c_str(), input.size());
    EVP_DigestFinal_ex(context, hash.data(), &len);

    // Free memory
    EVP_MD_CTX_free(context);
    
    hash.resize(len);
    return hash;
}
