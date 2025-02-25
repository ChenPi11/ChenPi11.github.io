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

import { logInfo } from "./log.js";
import { _ } from "./i18n.js";
import { sprintf } from "sprintf-js";
import { fstat, readFileSync, readdirSync } from "fs";
import upath from "upath";

/**
 * Post meta info.
 * 
 * @author ChenPi11
 * @export
 * @class Post
 * @implements {Post}
 */
export class Post {
    private link: string;
    private title: string;
    private date: string;
    private tags: Set<string>;

    /**
     * Creates an instance of Post.
     *
     * @param {string} link Link of the post.
     * @param {string} title Title of the post.
     * @param {string} date Date of the post.
     * @param {string[]} tags Tags of the post.
     * @memberof Post
     */
    constructor(link:string, title: string, date: string, tags: string[]) {
        this.link = link;
        this.title = title;
        this.date = date;
        this.tags = new Set(tags);
    }

    /**
     * Returns the link of the post.
     *
     * @returns {string} Link of the post.
     * @memberof Post
     */
    getLink(): string {
        return this.link;
    }

    /**
     * Returns the tag list of the post.
     * 
     * @returns {string[]} Tag list of the post.
     * @memberof Post
     */
    getTagList(): string[] {
        return Array.from(this.tags);
    }

    /**
     * Returns the title of the post.
     * 
     * @returns {string} Title of the post.
     * @memberof Post
     */
    getTitle(): string {
        return this.title;
    }

    /**
     * Returns the date of the post.
     *
     * @returns {string} Date of the post.
     * @memberof Post
     */
    getDate(): string {
        return this.date;
    }
}

/**
 * Loads a post from a file.
 * 
 * @param {string} filePath Path of the file.
 * @returns {Post} Post loaded from the file.
 */
function loadPost(filePath: string): Post {
    const link = upath.basename(filePath, ".html");
    const content = readFileSync(filePath, "utf-8");
    const lines = content.split("\n");
    const title = lines[0];
    const date = lines[1];
    const tags = lines[2].split(",");

    return new Post(link, title, date, tags);
}

/**
 * Loads all posts from a directory.
 * 
 * @param {string} postDir Directory of the posts.
 * @returns {Post[]} Posts loaded from the directory.
 */
export function loadPosts(postDir: string): Post[] {
    const posts: Post[] = [];
    readdirSync(postDir).forEach((file) => {
        const filePath = upath.join(postDir, file);
        if (upath.extname(file) === ".info") {
            posts.push(loadPost(filePath));
            logInfo(sprintf(_("Loaded post: %s"), file));
        }
    })
    return posts;
}
