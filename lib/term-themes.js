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

export function getTermTheme(themeName)
{
    if (themeName in terminalThemes)
    {
        return terminalThemes[themeName];
    }
    else
    {
        console.warn(`Terminal theme ${themeName} not found, using default theme.`);
        return terminalThemes[defaultTerminalTheme];
    }
}

export function listTermThemes()
{
    return new Map(Object.entries(terminalThemes));
}

export function getPreferredTermThemeName()
{
    let themeName = getCookie("term-theme");
    if (themeName in terminalThemes)
    {
        return themeName;
    }
    return defaultTerminalTheme;
}

export function getPreferredTermTheme()
{
    return getTermTheme(getPreferredTermThemeName());
}

export function setPreferredTermTheme(themeName)
{
    if (!(themeName in terminalThemes))
    {
        console.warn(`Terminal theme ${themeName} not found.`);
        return;
    }
    setCookie("term-theme", themeName);
}
