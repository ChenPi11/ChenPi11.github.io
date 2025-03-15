/**
 * @file file-util.cpp
 * @brief File utils implementation.
 * @author ChenPi11
 * @copyright Copyright (C) 2025 ChenPi11
 */
/*
 * Copyright (C) 2025 ChenPi11
 * This file is part of the chenpi11-blog.
 *
 * chenpi11-blog is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * chenpi11-blog is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with chenpi11-blog.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "file-util.hpp"

#include "i18n.hpp"
#include "log.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>

std::string file::readfile(const std::filesystem::path &filepath)
{
    std::ifstream file(filepath);
    if (!file)
    {
        std::string filepath_str = filepath.string();
        logging::error(_("Cannot open file: %s\n"), filepath_str.c_str());
        throw std::system_error(errno, std::generic_category());
    }

    std::size_t size = std::filesystem::file_size(filepath);
    std::string data(size, '\0');
    file.read(data.data(), size);
    file.close();

    return data;
}

void file::writefile(const std::filesystem::path &filepath, const std::string &data)
{
    std::ofstream file(filepath);
    if (!file)
    {
        std::string filepath_str = filepath.string();
        logging::error(_("Cannot open file: %s\n"), filepath_str.c_str());
        throw std::system_error(errno, std::generic_category());
    }
    file << data;
    file.close();
}

#define CHECK(x)                                                                                                       \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            goto NOT;                                                                                                  \
        }                                                                                                              \
    } while (false)

#define is_dir std::filesystem::is_directory
#define is_file std::filesystem::is_regular_file

bool file::is_chenpi11_blog_rootdir()
{
    CHECK(is_dir(std::filesystem::current_path()));
    CHECK(is_file("requirements.txt") && is_file("pyproject.toml")); // It's a Python project.
    CHECK(is_file("Cargo.toml") && is_file("Makefile.toml"));        // It's a Rust project.
    CHECK(is_file("configure.ac") && is_file("autogen.sh"));         // It's an Autotools project.
    CHECK(is_file("CMakeLists.txt"));                                // It's a CMake project.
    CHECK(is_file("package.json"));                                  // It's a Node.js project.
    CHECK(is_file("Makefile.in"));                                   // It's an Autoconf+Makefile project.
    CHECK(is_file("repo.json"));                                     // It's a Rubisco project.
    CHECK(is_file("tsconfig.json"));                                 // It's a TypeScript project.
    CHECK(is_file("go.mod"));                                        // It's a Go project.

    errno = 0;

    return true;

NOT:
    errno = 0;

    return false;
}
