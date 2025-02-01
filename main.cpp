/*
 *  Author      : Reese
 *  Created On  : 2025-02-01 18:45
 *  Description :
 */

#include <iostream>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,abm,bmi2")

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {

    return 0;
}