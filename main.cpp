/*
 *  Author      : Reese
 *  Created On  : 2025-01-13 01:25
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