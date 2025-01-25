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

const theme_neon = {
    "foreground": "#F8F8F8",
    "background": "#171717",
    "cursor": "#F8F8F8",
    "black": "#171717",
    "brightBlack": "#878787",
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

const theme_warm_neon = {
    foreground: '#AFDAB6',
    background: '#404040',
    cursor: '#30FF24',
    black: '#000000',
    brightBlack: '#FEFCFC',
    red: '#E24346',
    brightRed: '#E97071',
    green: '#39B13A',
    brightGreen: '#9CC090',
    yellow: '#DAE145',
    brightYellow: '#DDDA7A',
    blue: '#4261C5',
    brightBlue: '#7B91D6',
    magenta: '#F920fB',
    brightMagenta: '#F674BA',
    cyan: '#2ABBD4',
    brightCyan: '#5ED1E5',
    white: '#D0B8A3',
    brightWhite: '#D8C8BB'
}

document.addEventListener("DOMContentLoaded", function () {
    setTheme("dark");
    syncThemeButton();

    const terminalContainer = document.getElementById("terminal");
    const terminal = new Terminal({
        theme: theme_neon,
        fontFamily: "Meslo, monospace",
        fontSize: 14,
        scrollback: 9999999,
    });
    const fitAddon = new FitAddon.FitAddon();

    terminal.loadAddon(fitAddon);
    terminal.open(terminalContainer);
    fitAddon.fit();

    fetch("buildlog.txt")
        .then(response => {
            if (!response.ok) {
                throw new Error(`Network response was not ok ${response.statusText}`);
            }
            response.text()
                .then(text => {
                    const lines = text.split("\n");
                    for (let i = 0; i < lines.length; i++) {
                        terminal.writeln(lines[i]);
                    }
                })
                .catch(error => {
                    console.error("Error reading file:", error);
                    terminal.writeln(`\x1b[31mError reading file: ${error}\x1b[0m`);
                }
                );
        })
        .catch(error => {
            console.error("There was a problem with the fetch operation:", error);
            terminal.writeln(`\x1b[31mError fetching file: ${error}\x1b[0m`);
        });

    window.addEventListener("resize", () => fitAddon.fit());
    document.body.style.overflow = "hidden";

    function onThemeChange(theme) {
        if (theme == "dark") {
            terminal.options.theme = theme_neon;
        }
        else {
            terminal.options.theme = theme_warm_neon;
        }
    }

    addThemeChangeCallback(onThemeChange);
});
