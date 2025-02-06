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

import { getPreferredTermTheme } from './term-themes.js';

$(function () {
    const terminalContainer = $("#terminal");
    const terminal = new Terminal({
        theme: getPreferredTermTheme(),
        fontFamily: "Meslo, monospace",
        fontSize: 14,
        scrollback: 9999999,
    });
    const fitAddon = new FitAddon.FitAddon();

    terminal.loadAddon(fitAddon);
    terminal.open(terminalContainer.get(0));
    fitAddon.fit();

    const buildLogUrl = "/buildlog.txt";
    fetch(buildLogUrl)
        .then(response => {
            if (!response.ok) {
                throw new Error(response.statusText);
            }
            response.text()
                .then(text => {
                    const lines = text.split("\n");
                    for (let i = 0; i < lines.length; i++) {
                        terminal.writeln(lines[i]);
                    }
                })
                .catch(error => {
                    throw new Error(error);
                });
        })
        .catch(error => {
            console.error("Error while reading file: ", error);
            terminal.writeln(`\x1b[31mError while reading file ${buildLogUrl} : ${error}\x1b[0m`);
        });

    $(window).on("resize", () => fitAddon.fit());
    $(document).css("overflow", "hidden");

    function onThemeChange(theme) {
        if (theme == "dark") {
            // terminal.options.theme = theme_neon;
        }
        else {
            // terminal.options.theme = theme_warm_neon;
        }
    }

    addThemeChangeCallback(onThemeChange);
});
