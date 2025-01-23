# Copyright (C) 2025 ChenPi11.
# This file is part of chenpi11-blog.
#
# chenpi11-blog is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# chenpi11-blog is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with chenpi11-blog.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required ( VERSION 3.20 )

project (
    "chenpi11-blog"
    VERSION 0.1.0
    DESCRIPTION "ChenPi11's blog"
)

set ( CMAKE_CXX_STANDARD 20 )

set ( SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/mkpostlists.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/configure.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/log.c" )

include_directories ( "${CMAKE_CURRENT_SOURCE_DIR}/include" )

add_executable ( mkpostlists ${SOURCES} )

install ( TARGETS mkpostlists )
