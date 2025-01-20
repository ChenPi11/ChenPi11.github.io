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

#include <configure.h>

#include <log.h>

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static size_t substr_count(char *str, const char *sub_str)
{
    if (str == NULL || sub_str == NULL)
    {
        die("substr_count(): Parameters should not be NULL\n");
    }
    size_t n = 0;
    char *begin_ptr = str;
    char *end_ptr = NULL;

    while ((end_ptr = strstr(begin_ptr, sub_str)) != NULL)
    {
        end_ptr += strlen(sub_str);
        begin_ptr = end_ptr;
        ++n;
    }
    return n;
}

static void str_replace(const char *file_path, const char *new_str, const char *old_str)
{
    struct stat file_stat;
    FILE *fp;

    if (file_path == NULL || new_str == NULL || old_str == NULL)
    {
        die("str_replace(): Parameters should not be NULL\n");
    }

    if (old_str[0] == '\0')
    {
        warn("Empty find string when replacing string in file: %s\n", file_path);
        warn("Nothing will be replaced.\n");
        return;
    }

    if ((fp = fopen(file_path, "r")) == NULL)
    {
        die("Cannot open file: %s\n", file_path);
    }

    if (stat(file_path, &file_stat) == -1)
    {
        fclose(fp);
        die("Cannot stat file %s\n", file_path);
    }

    size_t file_len = (size_t)file_stat.st_size;

    if (file_len == 0)
    {
        fclose(fp);
        return;
    }

    char *orig_str = (char *)malloc(file_len + 1);
    if (orig_str == NULL)
    {
        fclose(fp);
        die("Cannot allocate memory.\n");
    }
    memset(orig_str, 0, file_len + 1);

    const int count = 1;
    int ret = fread(orig_str, file_len, count, fp);

    if (ret != count)
    {
        fclose(fp);
        free(orig_str);
        die("I/O Error: %s.\n", file_path);
    }

    int n = substr_count(orig_str, old_str);

    int rst_str_len = file_len + n * abs(((int)strlen(new_str) - (int)strlen(old_str))) + 1;
    char *rst_str = (char *)malloc(rst_str_len);
    if (rst_str == NULL)
    {
        die("Cannot allocate memory.\n");
    }
    memset(rst_str, 0, rst_str_len);

    char *cpy_str = rst_str;
    char *begin_ptr = orig_str;
    char *end_ptr = NULL;

    while ((end_ptr = strstr(begin_ptr, old_str)) != NULL)
    {
        memcpy(cpy_str, begin_ptr, end_ptr - begin_ptr);
        cpy_str += (end_ptr - begin_ptr);
        memcpy(cpy_str, new_str, strlen(new_str));
        cpy_str += strlen(new_str);
        end_ptr += strlen(old_str);
        begin_ptr = end_ptr;
    }
    strcpy(cpy_str, begin_ptr);

    fclose(fp);

    if ((fp = fopen(file_path, "w")) == NULL)
    {
        die("Cannot open file: %s\n", file_path);
    }

    ret = fwrite(rst_str, strlen(rst_str), count, fp);
    if (ret != count)
    {
        fclose(fp);
        free(orig_str);
        free(rst_str);
        die("I/O Error: %s.\n", file_path);
    }

    free(orig_str);
    free(rst_str);
    fclose(fp);
}

void configure(struct configures_t configs, const char *filepath)
{
    info("%s: Configuring %s ...\n", filepath);
    for (size_t i = 0; i < configs.num; ++i)
    {
        struct configure_t replace = configs.first[i];
        char strkey[BUFSIZ];
        memset(strkey, 0, BUFSIZ);
        snprintf(strkey, BUFSIZ, "@%s@", replace.key);
        str_replace(filepath, replace.value, strkey);
    }
}

void free_configures(struct configures_t *configs)
{
    if (configs == NULL)
    {
        return;
    }
    free(configs->first);
    configs->num = 0;
    configs->first = NULL;
}