// Represents connection with NUT server.
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

#ifndef NUT_PLUS_PLUS_CONNECTION_H
#define NUT_PLUS_PLUS_CONNECTION_H

// Unused import fixes missing dependency for uint16_t when using upsclient.h methods.
#include <cstdint>
#include <string>
#include <vector>
#include <upsclient.h>


namespace nut {

    class UPS;

    class Connection {
    private:
        UPSCONN_t m_connection;
        std::string m_hostname;
        int m_port;

    public:
        explicit Connection(std::string  hostname = "localhost", int port = 3493);
        ~Connection();

        void connect();
        [[nodiscard]] std::string get_var(const std::string& ups_name, const std::string& var_key) const;
        [[nodiscard]] double get_var_double(const std::string& ups_name, const std::string& var_key) const;
        [[nodiscard]] std::vector<std::vector<std::string>> get_var_list(const std::string& var_key) const;
        [[nodiscard]] std::vector<std::vector<std::string>> get_var_list(const std::string& ups_name, const std::string& var_key) const;
        [[nodiscard]] UPS get_ups(const std::string& ups_name) const;
        [[nodiscard]] std::vector<UPS> get_ups_list() const;
        void handle_error() const;

        [[nodiscard]] std::string get_hostname() const {
            return m_hostname;
        }

        [[nodiscard]] int get_port() const {
            return m_port;
        }

        [[nodiscard]] UPSCONN_t* get_handle() const {
            return const_cast<UPSCONN_t*>(&m_connection);
        }


    };
}


#endif //NUT_PLUS_PLUS_CONNECTION_H