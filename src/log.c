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

#include "log.h"

#include "i18n.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static const char *proc_name = "";
static enum LogLevel log_level = LOG_INFO;

void log_init(int argc, char *argv[])
{
    if (argc > 0)
    {
        proc_name = argv[0];
    }
}

void set_log_level(enum LogLevel level)
{
    log_level = level;
}

enum LogLevel get_log_level()
{
    return log_level;
}

void info(const char *fmt, ...)
{
    va_list ap;

    if (log_level > LOG_INFO)
    {
        return;
    }

    va_start(ap, fmt);
    fprintf(stderr, _("INFO: "));
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}

void warn(const char *fmt, ...)
{
    va_list ap;

    if (log_level > LOG_WARN)
    {
        return;
    }

    va_start(ap, fmt);
    fprintf(stderr, _("WARNING: "));
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}

void error(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, _("ERROR: "));
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    if (errno)
    {
        perror(proc_name);
    }
}

const char *get_proc_name()
{
    return proc_name;
}
