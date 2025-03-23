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

import { getCookie, setCookie } from "./cookie.js";
import { terminalThemes, defaultTerminalTheme } from "./themes-list.js";
import { getTheme, addThemeChangeCallback } from "./theme-loader.js";

/**
 * Get terminal theme data by its name. If not found, return default theme.
 *
 * @param {string} themeName 
 * @returns {object} Terminal theme data.
 */
export function getTermTheme(themeName) {
    if (themeName in terminalThemes) {
        return terminalThemes[themeName];
    }
    else {
        console.warn(`Terminal theme ${themeName} not found, using default theme.`);
        return terminalThemes[defaultTerminalTheme];
    }
}

/**
 * Get all terminal themes.
 *
 * @returns {Map<string, object>}
 */
export function listTermThemes() {
    return new Map(Object.entries(terminalThemes));
}

/**
 * Get preferred terminal theme name.
 *
 * @returns {string} Preferred terminal theme name.
 */
export function getPreferredTermThemeName() {
    let cookie_name = "term-theme";
    if (getTheme() == "dark") {
        cookie_name += "-dark";
    }
    let themeName = getCookie(cookie_name);
    if (themeName in terminalThemes) {
        return themeName;
    }
    return defaultTerminalTheme;
}

/**
 * Get preferred terminal theme.
 *
 * @returns {object} Terminal theme data.
 */
export function getPreferredTermTheme() {
    return getTermTheme(getPreferredTermThemeName());
}

/**
 * Set preferred terminal theme.
 *
 * @param {string} themeName Terminal theme name.
 */
export function setPreferredTermTheme(themeName) {
    if (!(themeName in terminalThemes)) {
        console.warn(`Terminal theme ${themeName} not found.`);
        return;
    }
    let cookie_name = "term-theme";
    if (getTheme() == "dark") {
        cookie_name += "-dark";
    }
    setCookie(cookie_name, themeName);
}

/**
 * List of terminals.
 *
 * @type {Terminal[]}
 */
let terminals = [];

addThemeChangeCallback(function () {
    let theme = getPreferredTermTheme();
    for (const terminal of terminals) {
        async function refresh() {
            terminal.options.theme = theme;
        }
        refresh();
    }
});

/**
 * Register a terminal to the terminal list.
 *
 * @param {Terminal} terminal Terminal object.
 */
export function registerTerminal(terminal) {
    terminals.push(terminal);
}

/**
 * Get preferred terminal font family.
 *
 * @returns {string} Preferred terminal font family.
 */
export function getPreferredTermFontFamily() {
    return "Meslo, monospace";
}

/**
 * Get preferred terminal font size.
 *
 * @returns {number} Preferred terminal font size.
 */
export function getPreferredTermFontSize() {
    return 14;
}
