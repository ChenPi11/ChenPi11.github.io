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

#ifdef __cplusplus
extern "C"
{
#endif

extern void log_init(int argc, char *argv[]);

extern void info(const char *fmt, ...);

extern void warn(const char *fmt, ...);

extern void die(const char *fmt, ...);

extern const char *get_proc_name();

#ifdef __cplusplus
}
#endif

#endif
