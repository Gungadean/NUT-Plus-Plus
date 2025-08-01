// Represents instance of an UPS on the NUT server.
//
// Copyright (C) 2025 NUT-Plus-Plus <nutpp+ryanjhuston@comcast.net>
//
// This project is a C++ wrapper for the Network UPS Tools (NUT) library.
// It is not affiliated with the official NUT project.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#include "UPS.h"

#include <iostream>
#include <ostream>

namespace nut {

    UPS::UPS(const Connection& connection, const char* ups_name, const char* ups_description) :
        connection(connection),
        ups_name(ups_name),
        ups_description(ups_description)
    {
        std::cout << "UPS " << ups_name << " created." << std::endl;
    }

    UPS::~UPS() = default;

    std::string& UPS::get_ups_name() {
        return ups_name;
    }

    std::string& UPS::get_ups_description() {
        return ups_description;
    }

    double UPS::get_charge() {

    }

    double UPS::get_load() {

    }

    std::string UPS::get_model() {

    }

    std::chrono::seconds UPS::get_runtime() {

    }

    std::string UPS::get_serial() {

    }
} // nut