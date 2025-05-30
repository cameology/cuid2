#ifndef CUID2_H
#define CUID2_H


#include <string>

#include "cuid2/constant.h"


namespace cuid2 {
    std::string createId(const int& length = cuid2::DEFAULT_LENGTH);
}

#endif