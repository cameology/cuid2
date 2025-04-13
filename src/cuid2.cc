#include "cuid2/cuid2.h"

#include <string>
#include <openssl/evp.h>

#include "cuid2/utils.h"
#include "cuid2/contants.h"



std::string cuid2::createId() {
    using namespace std::string_literals;

    auto cuid2      = ""s;
    auto epoch      = BN_new();
    auto counter    = BN_new();

    BN_set_word(epoch, cuid2::epochInNano());
    BN_set_word(counter, cuid2::counter());

    cuid2 += cuid2::alpha();
    cuid2 += cuid2::hash(""
            + cuid2::base36Encode(epoch)                // base36 time
            + cuid2::entropy(cuid2::DEFAULT_LENGTH)     // salt
            + cuid2::base36Encode(counter)              // base36 counter
            + cuid2::fingerprint()                      // fingerprint
        );

    // Free memories
    BN_free(epoch);
    BN_free(counter);

    return cuid2.substr(1, cuid2::DEFAULT_LENGTH);
}
