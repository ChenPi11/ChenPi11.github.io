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

#include <copyfile.h>

#include <log.h>

#include <stdio.h>
#include <sys/stat.h>

extern void copy_file(const char *from, const char *to)
{
    FILE *from_file = fopen(from, "rb");
    struct stat from_stat;
    if (from_file == NULL)
    {
        die("Cannot open file: %s\n", from);
    }
    if (stat(from, &from_stat) == -1)
    {
        fclose(from_file);
        die("Cannot stat file: %s\n", from);
    }

    size_t from_size = from_stat.st_size;

    FILE *to_file = fopen(to, "wb");
    if (to_file == NULL)
    {
        fclose(from_file);
        die("Cannot open file: %s\n", to);
    }
    char buffer[BUFSIZ];
    size_t read = 0;
    while ((read = fread(buffer, 1, BUFSIZ, from_file)) > 0)
    {
        fwrite(buffer, 1, read, to_file);
    }
    fclose(from_file);
    fclose(to_file);
}
