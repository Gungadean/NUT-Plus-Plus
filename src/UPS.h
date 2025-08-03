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

#ifndef NUT_PLUS_PLUS_UPS_H
#define NUT_PLUS_PLUS_UPS_H

#include <chrono>
#include <string>
#include <vector>

namespace nut {

    class Connection;

    class UPS {
        private:
            const Connection& m_connection;
            const std::string m_ups_name;
            const std::string m_ups_description;
        public:
            UPS(const Connection& connection, std::string ups_name, std::string ups_description);
            ~UPS();

            [[nodiscard]] const std::string& get_ups_name() const;
            [[nodiscard]] const std::string& get_ups_description() const;

            [[nodiscard]] double get_charge() const;
            [[nodiscard]] double get_load() const;
            [[nodiscard]] std::string get_model() const;
            [[nodiscard]] std::string get_serial() const;
            [[nodiscard]] std::vector<std::string> get_var_list() const;
            [[nodiscard]] std::vector<std::string> get_cmd_list() const;
            [[nodiscard]] std::string get_var(const std::string& var_name) const;
    };
} // nut

#endif //NUT_PLUS_PLUS_UPS_H