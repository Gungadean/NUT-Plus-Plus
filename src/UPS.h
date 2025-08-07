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

#include <string>
#include <vector>

namespace nut {

    class Server;

    class UPS {
        private:
            const Server& m_server;
            const std::string m_ups_name;
            const std::string m_ups_description;
        public:
            UPS(const Server& server, std::string ups_name, std::string ups_description);
            ~UPS();

            /**
             * Get name of UPS.
             * @return string name
             */
            [[nodiscard]] const std::string& get_name() const;

            /**
             * Get description of UPS.
             * @return string description
             */
            [[nodiscard]] const std::string& get_description() const;

            /**
             * Get current charge of UPS.
             * @return double charge percent
             */
            [[nodiscard]] double get_charge() const;

            /**
             * Get current load of UPS.
             * @return double load percent
             */
            [[nodiscard]] double get_load() const;

            /**
             * Get model of UPS.
             * @return string model name
             */
            [[nodiscard]] std::string get_model() const;

            /**
             * Get serial number of UPS.
             * @return string serial number
             */
            [[nodiscard]] std::string get_serial() const;

            /**
             * Get list of supported variables for UPS.
             * @return vector of supported variables as strings.
             */
            [[nodiscard]] std::vector<std::string> get_variables_list() const;

            /**
             * Get list of supported commands for UPS.
             * @return vector of support commands as strings.
             */
            [[nodiscard]] std::vector<std::string> get_command_list() const;

            /**
             * Get value of specified variable name.
             * @param var_name name of variable to retrieve
             * @return string value of variable
             */
            [[nodiscard]] std::string get_variable(const std::string& var_name) const;
    };
} // nut

#endif //NUT_PLUS_PLUS_UPS_H