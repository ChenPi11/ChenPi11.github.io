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
    const _ = getTerminal("example");
    const stdout = _.terminal;
    const stdin = _.stdin;

    // Evil hack.
    let needStop = false;
    $(`#example`).get(0).terminal.onData(function (data) {
        if (data === "\u0003") {
            needStop = true;
        }
    });

    async function main() {
        try {
            while (true) {
                await input(stdout, stdin, "键入 Enter 以开始，Ctrl+C 以重置 > ");
                fprintfln(stdout, "Destroying 4294967295");
                playBell();
                fprintfln(stdout, "Destroying 0");
                while (!needStop) {
                    fprintfln(stdout, ">>> Invalid syntax.");
                    await new Promise((resolve) => setTimeout(resolve, 1000));
                }
                fprintfln(stdout, "^C");
                await input(stdout, stdin, "键入 Enter 以重置 > ");
                needStop = false;
                $(`#example`).get(0).terminal.clear();
            }
        }
        catch (e) {
            fprintfln(stdout, `错误: ${e}`);
        }
    }
    main();
});
