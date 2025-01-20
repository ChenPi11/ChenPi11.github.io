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

const xterm_css = "xterm/css/xterm.css"
const xterm_js = "xterm/lib/xterm.js";

// Insert CSS
let xterm_css_tag = document.createElement("link");
xterm_css_tag.href = xterm_css;
xterm_css_tag.rel = "stylesheet";
document.head.appendChild(xterm_css_tag);

// Insert JS
let xterm_js_tag = document.createElement("script");
xterm_js_tag.src = xterm_js;
xterm_js_tag.type = "text/javascript";
document.head.appendChild(xterm_js_tag);

function initTerminal() {
    const theme_neon = {
        "foreground": "#F8F8F8",
        "background": "#171717",
        "cursor": "#F8F8F8",
        "black": "#171717",
        "brightBlack": "#38252C",
        "red": "#D81765",
        "brightRed": "#FF0000",
        "green": "#97D01A",
        "brightGreen": "#76B639",
        "yellow": "#FFA800",
        "brightYellow": "#E1A126",
        "blue": "#16B1FB",
        "brightBlue": "#289CD5",
        "magenta": "#FF2491",
        "brightMagenta": "#FF2491",
        "cyan": "#0FDCB6",
        "brightCyan": "#0A9B81",
        "white": "#EBEBEB",
        "brightWhite": "#F8F8F8"
    }

    let term = new Terminal({
        theme: theme_neon,
        fontFamily: "Meslo, monospace",
        fontSize: 14,
        scrollback: 9999999
    });

    term.open(document.getElementById("terminal"));

    fetch("buildlog.txt")
        .then(response => {
            if (!response.ok) {
                throw new Error(`Network response was not ok ${response.statusText}`);
            }
            response.text()
                .then(text => {
                    const lines = text.split("\n");
                    for (let i = 0; i < lines.length; i++) {
                        term.writeln(lines[i]);
                    }
                })
                .catch(error => {
                    console.error("Error reading file:", error);
                    term.writeln(`\x1b[31mError reading file: ${error}\x1b[0m`);
                }
                );
        })
        .catch(error => {
            console.error("There was a problem with the fetch operation:", error);
            term.writeln(`\x1b[31mError fetching file: ${error}\x1b[0m`);
        });

}

// Wait for JS to load
xterm_js_tag.onload = initTerminal
