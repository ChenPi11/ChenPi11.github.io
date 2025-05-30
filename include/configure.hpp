/**
 * @file configure.hpp
 * @brief Configure a string with key-value pairs.
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
#ifndef _CONFIGURE_HPP_
#define _CONFIGURE_HPP_

#include <string>
#include <vector>

namespace configure
{

/**
 * @brief The configure struct.
 */
struct configure_t
{
    /**
     * @brief The key of the configure.
     */
    std::string key;

    /**
     * @brief The value of the configure.
     */
    std::string value;
};

/**
 * @brief The configures.
 */
using configures_t = std::vector<configure_t>;

/**
 * @brief Get the configure value by key.
 * @param configs The configures.
 * @param src The source string.
 * @return The configured string.
 */
extern std::string configure(const configures_t &configs, const std::string &src);

} // namespace configure

#endif // _CONFIGURE_HPP_
