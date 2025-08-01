// [File description]
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

#ifndef NUT_PLUS_PLUS_AUTHENTICATIONEXCEPTION_H
#define NUT_PLUS_PLUS_AUTHENTICATIONEXCEPTION_H

#include "NUTException.h"

namespace nut {
    class AuthenticationException : public NUTException {
    public:
        using NUTException::NUTException;
    };
}

#endif //NUT_PLUS_PLUS_AUTHENTICATIONEXCEPTION_H