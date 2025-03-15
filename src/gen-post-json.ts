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

import { isChenPi11Blog } from "./is-blog.js";
import { loadPosts, Post } from "./post-meta.js";
import { logError } from "./log.js";
import { _, initI18n } from "./i18n.js";
import { setVerbose } from "./verbose.js";
import process from "process";
import * as fs from "fs";

/**
 * The meta data of a post.
 */
interface PostMeta {
    /**
     * The link of the post.
     */
    link: string;

    /**
     * The title of the post.
     */
    title: string;

    /**
     * The date of the post.
     */
    date: string;

    /**
     * The tags of the post.
     */
    tags: string[];

    /**
     * The description of the post.
     */
    desc: string;
}

/**
 * The meta data of the blog.
 *
 * @param {Post[]} posts The posts of the blog.
 * @returns {PostMeta[]} The meta data of the blog.
 */
function toPostMetas(posts: Post[]): PostMeta[] {
    const postsJson: PostMeta[] = [];
    posts.forEach((post) => {
        postsJson.push({
            link: post.getLink(),
            title: post.getTitle(),
            date: post.getDate(),
            tags: post.getTagList(),
            desc: post.getDescription(),
        });
    });
    return postsJson;
}

/**
 * Get the tags map of the blog.
 *
 * @param {Post[]} posts The posts of the blog.
 * @returns {Map<string, number>} The tags map of the blog.
 */
function getTagsMap(posts: Post[]): Map<string, number> {
    const tagMap: Map<string, number> = new Map();
    posts.forEach((post) => {
        post.getTagList().forEach((tag) => {
            if (tagMap.has(tag)) {
                tagMap.set(tag, tagMap.get(tag)! + 1);
            } else {
                tagMap.set(tag, 1);
            }
        })
    });
    return tagMap;
}

/**
 * Map to object.
 *
 * @param {Map<string, any>} map The map.
 * @returns {Record<string, any>} The object.
 */
function mapToObject(map: Map<string, any>): Record<string, any> {
    const obj: Record<string, any> = {};
    map.forEach((value, key) => {
        obj[key] = value;
    });
    return obj;
};

/**
 * Get the posts json of the blog.
 *
 * @param {Post[]} posts The posts of the blog.
 * @param {Map<string, number>} tagsMap The tags map of the blog.
 * @returns {string} The posts json of the blog.
 */
function getPostsJson(posts: Post[], tagsMap: Map<string, number>): string {
    const postsJson: PostMeta[] = toPostMetas(posts);
    const tags: string[] = Array.from(tagsMap.keys()).sort((a, b) => {
        return tagsMap.get(b)! - tagsMap.get(a)!;
    });
    const sortedTagsMap: Map<string, number> = new Map();
    tags.forEach((tag) => {
        sortedTagsMap.set(tag, tagsMap.get(tag)!);
    });

    return JSON.stringify({
        posts: postsJson,
        tags: mapToObject(sortedTagsMap),
    });
}

/**
 * Show the help message.
 */
function showHelp() {
    process.stdout.write(_("Usage: gen-post-json [-h|--help] [-V|--version] [-v|--verbose] <posts dir> <output file>\n"));
    process.stdout.write("\n");
    process.stdout.write(_("Options:\n"));
    process.stdout.write(_("  -h, --help     Display this help and exit.\n"));
    process.stdout.write(_("  -V, --version  Output version information and exit.\n"));
    process.stdout.write(_("  -v, --verbose  Verbosely report processing.\n"));
}

/**
 * Show the version information.
 */
function showVersion() {
    process.stdout.write("gen-post-json 0.1.0\n");
    process.stdout.write(_("Copyright (C) 2025 ChenPi11\n"));
    process.stdout.write(_("License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n"));
    process.stdout.write(_("This is free software: you are free to change and redistribute it.\n"));
    process.stdout.write(_("There is NO WARRANTY, to the extent permitted by law.\n"));
    process.stdout.write(_("Written by ChenPi11.\n"));
}

/**
 * The main function.
 */
function main() {
    initI18n();

    if (!isChenPi11Blog()) {
        logError(_("Not a chenpi11-blog project."));
        process.exit(1);
    }
    if (process.argv.includes("--help") || process.argv.includes("-h")) {
        showHelp();
        process.exit(0);
    }
    if (process.argv.includes("--version") || process.argv.includes("-V")) {
        showVersion();
        process.exit(0);
    }

    let args = process.argv.slice(2);
    if (process.argv.includes("--verbose") || process.argv.includes("-v")) {
        setVerbose(true);
        args = args.filter((arg) => {
            return arg != "--verbose" && arg != "-v";
        })
    } else {
        setVerbose(false);
    }
    if (args.length != 2) {
        logError(_("Usage: gen-post-json [-h|--help] [-V|--version] [-v|--verbose] <posts dir> <output file>\n"));
        process.exit(1);
    }

    try {
        const postsDir: string = args[0];
        const outputFile: string = args[1];

        const posts: Post[] = loadPosts(postsDir);
        const tagsMap: Map<string, number> = getTagsMap(posts);

        if (posts.length == 0) {
            throw new Error(_("No posts found."));
        }
        const jsonData = getPostsJson(posts, tagsMap);
        if (outputFile == "-") {
            process.stdout.write(jsonData);
            return;
        }
        fs.writeFileSync(outputFile, jsonData);
    }
    catch (exception: any) {
        logError(exception.message);
        process.exit(1);
    }
}

main();
