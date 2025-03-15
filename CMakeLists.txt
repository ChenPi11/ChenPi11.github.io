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
    HOMEPAGE_URL "https://github.com/ChenPi11/ChenPi11.github.io"
    LANGUAGES CXX
)

# Set options.
set ( CMAKE_CXX_STANDARD 20 )
cmake_policy ( SET CMP0156 NEW )
cmake_policy ( SET CMP0179 NEW )

# Find sources.
file ( GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )

# Include directories.
include_directories ( "${CMAKE_CURRENT_SOURCE_DIR}" )
include_directories ( "${CMAKE_CURRENT_SOURCE_DIR}/include" )

# Find libraries.
find_package ( Intl OPTIONAL_COMPONENTS )

if ( NOT Intl_FOUND )
    set ( HAVE_LIBINTL_H 0 )
else ()
    set ( HAVE_LIBINTL_H 1 )
endif ()

# Configure header file.
set ( PACKAGE_NAME "${PROJECT_NAME}" )
set ( PACKAGE_VERSION "${PROJECT_VERSION}" )
configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/config.hpp" )

# Set compiler flags.
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra" )

# Build target.
add_executable ( mkpostlists ${SOURCES} )

# Link libraries.
target_link_libraries ( mkpostlists Intl::Intl )

# Install target.
install ( TARGETS mkpostlists )

# Uninstall target.
configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY )

add_custom_target ( uninstall
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake" )
