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

#include "Server.h"
#include "UPS.h"

#include <iostream>
#include <upsclient.h>
#include <ostream>
#include <string>
#include <utility>

#include "exceptions/AuthenticationException.h"
#include "exceptions/ClientException.h"
#include "exceptions/CommandException.h"
#include "exceptions/ConnectionException.h"
#include "exceptions/UPSException.h"
#include "exceptions/VariableException.h"

namespace nut {
    Server::Server(std::string hostname, const int port):
        m_hostname(std::move(hostname)),
        m_port(port),
        m_connection{}
    {}

    Server::~Server() {
        if (get_handle() != nullptr) {
            upscli_disconnect(&m_connection);
        }
    }

    void Server::connect() {
        int result = upscli_connect(get_handle(), get_hostname().c_str(), get_port(), UPSCLI_CONN_TRYSSL);

        if (result != 0) {
            upscli_disconnect(&m_connection);
            handle_error();
        }
    }

    std::string Server::get_var(const std::string &ups_name, const std::string &var_key) const {
        const char* query[] = { "VAR", ups_name.c_str(), var_key.c_str()};
        size_t num_queries = 3;
        size_t num_answers;
        char** answer_list;

        if (upscli_get(get_handle(), num_queries, query, &num_answers, &answer_list) != 0) {
            handle_error();
        }

        if (num_answers != 4) {
            throw ClientException("Unexpected response length.");
        }

        return answer_list[3];
    }

    double Server::get_var_double(const std::string &ups_name, const std::string &var_key) const {
        std::string raw_double = get_var(ups_name, var_key);
        double value;

        try {
            value = std::stod(raw_double);
        } catch (const std::invalid_argument& e) {
            throw ClientException(e.what());
        } catch (const std::out_of_range& e) {
            throw ClientException(e.what());
        }

        return value;
    }

    std::vector<std::vector<std::string>> Server::get_var_list(const std::string &var_key) const {
        return get_var_list("", var_key);
    }

    std::vector<std::vector<std::string>> Server::get_var_list(const std::string &ups_name, const std::string &var_key) const {
        std::vector<std::vector<std::string>> result;

        std::vector<const char*> query;
        size_t num_queries;
        size_t num_answers;
        char** answer_list;

        if (ups_name.empty()) {
            query = { var_key.c_str() };
            num_queries = 1;
        } else {
            query = { var_key.c_str(), ups_name.c_str() };
            num_queries = 2;
        }

        if (upscli_list_start(get_handle(), num_queries, query.data()) != 0) {
            handle_error();
        }

        while (upscli_list_next(get_handle(), num_queries, query.data(), &num_answers, &answer_list) == 1) {
            std::vector<std::string> answer_vector;
            for (int i = 0; i < num_answers; ++i) {
                answer_vector.emplace_back(answer_list[i]);
            }
            result.emplace_back(answer_vector);
        }

        return result;
    }

    UPS Server::get_ups(const std::string& ups_name) const {
        const char* query[] = { "UPSDESC", ups_name.c_str() };
        size_t num_queries = 2;
        size_t num_answers;
        char** answer_list;

        if (upscli_get(get_handle(), num_queries, query, &num_answers, &answer_list) != 0) {
            handle_error();
        }

        if (num_answers != 3) {
            throw ClientException("Unexpected response length.");
        }

        return {*this, ups_name.c_str(), answer_list[2]};
    }

    std::vector<UPS> Server::get_ups_list() const {
        std::vector<UPS> ups_vector;
        const std::vector<std::vector<std::string>> result = get_var_list("UPS");;

        for (auto answer_list : result) {
            ups_vector.emplace_back(*this, answer_list.at(1), answer_list.at(2));
        }

        return ups_vector;
    }

    void Server::handle_error() const {
        const int error_code = upscli_upserror(get_handle());
        const std::string error_msg = upscli_strerror(get_handle());

        switch (error_code) {
            // Connection Errors
            case UPSCLI_ERR_NOSUCHHOST: // 2
            case UPSCLI_ERR_SENDFAILURE: // 27
            case UPSCLI_ERR_RECVFAILURE: // 28
            case UPSCLI_ERR_SOCKFAILURE: // 29
            case UPSCLI_ERR_BINDFAILURE: // 30
            case UPSCLI_ERR_CONNFAILURE: // 31
            case UPSCLI_ERR_WRITE: // 32
            case UPSCLI_ERR_READ: // 33
            case UPSCLI_ERR_SSLFAIL: // 36
            case UPSCLI_ERR_SSLERR: // 37
            case UPSCLI_ERR_SRVDISC: // 38
            case UPSCLI_ERR_DRVNOTCONN: // 39
                throw ConnectionException(error_msg);

            // Authentication Errors
            case UPSCLI_ERR_ACCESSDENIED: // 6
            case UPSCLI_ERR_PWDREQUIRED: // 7
            case UPSCLI_ERR_PWDINCORRECT: // 8
            case UPSCLI_ERR_LOGINTWICE: // 12
            case UPSCLI_ERR_PWDSETTWICE: // 13
            case UPSCLI_ERR_INVUSERNAME: // 23
            case UPSCLI_ERR_USERSETTWICE: // 24
            case UPSCLI_ERR_INVPASSWORD: // 34
            case UPSCLI_ERR_USERREQUIRED: // 35
                throw AuthenticationException(error_msg);

            // Variable Errors
            case UPSCLI_ERR_VARNOTSUPP: // 1
            case UPSCLI_ERR_VARUNKNOWN: // 11
            case UPSCLI_ERR_UNKNOWNVAR: // 15
            case UPSCLI_ERR_VARREADONLY: // 16
            case UPSCLI_ERR_INVALIDVALUE: // 18
                throw VariableException(error_msg);

            // Command Errors
            case UPSCLI_ERR_UNKINSTCMD: // 20
            case UPSCLI_ERR_CMDFAILED: // 21
            case UPSCLI_ERR_CMDNOTSUPP: // 22
            case UPSCLI_ERR_UNKCOMMAND: // 25
                throw CommandException(error_msg);

            // Client and Syntax Errors
            case UPSCLI_ERR_INVRESP: // 3
            case UPSCLI_ERR_MISSINGARG: // 9
            case UPSCLI_ERR_UNKNOWNTYPE: // 15
            case UPSCLI_ERR_TOOLONG: // 17
            case UPSCLI_ERR_INVALIDARG: // 26
            case UPSCLI_ERR_NOMEM: // 40
            case UPSCLI_ERR_PARSE: // 41
            case UPSCLI_ERR_PROTOCOL: // 42
                throw ClientException(error_msg);

            // UPS Errors
            case UPSCLI_ERR_UNKNOWNUPS: // 4
            case UPSCLI_ERR_DATASTALE: // 10
            case UPSCLI_ERR_SETFAILED: // 19
                throw UPSException(error_msg);

            default:
                throw NUTException(error_msg);

        }
    }
}
