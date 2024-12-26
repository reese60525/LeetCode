/*
 *  Author      : Reese
 *  Created On  : 2024-12-26 21:11
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