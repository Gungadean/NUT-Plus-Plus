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
        UPSCONN_t connection;
        std::string hostname;
        int port;

    public:
        explicit Connection(std::string  hostname = "localhost", int port = 3493);
        ~Connection();

        void connect();
        [[nodiscard]] UPS get_ups(const std::string& ups_name);
        [[nodiscard]] std::vector<UPS> get_ups_list();
        void handle_error();

        [[nodiscard]] std::string get_hostname() const {
            return hostname;
        }

        [[nodiscard]] int get_port() const {
            return port;
        }

        UPSCONN_t* get_handle() {
            return &connection;
        }


    };
}


#endif //NUT_PLUS_PLUS_CONNECTION_H