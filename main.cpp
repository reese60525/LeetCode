/*
 *  Author      : Reese
 *  Created On  : 2024-12-25 13:01
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