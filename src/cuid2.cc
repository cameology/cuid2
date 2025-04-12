#include "cuid2/cuid2.h"

#include <string>

#include "cuid2/utils.h"
#include "cuid2/contants.h"



std::string cuid2::createId() {
    std::string cuid2    = "";

    cuid2 += cuid2::alpha();
    cuid2 += cuid2::hash(""
            + cuid2::base36Encode(cuid2::toBignum(cuid2::epochInNano()))    // base36 time
            + cuid2::entropy(cuid2::DEFAULT_LENGTH)                         // salt
            + cuid2::base36Encode(cuid2::toBignum(cuid2::counter()))        // base36 counter
            + cuid2::fingerprint()                                          // fingerprint
        );

    return cuid2.substr(1, cuid2::DEFAULT_LENGTH);
}
