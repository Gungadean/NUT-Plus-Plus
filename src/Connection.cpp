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

#include "Connection.h"
#include "UPS.h"

#include <iostream>
#include <upsclient.h>
#include <ostream>
#include <string>
#include <utility>

#include "exceptions/AuthenticationException.h"
#include "exceptions/CommandException.h"
#include "exceptions/ConnectionException.h"

namespace nut {
    Connection::Connection(std::string hostname, const int port):
        hostname(std::move(hostname)),
        port(port),
        connection{}
    {
        std::cout << "Connection object created for " << hostname << std::endl;
    }

    Connection::~Connection() {
        if (get_handle() != nullptr) {
            upscli_disconnect(&connection);
        }
        std::cout << "Connection closed." << std::endl;
    }

    void Connection::connect() {
        int result = upscli_connect(get_handle(), hostname.c_str(), port, UPSCLI_CONN_TRYSSL);

        if (result != 0) {
            std::cerr << "Connection failed." << upscli_strerror(&connection) << std::endl;
            upscli_disconnect(&connection);
            throw std::runtime_error("Connection failed: " + std::string(upscli_strerror(get_handle())));
        }
        std::cout << "Connection established." << std::endl;
    }

    UPS Connection::get_ups(const std::string& ups_name) {
        const char* query[] = { "UPSDESC", ups_name.c_str() };
        size_t num_queries = 2;
        size_t num_answers;
        char** answer_list;

        if (upscli_get(get_handle(), num_queries, query, &num_answers, &answer_list) == 0) {
            if (num_answers == 3) {
                return {*this, ups_name.c_str(), answer_list[2]};
            }
        }

        throw std::runtime_error("Failed to get UPS " + std::string(upscli_strerror(get_handle())));
    }

    std::vector<UPS> Connection::get_ups_list() {
        std::vector<UPS> result;

        const char* query[] = { "UPS" };
        size_t num_queries = 1;
        size_t num_answers;
        char** answer_list;

        if (upscli_list_start(get_handle(), num_queries, query) != 0) {
            std::cout << "Failed to get ups list: " << std::string(upscli_strerror(get_handle())) << std::endl;
        }

        while (upscli_list_next(get_handle(), num_queries, query, &num_answers, &answer_list) == 1) {
            if (num_answers == 3) {
                const char* ups_name = answer_list[1];
                const char* ups_description = answer_list[2];

                result.emplace_back(*this, ups_name, ups_description);
            }
        }
        return result;
    }

    void Connection::handle_error() {
        const int error_code = upscli_upserror(get_handle());
        const std::string error_msg = upscli_strerror(get_handle());

        switch (error_code) {
            case UPSCLI_ERR_NOSUCHHOST:
            case UPSCLI_ERR_CONNFAILURE:
            case UPSCLI_ERR_SRVDISC:
                throw ConnectionException(error_msg);
            case UPSCLI_ERR_ACCESSDENIED:
            case UPSCLI_ERR_PWDREQUIRED:
            case UPSCLI_ERR_PWDINCORRECT:
            case UPSCLI_ERR_INVPASSWORD:
                throw AuthenticationException(error_msg);
            case UPSCLI_ERR_CMDFAILED:
            case UPSCLI_ERR_CMDNOTSUPP:
                throw CommandException(error_msg);

        }
    }
}
