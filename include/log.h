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
#ifndef _LOG_H_
#define _LOG_H_

#include "defines.h"

EXTERN_C_BEG

/* Initialize the log module. */
extern void log_init(int argc, char *argv[]);

enum LogLevel
{
    LOG_INFO,
    LOG_WARN,
};

/* Set log level. */
extern void set_log_level(enum LogLevel level);

/* Get log level. */
extern enum LogLevel get_log_level();

/* Show info. */
extern void info(const char *fmt, ...);

/* Show warning. */
extern void warn(const char *fmt, ...);

/* Show error. */
extern void error(const char *fmt, ...);

/* Show fatal and goto ERROR. */
#define die(fmt, ...)                                                                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        error(fmt, ##__VA_ARGS__);                                                                                     \
        goto ERROR;                                                                                                    \
    } while (FALSE)

/* Get the process name. */
extern const char *get_proc_name();

EXTERN_C_END

#endif
