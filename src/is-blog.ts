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

import { existsSync, statSync } from "fs";

/**
 * Checks if a file exists and is a file.
 * 
 * @param isFile Path to check.
 * @returns True if the file exists and is a file.
 */
function isFile(isFile: string): boolean {
    return existsSync(isFile) && statSync(isFile).isFile();
}

/**
 * Checks if a file exists and is a directory.
 * 
 * @param isFile Path to check.
 * @returns True if the file exists and is a directory.
 */
function isDir(isFile: string): boolean {
    return existsSync(isFile) && statSync(isFile).isDirectory();
}

/**
 * Checks if the current directory is a chenpi11-blog project.
 * 
 * @returns True if the current directory is a chenpi11-blog project.
 */
export function isChenPi11Blog(): boolean {
    return (
        isDir(".")
        && isFile("requirements.txt") && isFile("pyproject.toml") // It's a Python project.
        && isFile("Cargo.toml") && isFile("Makefile.toml")  // It's a Rust project.
        && isFile("configure.ac") && isFile("autogen.sh")  // It's an Autotools project.
        && isFile("CMakeLists.txt")  // It's a CMake project.
        && isFile("package.json")  // It's a Node.js project.
        && isFile("Makefile.in")  // It's an Autoconf+Makefile project.
        && isFile("repo.json")  // It's a Rubisco project.
    )
}
