# CMakeLists.txt
#
# Copyright 2022 Pg Biel
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
# SPDX-License-Identifier: GPL-2.0-or-later
#
cmake_minimum_required(VERSION 3.24)
project(utf_analysis)

set(CMAKE_CXX_STANDARD 20)

add_executable(utf_analysis src/main.cpp)

# ICU : https://stackoverflow.com/a/54912121

# ICU Components Reference:
# https://cmake.org/cmake/help/latest/module/FindICU.html
# ICU components = data, i18n, io, le, lx, test, tu and uc.

find_package(ICU 72.0 COMPONENTS uc i18n REQUIRED)

# Link using the imported target names (ICU::uc, ICU::i18n, etc.)

target_link_libraries(utf_analysis ICU::uc ICU::i18n)