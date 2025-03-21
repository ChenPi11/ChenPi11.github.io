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

/**
 * Program verbose level.
 */
var verboseEnabled: boolean = false;

/**
 * Set program verbose level.
 *
 * @param verbose Set it to true for verbose mode. Normal mode otherwise.
 */
export function setVerbose(verbose: boolean) {
    verboseEnabled = verbose;
}


/**
 * Get program verbose level.
 *
 * @returns The program verbose level.
 */
export function getVerbose(): boolean {
    return verboseEnabled;
}
