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

#ifndef _POST_HASH_H_
#define _POST_HASH_H_

#include "post.h"

struct content_t to_md5(struct content_t content);

/*
 * Read the hash file and check if the post is the latest one.
 * Set the post's last_modified if the post is the latest one.
 * Return TRUE if the post is the latest one, FALSE otherwise.
 */
extern int post_is_latest(struct post_t *post);

/* Update the hash file. */
extern int update_hash(struct post_t *post);

#endif
