/*
 *  Author      : Reese
 *  Created On  : 2025-01-10 00:06
 *  Description :
 */

#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {

    return 0;
}