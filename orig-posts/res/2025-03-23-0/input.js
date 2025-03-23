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

"use strict";

import { getTerminal, fprintfln, input } from "/lib/terminal.js";
import { playBell } from "/lib/bell.js";

$(function () {
    const _ = getTerminal("input");
    const term = _.terminal;
    const stdin = _.stdin;

    async function main() {
        fprintfln(term, "请注意：Terminal Applet 对于输入的支持是实验性的！");
        playBell();
        while (true) {
            const input_str = await input(term, stdin, "> ");
            if (input_str === "ls") {
                fprintfln(term, "a.txt b.txt c.txt a.c a.js package.json");
            } else if (input_str === "cat a.txt") {
                fprintfln(term, "Hello, world!");
            } else if (input_str === "cat b.txt") {
                fprintfln(term, "BBBBBBBBBB");
            } else if (input_str === "cat c.txt") {
                fprintfln(term, "CCCCCCCCCC");
            } else if (input_str === "cat a.c") {
                fprintfln(term, "#include <stdio.h>");
                fprintfln(term, "int main() {");
                fprintfln(term, "    printf(\"Hello, world!\\n\");");
                fprintfln(term, "    return 0;");
                fprintfln(term, "}");
            } else if (input_str === "cat a.js") {
                fprintfln(term, "console.log(\"Hello, world!\");");
            } else if (input_str === "cat package.json") {
                fprintfln(term, "{");
                fprintfln(term, "    \"name\": \"chenpi11-blog\",");
                fprintfln(term, "    \"version\": \"1.0.0\",");
                fprintfln(term, "    \"description\": \"chenpi11-blog is a blog built with Vue.js and Vite.js.\"");
                fprintfln(term, "}");
            } else if (input_str === "help") {
                fprintfln(term, "ls: list files");
                fprintfln(term, "cat <file>: print file content");
                fprintfln(term, "help: print this help message");
                fprintfln(term, "bell: play bell sound");
            } else if (input_str === "bell") {
                playBell();
            }
            else {
                fprintfln(term, "command not found: %s. type \"help\" for help", input_str);
            }
        }
    }
    main();
});
