/**
 * @file file-util.hpp
 * @brief File operation utils.
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

#pragma once
#ifndef _FILE_UTIL_HPP_
#define _FILE_UTIL_HPP_

#include <filesystem>
#include <string>

namespace file
{
/**
 * @brief Read all data from a file to a string.
 * @param filepath The path of the file.
 * @return The string of the file data.
 */
extern std::string readfile(const std::filesystem::path &filepath);

/**
 * @brief Write a string to a file.
 * @param filepath The path of the file.
 * @param data The string to be written.
 */
extern void writefile(const std::filesystem::path &filepath, const std::string &data);

/**
 * @brief Check if the current working directory is ChenPi11's blog root directory.
 * @return true if it is, false otherwise.
 */
extern bool is_chenpi11_blog_rootdir();

} // namespace file

#endif // _CONTENT_HPP_
