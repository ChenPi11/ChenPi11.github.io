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

import { mo } from "gettext-parser";

import { osLocaleSync } from "os-locale";
import { existsSync, readFileSync, statSync } from "fs";

/**
 * The root directory for executable and libraries.
 */
const ROOT_DIR = "./.venv";

/**
 * The name of the package.
 */
const PACKAGE_NAME = "chenpi11-blog";

/**
 * The map of the translated texts.
 */
const i18nMap = new Map<string, string>();

/**
 * Initializes the i18n module.
 */
export function initI18n() {
    const locale = osLocaleSync().replace(/-/g, "_");
    const moFile = `${ROOT_DIR}/share/locale/${locale}/LC_MESSAGES/${PACKAGE_NAME}.mo`;
    if (existsSync(moFile)) {
        const poContent = readFileSync(moFile);
        const poo = mo.parse(poContent);
        const translations = poo.translations[""];
        for (const key in translations) {
            const msg = translations[key];
            if (msg.msgstr.length > 0) {
                i18nMap.set(key, msg.msgstr[0]);
            }
        }
    }
}

/**
 * Gets the translated text.
 *
 * @param key The key of the text.
 * @returns The translated text. If the key is not found, returns the key.
 */
export function getText(key: string): string {
    if (i18nMap.has(key)) {
        return i18nMap.get(key)!;
    }
    return key;
}

/**
 * Gets the translated text.
 *
 * @param key The key of the text.
 * @returns The translated text. If the key is not found, returns the key.
 */
export const _ = getText;
