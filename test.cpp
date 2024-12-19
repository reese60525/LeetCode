/******************************************
 *  File        : test.cpp
 *  Author      : Reese
 *  Created On  : 2024-12-19 11:40
 *  Description :
 ******************************************/

#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {

    return 0;
}