# cuid2

CUID2 for C++17. Next generation GUIDs. Collision-resistant ids optimized for 
horizontal scaling and performance.

A port of the [CUID2 reference implementation](https://github.com/paralleldrive/cuid2) 
by [Parallel Drive](https://github.com/paralleldrive) to C++17.

> :memo: Note: Originally taken from https://github.com/overflowdigital before it 
> was unpublished. Thank you to @joshuathompsonlindley for your original contribution!

## What is CUID2?

* Secure: It's not possible to guess the next ID.
* Collision resistant: It's extremely unlikely to generate the same ID twice.
* Horizontally scalable: Generate IDs on multiple machines without coordination.
* Offline-compatible: Generate IDs without a network connection.
* URL and name-friendly: No special characters.

## Why?

For more information on the theory and usage of CUID2, see the 
[following](https://github.com/paralleldrive/cuid2#why).

## Improvements Over CUID

For more information on the improvements of CUID2 over CUID, see the 
[following](https://github.com/paralleldrive/cuid2#improvements-over-cuid).


## Install
```cmake
cmake_minimum_required(VERSION 3.14.0)

# Cuid2 requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    cuid2
    GIT_REPOSITORY https://github.com/cameology/cuid2.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(cuid2)
```

## Usage
```c++
#include <iostream>

#include <cuid2/cuid2.h>


int main() {
    auto id     = cuid2::createId();
    auto id50   = cuid2::createId(50);

    std::cout << id << std::endl;
    std::cout << id50 << std::endl;

    return 0;
}
```

## TODO
- Histogram