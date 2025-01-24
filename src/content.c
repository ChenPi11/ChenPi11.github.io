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

#include "content.h"
#include "defines.h"
#include "log.h"

#include <malloc.h>
#include <stdio.h>
#include <sys/stat.h>

struct content_t static_content(const char *source)
{
    return (struct content_t){.content = (char *)source, .len = strlen(source), .is_static = TRUE};
}

struct content_t alloc_content(size_t length)
{
    struct content_t res;

    init_struct(res);

    res.content = malloc(length + 1);
    if (res.content == NULL)
    {
        die("Memory allocation failed.");
    }

    res.len = length;
    res.is_static = FALSE;

    return res;

ERROR:
    return null_content;
}

void free_content(struct content_t *content)
{
    if (content == NULL || content->is_static)
    {
        return;
    }

    free(content->content);
    content->content = NULL;
    content->len = 0;
}

int startswith(const struct content_t content, const struct content_t prefix)
{
    if (is_null_content(content) && is_null_content(prefix))
    {
        return TRUE;
    }
    if (prefix.len > content.len || is_null_content(content) || is_null_content(prefix))
    {
        return FALSE;
    }

    return memcmp(content.content, prefix.content, prefix.len) == 0;
}

int endswith(const struct content_t content, const struct content_t suffix)
{
    if (is_null_content(content) && is_null_content(suffix))
    {
        return TRUE;
    }
    if (suffix.len > content.len || is_null_content(content) || is_null_content(suffix))
    {
        return FALSE;
    }

    return memcmp(content.content + content.len - suffix.len, suffix.content, suffix.len) == 0;
}

#define NOT(c) (content->content[i] != c)

int lstrip(struct content_t *content)
{
    size_t prefix_pos = 0;
    struct content_t new_content = null_content;

    if (content == NULL)
    {
        return RET_ERROR;
    }
    if (is_null_content(*content))
    {
        return RET_SUCCESS;
    }

    for (size_t i = 0; i < content->len; i++)
    {
        if (NOT(' ') && NOT('\t') && NOT('\n') && NOT('\r') && NOT('\v') && NOT('\f'))
        {
            prefix_pos = i;
            break;
        }
    }

    new_content = alloc_content(content->len - prefix_pos);
    if (is_null_content(new_content))
    {
        return RET_ERROR;
    }
    for (size_t i = 0; i < new_content.len; i++)
    {
        new_content.content[i] = content->content[i + prefix_pos];
    }

    free_content(content);
    *content = new_content;

    return RET_SUCCESS;
}

int rstrip(struct content_t *content)
{
    size_t suffix_pos = 0;
    struct content_t new_content = null_content;

    if (content == NULL)
    {
        return RET_ERROR;
    }
    if (is_null_content(*content))
    {
        return RET_SUCCESS;
    }

    for (size_t i = content->len - 1; i >= 0; i--)
    {
        if (NOT(' ') && NOT('\t') && NOT('\n') && NOT('\r') && NOT('\v') && NOT('\f'))
        {
            suffix_pos = i + 1;
            break;
        }
    }
    new_content = alloc_content(suffix_pos);
    if (is_null_content(new_content))
    {
        return RET_ERROR;
    }

    for (size_t i = 0; i < new_content.len; i++)
    {
        new_content.content[i] = content->content[i];
    }

    free_content(content);
    *content = new_content;

    return RET_SUCCESS;
}

int strip(struct content_t *content)
{
    int ret;

    ret = lstrip(content);
    if (ret != RET_SUCCESS)
    {
        return ret;
    }

    ret = rstrip(content);
    if (ret != RET_SUCCESS)
    {
        return ret;
    }

    return RET_SUCCESS;
}
