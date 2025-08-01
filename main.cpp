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

    nut::UPS test(connection.get_ups("dummy"));

    std::cout << test.get_ups_description() << std::endl;

    return 0;
}
