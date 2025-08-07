//
// Created by ryan on 7/22/25.
//

#include <iostream>

#include "src/Server.h"
#include "src/UPS.h"

int main() {
    nut::Server server;

    server.connect();

    const std::vector<nut::UPS> list = server.get_ups_list();

    const nut::UPS dummy_ups(server.get_ups("dummy"));

    std::cout << dummy_ups.get_description() << std::endl;
    std::cout << dummy_ups.get_charge() << std::endl;
    std::cout << dummy_ups.get_load() << std::endl;
    std::cout << dummy_ups.get_model() << std::endl;
    std::cout << dummy_ups.get_serial() << std::endl;

    for (const auto & i : dummy_ups.get_command_list()) {
        std::cout << i << std::endl;
    }

    for (const auto & i : dummy_ups.get_command_list()) {
        std::cout << i << std::endl;
    }

    return 0;
}
