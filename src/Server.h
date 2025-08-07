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

    class Server {
    private:
        UPSCONN_t m_connection;
        std::string m_hostname;
        int m_port;

    public:
        explicit Server(std::string  hostname = "localhost", int port = 3493);
        ~Server();

        /**
         * Initialize connection to NUT Server.
         */
        void connect();

        /**
         * Get variable value from specified UPS.
         * @param ups_name Name of UPS to query
         * @param var_key Variable to be queried
         * @return string of variable value
         * @throws NUTException
         */
        [[nodiscard]] std::string get_var(const std::string& ups_name, const std::string& var_key) const;

        /**
         * Get variable value from specified UPS and attempt to cast to double.
         * @param ups_name Name of UPS to query
         * @param var_key Variable to be queried
         * @return double of variable value
         * @throws NUTException, std::invalid_argument, std::out_of_range
         */
        [[nodiscard]] double get_var_double(const std::string& ups_name, const std::string& var_key) const;

        /**
         * Query variable which returns a list with NO specified UPS.
         * @param var_key string key to be queried
         * @return vector of strings containing return values.
         * @throws NUTException
         */
        [[nodiscard]] std::vector<std::vector<std::string>> get_var_list(const std::string& var_key) const;

        /**
         * Query variable which returns a list for a specified UPS.
         * @param ups_name string name of UPS
         * @param var_key string key to be queried
         * @return vector of strings containing return values.
         * @throws NUTException
         */
        [[nodiscard]] std::vector<std::vector<std::string>> get_var_list(const std::string& ups_name, const std::string& var_key) const;

        /**
         * Get UPS object for a specified name.
         * @param ups_name string name of UPS
         * @return UPS object for name.
         * @throws NUTException
         */
        [[nodiscard]] UPS get_ups(const std::string& ups_name) const;

        /**
         * Get list of UPS connected to this NUT server.
         * @return vector of UPS objects
         */
        [[nodiscard]] std::vector<UPS> get_ups_list() const;

        /**
         * Retrieve upscli error code and throw the corresponding NUT++ exception.
         * @throws NUTException
         */
        void handle_error() const;

        /**
         * Get hostname of NUT server.
         * @return string hostname
         */
        [[nodiscard]] std::string get_hostname() const {
            return m_hostname;
        }

        /**
         * Get port of NUT server.
         * @return int port
         */
        [[nodiscard]] int get_port() const {
            return m_port;
        }

        /**
         * Get instance of UPSCONN_t object with constant casting.
         * @return const_cast of UPSCONN_t.
         */
        [[nodiscard]] UPSCONN_t* get_handle() const {
            return const_cast<UPSCONN_t*>(&m_connection);
        }
    };
}


#endif //NUT_PLUS_PLUS_CONNECTION_H