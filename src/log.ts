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

import { _ } from "./i18n.js";
import { stderr } from "process";
import { getVerbose } from "./verbose.js";

/**
 * Logs a message to stderr.
 *
 * @param msg Message to log.
 * @param control Control code.
 */
function logMsg(msg: string, control: string) {
    if (!msg.endsWith("\n")) {
        msg += "\n";
    }
    if (stderr.isTTY) {
        msg = `\x1b[${control}m${msg}\x1b[0m`;
    }
    stderr.write(msg);
}

/**
 * Logs a verbose message to stderr.
 *
 * @param msg Message to log.
 */
export function logVerbose(msg: string) {
    if (getVerbose())
    {
        logMsg(msg, "32");
    }
}

/**
 * Logs a info message to stderr.
 *
 * @param msg Message to log.
 */
export function logInfo(msg: string) {
    logMsg(msg, "34");
}

/**
 * Logs a error message to stderr.
 *
 * @param msg Message to log.
 */
export function logError(msg: string) {
    logMsg(_("ERROR: ") + msg, "31");
}
