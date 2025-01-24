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

#include "post.h"

#include "configure.h"
#include "content.h"
#include "defines.h"
#include "file-util.h"
#include "log.h"
#include "markdown-it.h"

#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char *post_template_file = NULL;

static struct tags_t parse_tags(struct content_t line)
{
    struct tags_t tags = null_tags;
    struct content_t *ptags = NULL;
    size_t num = 0;
    char *token = NULL;

    token = strtok(line.content, TAGS_SEP);
    while (token != NULL)
    {
        struct content_t tag = null_content;
        struct content_t *tmp = NULL;

        tag = alloc_content(strlen(token));
        if (is_null_content(tag))
        {
            goto ERROR;
        }
        memcpy(tag.content, token, tag.len);
        tag.content[tag.len] = '\0';
        num++;

        tmp = realloc(ptags, num * sizeof(struct content_t));
        if (tmp == NULL)
        {
            free_content(&tag);
            die("Cannot reallocate memory.\n");
        }
        ptags = tmp;
        memcpy(ptags + num - 1, &tag, sizeof(struct content_t));
        token = strtok(NULL, TAGS_SEP);
    }

    tags.num = num;
    tags.first = ptags;

    return tags;

ERROR:
    tags.first = ptags; // So free_tags() can free tags.
    free_tags(&tags);
    return null_tags;
}

static int check_duplicate_tags(struct tags_t tags)
{
    for (size_t i = 0; i < tags.num; i++)
    {
        for (size_t j = i + 1; j < tags.num; j++)
        {
            if (strcmp(tags.first[i].content, tags.first[j].content) == 0)
            {
                die("Duplicate tag: \"%s\"\n", tags.first[i].content);
            }
        }
    }

    return FALSE;

ERROR:
    return TRUE;
}

void post_init(const char *template_file)
{
    if (template_file == NULL)
    {
        die("Post template file is NULL.\n");
    }
    info("Using %s as post template\n", template_file);
    post_template_file = template_file;

    return;

ERROR:
    exit(EXIT_FAILURE);
}

struct post_t load_post(const char *filepath)
{
    struct post_t post = null_post;
    const char *basename = NULL;
    char *dot_pos = NULL;
    FILE *file = NULL;
    struct content_t line = null_content;

    /* Filename. */
    basename = file_basename(filepath);
    post.filename = alloc_content(strlen(basename));
    if (is_null_content(post.filename))
    {
        return null_post;
    }
    memcpy(post.filename.content, basename, post.filename.len);
    post.filename.content[post.filename.len] = '\0';

    dot_pos = strchr(post.filename.content, '.');
    if (dot_pos != NULL)
    {
        *dot_pos = '\0';
    }

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        die("Cannot open file: %s\n", filepath);
    }

    /* Title. */
    line = read_line(file, filepath);
    if (!startswith(line, CONTENT(TITLE_START)))
    {
        warn("First line must start with \"# \"\n");
        die("First line of %s is not a title\n", filepath);
    }
    post.title = alloc_content(line.len - 2);
    if (is_null_content(post.title))
    {
        goto ERROR;
    }
    memcpy(post.title.content, line.content + 2, post.title.len);
    post.title.content[post.title.len] = '\0';
    if (strip(&post.title) != RET_SUCCESS)
    {
        die("Cannot strip title.\n");
    }
    free_content(&line);

    /* Date. */
    line = read_line(file, filepath);
    if (!startswith(line, CONTENT(DATE_START)))
    {
        warn("Second line must start with \"" DATE_START "\"\n");
        die("Second line of %s is not a date\n", filepath);
    }
    if (!endswith(line, CONTENT(DATE_END)))
    {
        warn("Second line must end with \"" DATE_END "\"\n");
        die("Second line of %s is not a date.\n", filepath);
    }
    if (line.len <= strlen(DATE_END) + strlen(DATE_START))
    {
        fclose(file);
        free_content(&line);
        free_post(&post);
        warn("Second line must contain a date.\n");
        die("Second line of %s is not a date.\n", filepath);
    }
    post.date = alloc_content(line.len - strlen(DATE_END) - strlen(DATE_START));
    if (is_null_content(post.date))
    {
        goto ERROR;
    }
    memcpy(post.date.content, line.content + strlen(DATE_START), post.date.len);
    post.date.content[post.date.len] = '\0';
    if (strip(&post.date) != RET_SUCCESS)
    {
        die("Cannot strip date.\n");
    }
    free_content(&line);

    /* Tags. */
    line = read_line(file, filepath);
    if (!startswith(line, CONTENT(TAG_START)))
    {
        warn("Third line must start with \"" TAG_START "\"\n");
        die("Third line of %s is not a tag\n", filepath);
    }
    if (!endswith(line, CONTENT(TAG_END)))
    {
        warn("Third line must end with \"" TAG_END "\"\n");
        die("Third line of %s is not a tag.\n", filepath);
    }
    if (line.len <= strlen(TAG_END) + strlen(TAG_START))
    {
        warn("Third line must contain a tag.\n");
        die("Third line of %s is not a tag.\n", filepath);
    }

    line.content[line.len - strlen(TAG_END)] = '\0';
    line.content += strlen(TAG_START);
    post.tags = parse_tags(line);
    if (check_duplicate_tags(post.tags))
    {
        goto ERROR;
    }

    post.content = read_file(filepath);
    if (is_null_content(post.content))
    {
        goto ERROR;
    }

    close_file(file);

    return post;

ERROR:
    free_post(&post);
    close_file(file);

    return null_post;
}

int save_post(struct post_t post)
{
    char out_filename[BUFSIZ];
    char postinfo_filename[BUFSIZ];
    char tmp_filename[BUFSIZ];
    FILE *tmpfile = NULL;
    struct content_t html_snippet = null_content;
    FILE *postinfo = NULL;

    init_struct(out_filename);
    init_struct(postinfo_filename);
    init_struct(tmp_filename);

    if (snprintf(out_filename, BUFSIZ, POST_OUTPUT_DIR "%s.html", post.filename.content) < 0)
    {
        die("Cannot generate filename.\n");
    }
    if (snprintf(postinfo_filename, BUFSIZ, POST_OUTPUT_DIR "%s.info", post.filename.content) < 0)
    {
        die("Cannot generate filename.\n");
    }
    if (snprintf(tmp_filename, BUFSIZ, POST_OUTPUT_DIR "%s.html.tmp", post.filename.content) < 0)
    {
        die("Cannot generate filename.\n");
    }

    info("Generating %s ...\n", out_filename);

    if (copy_file(post_template_file, out_filename) != RET_SUCCESS)
    {
        die("Cannot copy file: %s\n", post_template_file);
    }

    tmpfile = fopen(tmp_filename, "wb");
    if (tmpfile == NULL)
    {
        die("Cannot open file: %s\n", tmp_filename);
    }
    if (fwrite(post.content.content, sizeof(char), post.content.len, tmpfile) != post.content.len)
    {
        die("Cannot write to file: %s\n", tmp_filename);
    }

    close_file(tmpfile);

    html_snippet = markdown_it_tohtml(tmp_filename);
    if (is_null_content(html_snippet))
    {
        die("Cannot convert markdown to html.\n");
    }

    if (remove_file(tmp_filename) != RET_SUCCESS)
    {
        die("Cannot remove file: %s\n", tmp_filename);
    }

    struct configure_t configures_[] = {PAIR("CONTENT", html_snippet.content), PAIR("SUBTITLE", post.title.content)};

    if (configure(create_configures(configures_), out_filename) != RET_SUCCESS)
    {
        die("Cannot configure file: %s\n", out_filename);
    }

    postinfo = fopen(postinfo_filename, "w");
    if (postinfo == NULL)
    {
        free_content(&html_snippet);
        die("Cannot open file: %s\n", postinfo_filename);
    }

    if (fprintf(postinfo, "%s\n", post.title.content) < 0)
    {
        die("Cannot write to file: %s\n", postinfo_filename);
    }
    if (fprintf(postinfo, "%s\n", post.date.content) < 0)
    {
        die("Cannot write to file: %s\n", postinfo_filename);
    }

    for (size_t i = 0; i < post.tags.num; i++)
    {
        if (fprintf(postinfo, "%s%s", post.tags.first[i].content, i == post.tags.num - 1 ? "\n" : ",") < 0)
        {
            die("Cannot write to file: %s\n", postinfo_filename);
        }
    }

    free_content(&html_snippet);
    close_file(postinfo);

    return RET_SUCCESS;
ERROR:

    free_content(&html_snippet);
    close_file(postinfo);
    close_file(tmpfile);

    return RET_ERROR;
}

void free_tags(struct tags_t *tags)
{
    if (tags == NULL)
    {
        return;
    }

    for (size_t i = 0; i < tags->num; i++)
    {
        free_content(&tags->first[i]);
    }
}

void free_post(struct post_t *post)
{
    if (post == NULL)
    {
        return;
    }

    free_content(&post->filename);
    free_content(&post->title);
    free_content(&post->date);
    free_tags(&post->tags);
}
