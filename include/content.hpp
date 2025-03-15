/**
 * @file content.hpp
 * @brief String utils.
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
#ifndef _CONTENT_HPP_
#define _CONTENT_HPP_

#include <string>
#include <vector>

namespace content
{

/**
 * @brief Split a string by a delimiter.
 * @param str The string to be split.
 * @param delim The delimiter.
 * @return The vector of the split result.
 */
extern std::vector<std::string> split(const std::string &str, const char delim);

/**
 * @brief Checking if the string has a suffix.
 * @param str The string to be checked.
 * @param suffix The suffix.
 * @return Return true if the string has the suffix. false otherwise.
 */
extern bool endswith(const std::string &str, const std::string &suffix);

} // namespace content

#endif // _CONTENT_HPP_
