#include "cuid2/cuid2.h"

#include <string>
#include <openssl/evp.h>

#include "cuid2/utils.h"
#include "cuid2/constant.h"



std::string cuid2::createId(const int& length) {
    using namespace std::string_literals;
    
    auto _length = length;
    if (length <= cuid2::MIN_LENGTH) {
        _length = cuid2::MIN_LENGTH;
    }
 
    auto cuid2      = ""s;
    auto epoch      = std::to_string(cuid2::epochInNano());
    auto counter    = std::to_string(cuid2::counter());

    cuid2 += cuid2::alpha();
    cuid2 += cuid2::hash(""
            + cuid2::base36Encode(epoch)                // base36 time
            + cuid2::entropy(_length)                   // salt
            + cuid2::base36Encode(counter)              // base36 counter
            + cuid2::fingerprint()                      // fingerprint
        );

    return cuid2.substr(1, _length);
}
