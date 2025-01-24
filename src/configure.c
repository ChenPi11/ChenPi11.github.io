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

#include "configure.h"

#include "content.h"
#include "defines.h"
#include "file-util.h"
#include "log.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t substr_count(char *str, const char *sub_str)
{
    size_t count = 0;
    char *begin_ptr = str;
    char *end_ptr = NULL;

    while ((end_ptr = strstr(begin_ptr, sub_str)) != NULL)
    {
        end_ptr += strlen(sub_str);
        begin_ptr = end_ptr;
        ++count;
    }

    return count;
}

#define _STRLEN_DELTA(str1, str2)                                                                                      \
    (strlen(str1) > strlen(str2) ? strlen(str1) - strlen(str2) : strlen(str2) - strlen(str1))

static int str_replace(const char *file_path, const char *to_str, const char *from_str)
{
    FILE *file = NULL;
    size_t file_size = 0;
    char *orig_str = NULL;
    size_t res_str_len = 0;
    char *res_str = NULL;
    char *cpy_str = NULL;
    char *begin_ptr = NULL;
    char *end_ptr = NULL;

    if (strlen(from_str) == 0)
    {
        warn("Empty find string when replacing string in file: %s\n", file_path);
        warn("Nothing will be replaced.\n");

        goto SUCCESS;
    }

    if ((file = fopen(file_path, "r")) == NULL)
    {
        die("Cannot open file: %s\n", file_path);
    }

    file_size = get_file_size(file_path);
    if (file_size == (size_t)(-1))
    {
        goto ERROR;
    }

    if (file_size == 0)
    {
        goto SUCCESS;
    }

    orig_str = (char *)calloc(file_size + 1, sizeof(char));
    if (orig_str == NULL)
    {
        die("Cannot allocate memory.\n");
    }

    if (fread(orig_str, sizeof(char), file_size, file) != file_size)
    {
        die("I/O Error: %s.\n", file_path);
    }

    close_file(file);

    res_str_len = file_size + substr_count(orig_str, from_str) * _STRLEN_DELTA(to_str, from_str) + 1;
    res_str = (char *)calloc(res_str_len, sizeof(char));
    if (res_str == NULL)
    {
        die("Cannot allocate memory.\n");
    }

    cpy_str = res_str;
    begin_ptr = orig_str;
    end_ptr = NULL;

    while ((end_ptr = strstr(begin_ptr, from_str)) != NULL)
    {
        memcpy(cpy_str, begin_ptr, end_ptr - begin_ptr);
        cpy_str += (end_ptr - begin_ptr);
        memcpy(cpy_str, to_str, strlen(to_str));
        cpy_str += strlen(to_str);
        end_ptr += strlen(from_str);
        begin_ptr = end_ptr;
    }
    memcpy(cpy_str, begin_ptr, strlen(begin_ptr));

    if ((file = fopen(file_path, "w")) == NULL)
    {
        die("Cannot open file: %s\n", file_path);
    }

    if (fwrite(res_str, sizeof(char), strlen(res_str), file) != strlen(res_str))
    {
        die("I/O Error: %s.\n", file_path);
    }

SUCCESS:
    close_file(file);
    free(orig_str);
    free(res_str);

    return RET_SUCCESS;

ERROR:
    close_file(file);
    free(orig_str);
    free(res_str);

    return RET_ERROR;
}

int configure(struct configures_t configs, const char *filepath)
{
    char strkey[BUFSIZ];
    struct configure_t replace;

    init_struct(strkey);
    init_struct(replace);

    if (filepath == NULL)
    {
        die("NULL filepath.\n");
    }

    info("Configuring %s ...\n", filepath);

    for (size_t i = 0; i < configs.num; ++i)
    {
        replace = configs.first[i];
        if (is_null_content(replace.key))
        {
            warn("NULL key found in configures.\n");
            continue;
        }

        const char *value = replace.value.content;

        if (is_null_content(replace.value))
        {
            warn("NULL value found in configures. Replace with empty string.\n");
            value = "";
        }

        replace = configs.first[i];
        init_struct(strkey);
        if (snprintf(strkey, BUFSIZ, "@%s@", replace.key.content) < 0)
        {
            die("Cannot format string: %s\n", replace.key.content);
        }
        if (str_replace(filepath, value, strkey) != RET_SUCCESS)
        {
            goto ERROR;
        }
    }

    return RET_SUCCESS;

ERROR:
    return RET_ERROR;
}
