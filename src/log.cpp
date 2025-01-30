/**
 * @file log.cpp
 * @brief The log module implementation.
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

#include "log.hpp"

#include "i18n.hpp"

#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

namespace
{
static const char *proc_name = "";
static enum logging::LogLevel log_level = logging::LogLevel::WARN;
}

void logging::init(int argc, char *argv[]) noexcept
{
    if (argc > 0)
    {
        proc_name = argv[0];
    }
}

void logging::set_level(const enum LogLevel level) noexcept
{
    log_level = level;
}

enum logging::LogLevel logging::get_level() noexcept
{
    return log_level;
}

void logging::info(const char *fmt, ...) noexcept
{
    if (log_level > LogLevel::INFO)
    {
        return;
    }

    std::va_list ap;

    va_start(ap, fmt);
    std::fprintf(stderr, "%s", _("INFO: "));
    std::vfprintf(stderr, fmt, ap);
    va_end(ap);
}

void logging::warn(const char *fmt, ...) noexcept
{
    if (log_level > LogLevel::WARN)
    {
        return;
    }

    std::va_list ap;

    va_start(ap, fmt);
    std::fprintf(stderr, "%s", _("WARNING: "));
    std::vfprintf(stderr, fmt, ap);
    va_end(ap);
}

void logging::error(const char *fmt, ...) noexcept
{
    std::va_list ap;

    va_start(ap, fmt);
    std::fprintf(stderr, "%s", _("ERROR: "));
    std::vfprintf(stderr, fmt, ap);
    va_end(ap);
    if (errno)
    {
        std::perror(proc_name);
    }

    std::exit(EXIT_FAILURE);
}

const char *logging::get_proc_name() noexcept
{
    return proc_name;
}
