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

import { getTerminal, fprintf } from "/lib/terminal.js";

$(function () {
    const _ = getTerminal("80x25");
    const term = _.terminal;
    const stdin = _.stdin;

    async function random_tty_color() {
        const colors = [
            40, 41, 42, 43, 44, 45, 46, 47,
            100, 101, 102, 103, 104, 105, 106, 107,
        ]
        return `\x1b[${colors[Math.floor(Math.random() * colors.length)]}m \x1b[0m`;
    }

    async function main() {
        for (let y = 0; y < 25; y++) {
            for (let x = 0; x < 80; x++) {
                fprintf(term, "%s", await random_tty_color());
            }
            fprintf(term, "\n");
        }
    }
    main();
});
