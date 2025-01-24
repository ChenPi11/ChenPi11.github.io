/**
 * @file log.hpp
 * @brief The log module.
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
#ifndef _LOG_HPP_
#define _LOG_HPP_

namespace logging
{
/**
 * @brief Initialize the log module.
 * @param argc The process argument count.
 * @param argv The process argument vector.
 */
void init(int argc, char *argv[]) noexcept;

/**
 * @brief Show info.
 * @param fmt The format string.
 * @param ... The format arguments.
 */
void info(const char *fmt, ...) noexcept;

/**
 * @brief Show warning.
 * @param fmt The format string.
 * @param ... The format arguments.
 */
void warn(const char *fmt, ...) noexcept;

/**
 * @brief Show error.
 * @param fmt The format string.
 * @param ... The format arguments.
 */
void error(const char *fmt, ...) noexcept;

/**
 * @brief Get the process name.
 * @return The process name.
 */
const char *get_proc_name() noexcept;
} // namespace log

#endif // _LOG_HPP_
