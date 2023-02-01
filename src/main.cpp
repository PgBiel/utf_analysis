/* main.cpp
 *
 * Copyright 2022 Pg Biel
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <iostream>
#include <string>
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#include <unicode/errorcode.h>
#include <numeric>
#include <vector>
#include <array>

// see https://stackoverflow.com/a/29729158
std::string convert_uchar(UChar32 uchar) {
    icu::UnicodeString tmp_ustr { uchar };
    std::string str_res {};

    tmp_ustr.toUTF8String(str_res);
    return str_res;
}

// see https://stackoverflow.com/a/72482270 (bottom example)
std::pair<std::string, icu::ErrorCode> get_charname(UChar32 chr) {
    UErrorCode errorCode {};
    std::array<char, 256> buffer {};
    u_charName_72(chr, UCharNameChoice::U_UNICODE_CHAR_NAME,
               buffer.data(), static_cast<int32_t>(buffer.size() - 1),
               &errorCode);

    std::string chrname {};
    if (errorCode == UErrorCode::U_ZERO_ERROR) {
        chrname = buffer.data();
    }

    icu::ErrorCode errorCodeObj {};
    errorCodeObj.set(errorCode);
    return { chrname, errorCodeObj };
}

void print_uchar(UChar32 chr) {
    std::string chrstr { convert_uchar(chr) };

    std::cout << chrstr << " ( 0x" << std::hex << chr << " )" << std::dec;

    std::pair<std::string, icu::ErrorCode> chrname_pair { get_charname(chr) };
    icu::ErrorCode errorCodeObj { chrname_pair.second };

    if (errorCodeObj.isFailure()) {
        std::cout << " (NAME ERROR: 0x" << std::hex << errorCodeObj.get() << std::dec << ")\n";
    } else {
        std::string_view chrname { chrname_pair.first };
        std::cout << " (" << chrname << ")\n";
    }
}

int main() {
    std::cout << "Provide line of input: ";

    std::string str {};
    do {
        std::getline(std::cin >> std::ws, str, '\n');
        if (!std::cin) {
            std::cout << "Could not process input, please try again.\n";
            std::cin.clear();
        }
    } while(!std::cin);

    icu::UnicodeString ustr { str.c_str() };
    int32_t charCount = ustr.countChar32();
    std::cout << charCount << " characters detected:\n";

    for (int i = 0; i < charCount; i++) {
        std::cout << "Char " << i << ": ";

        print_uchar(ustr.char32At(i));
    }

    return 0;
}
