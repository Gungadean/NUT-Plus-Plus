//
// Created by ryan on 7/22/25.
//

#include <iostream>

#include "src/Connection.h"
#include "src/UPS.h"

int main() {
    nut::Connection connection;

    connection.connect();

    const std::vector<nut::UPS> list = connection.get_ups_list();

    const nut::UPS test(connection.get_ups("dummy"));

    std::cout << test.get_ups_description() << std::endl;
    std::cout << test.get_charge() << std::endl;
    std::cout << test.get_load() << std::endl;
    std::cout << test.get_model() << std::endl;
    std::cout << test.get_serial() << std::endl;

    for (const auto & i : test.get_cmd_list()) {
        std::cout << i << std::endl;
    }

    for (const auto & i : test.get_var_list()) {
        std::cout << i << std::endl;
    }

    return 0;
}
