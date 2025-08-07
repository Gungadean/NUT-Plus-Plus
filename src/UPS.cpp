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

#include <string>
#include <ostream>
#include <utility>

#include "Server.h"

namespace nut {

    UPS::UPS(const Server& server, std::string ups_name, std::string ups_description) :
        m_server(server),
        m_ups_name(std::move(ups_name)),
        m_ups_description(std::move(ups_description))
    {}

    UPS::~UPS() = default;

    const std::string& UPS::get_name() const {
        return m_ups_name;
    }

    const std::string& UPS::get_description() const {
        return m_ups_description;
    }

    double UPS::get_charge() const {
        return m_server.get_var_double(get_name(), "battery.charge");
    }

    double UPS::get_load() const {
        return m_server.get_var_double(get_name(), "ups.load");
    }

    std::string UPS::get_model() const {
        return m_server.get_var(get_name(), "ups.model");
    }

    std::string UPS::get_serial() const {
        return m_server.get_var(get_name(), "device.serial");
    }

    std::string UPS::get_variable(const std::string& var_name) const {
        return m_server.get_var(get_name(), var_name);
    }

    std::vector<std::string> UPS::get_command_list() const {
        std::vector<std::string> cmds;
        std::vector<std::vector<std::string>> raw_list = m_server.get_var_list(get_name(), "CMD");

        for (std::vector<std::string>& answer_list : raw_list) {
            cmds.emplace_back(answer_list.at(2));
        }

        return cmds;
    }

    std::vector<std::string> UPS::get_variables_list() const {
        std::vector<std::string> vars;
        std::vector<std::vector<std::string>> raw_list = m_server.get_var_list(get_name(), "VAR");

        for (std::vector<std::string>& answer_list : raw_list) {
            vars.emplace_back(answer_list.at(2));
        }

        return vars;
    }
} // nut