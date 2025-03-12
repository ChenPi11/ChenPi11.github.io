/*
Copyright (C) 2025 ChenPi11.
This file is part of chenpi11-blog.

chenpi11-blog is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

chenpi11-blog is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with chenpi11-blog.  If not, see <https://www.gnu.org/licenses/>. */

package chenpi11_blog

import "os"

// Check if the path is a regular file.
func isFile(path string) bool {
	info, err := os.Stat(path)
	if err != nil {
		return false
	}
	return info.Mode().IsRegular()
}

// Check if the path is a directory.
func isDir(path string) bool {
	info, err := os.Stat(path)
	if err != nil {
		return false
	}
	return info.IsDir()
}

// Check if the path is a chenpi11-blog.
func IsChenPi11Blog() bool {
	result := isDir(".")
	result = result && isFile("requirements.txt") && isFile("pyproject.toml") // It's a Python project.
	result = result && isFile("Cargo.toml") && isFile("Makefile.toml")        // It's a Rust project.
	result = result && isFile("configure.ac") && isFile("autogen.sh")         // It's an Autotools project.
	result = result && isFile("CMakeLists.txt")                               // It's a CMake project.
	result = result && isFile("package.json")                                 // It's a Node.js project.
	result = result && isFile("Makefile.in")                                  // It's an Autoconf+Makefile project.
	result = result && isFile("repo.json")                                    // It's a Rubisco project.
	result = result && isFile("tsconfig.json")                                // It's a TypeScript project.
	result = result && isFile("go.mod")                                       // It's a Go project.

	return result
}
