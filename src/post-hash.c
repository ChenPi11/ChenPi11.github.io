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

#include "post-hash.h"

#include "content.h"
#include "defines.h"
#include "file-util.h"
#include "i18n.h"
#include "log.h"
#include "post.h"

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int post_is_latest(struct post_t *post)
{
    char hash_file_path[PATH_MAX];
    FILE *hash_file = NULL;
    struct content_t current_hash = null_content;
    struct content_t hash = null_content;
    struct content_t date = null_content;
    int ret = FALSE;

    init_struct(hash_file_path);

    if (snprintf(hash_file_path, PATH_MAX, "posts/hash/%s.hash", post->filename.content) < 0)
    {
        die(_("snprintf() failed.\n"));
    }

    if (!is_file(hash_file_path))
    {
        ret = FALSE;
        goto END;
    }

    hash_file = fopen(hash_file_path, "r");
    if (hash_file == NULL)
    {
        die(_("Cannot open file: %s\n"), hash_file_path);
        goto ERROR;
    }

    hash = read_line(hash_file, hash_file_path);
    if (is_null_content(hash))
    {
        warn(_("Cannot read file: %s\n"), hash_file_path);
        goto END;
    }
    date = read_line(hash_file, hash_file_path);
    if (is_null_content(date))
    {
        warn(_("Cannot read file: %s\n"), hash_file_path);
        goto END;
    }

    current_hash = to_md5(post->content);

    if (strcmp(hash.content, current_hash.content) == 0)
    {
        ret = TRUE;
        /* Set the post's last modified date. */
        post->last_modified = date;
    }

END:
    free_content(&current_hash);
    free_content(&hash);
    close_file(hash_file);

    return ret;
ERROR:

    free_content(&current_hash);
    free_content(&hash);
    close_file(hash_file);

    return RET_ERROR;
}

int update_hash(struct post_t *post)
{
    char hash_file_path[PATH_MAX];
    struct content_t md5 = null_content;
    struct content_t date = null_content;
    int is_latest = FALSE;
    time_t cur_time = 0;
    struct tm *time_info = NULL;
    FILE *hash_file = NULL;
    char time_buffer[80];

    init_struct(hash_file_path);
    init_struct(time_buffer);

    if (snprintf(hash_file_path, PATH_MAX, "posts/hash/%s.hash", post->filename.content) < 0)
    {
        die(_("snprintf() failed.\n"));
    }

    is_latest = post_is_latest(post);
    if (is_latest == RET_ERROR)
    {
        goto ERROR;
    }
    if (is_latest)
    {
        info(_("The post %s is the latest, skip update.\n"), post->filename.content);
        goto UPDATE_SUCCESS;
    }

    if (!is_dir("posts/hash"))
    {
        if (mkdir("posts/hash", 0755) != 0)
        {
            die(_("Cannot create directory: %s\n"), "posts/hash");
            goto ERROR;
        }
    }

    info("Update hash for post: \"%s\" (%s)\n", post->title.content, post->filename.content);

    /* Update the hash file. */
    if (time(&cur_time) == ((time_t)-1))
    {
        die(_("time() failed.\n"));
        goto ERROR;
    }

    time_info = localtime(&cur_time);
    if (time_info == NULL)
    {
        die(_("localtime() failed.\n"));
        goto ERROR;
    }

    if (strftime(time_buffer, sizeof(time_buffer), "%Y/%m/%d", time_info) == 0)
    {
        die(_("strftime() failed.\n"));
    }

    date = alloc_content(strlen(time_buffer) + 1);
    if (is_null_content(date))
    {
        die(_("Cannot allocate memory.\n"));
        goto ERROR;
    }
    memcpy(date.content, time_buffer, strlen(time_buffer) + 1);
    post->last_modified = date;

    md5 = to_md5(post->content);
    if (is_null_content(md5))
    {
        die(_("Cannot compute MD5 hash.\n"));
        goto ERROR;
    }

    hash_file = fopen(hash_file_path, "w");
    if (hash_file == NULL)
    {
        die(_("Cannot open file: %s\n"), hash_file_path);
        goto ERROR;
    }

    if (fprintf(hash_file, "%s\n%s\n", md5.content, date.content) < 0)
    {
        die(_("Cannot write to file: %s\n"), hash_file_path);
        goto ERROR;
    }

UPDATE_SUCCESS:
    close_file(hash_file);
    free_content(&md5);

    return RET_SUCCESS;
ERROR:

    close_file(hash_file);
    free_content(&md5);

    return RET_ERROR;
}
