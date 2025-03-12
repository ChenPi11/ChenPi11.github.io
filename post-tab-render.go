// Copyright (C) 2025 ChenPi11.
// This file is part of chenpi11-blog.
//
// chenpi11-blog is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// chenpi11-blog is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with chenpi11-blog.  If not, see <https://www.gnu.org/licenses/>.

package main

import (
	"os"
	"path/filepath"
	"strings"

	"chenpi11.github.io/post-tab-render/chenpi11_blog"
	"github.com/gookit/color"
	"github.com/leonelquinteros/gotext"
)

// Posts directory.
const POSTS_DIR = "posts"

// Show version information.
func showVersion() {
	print("post-tab-render 0.1.0\n")
	print(gotext.Get("Copyright (C) 2025 ChenPi11\n"))
	print(gotext.Get("License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n"))
	print(gotext.Get("This is free software: you are free to change and redistribute it.\n"))
	print(gotext.Get("There is NO WARRANTY, to the extent permitted by law.\n"))
	print(gotext.Get("Written by ChenPi11.\n"))
}

// Show help information.
func showHelp() {
	print(gotext.Get("Usage: post-tab-render [-h|--help] [-V|--version] [-v|--verbose]\n"))
	print("\n")
	print(gotext.Get("Options:\n"))
	print(gotext.Get("  -h, --help     Display this help and exit.\n"))
	print(gotext.Get("  -V, --version  Output version information and exit.\n"))
	print(gotext.Get("  -v, --verbose  Verbosely report processing.\n"))
}

func init() {
	chenpi11_blog.InitI18n()
}

func main() {
	if !chenpi11_blog.IsChenPi11Blog() {
		color.Notice.Print(gotext.Get("You must run post-tab-render in project's root directory!\n"))
		os.Exit(1)
	}

	args := os.Args[1:]
	if args == nil {
		showHelp()
		os.Exit(0)
	}
	for _, arg := range args {
		if arg == "-h" || arg == "--help" {
			showHelp()
			os.Exit(0)
		}
		if arg == "-V" || arg == "--version" {
			showVersion()
			os.Exit(0)
		}
		if arg == "-v" || arg == "--verbose" {
			chenpi11_blog.SetVerbose(true)
		}
	}

	chenpi11_blog.InitMarkdownIt()

	err := filepath.Walk(POSTS_DIR, func(path string, info os.FileInfo, err error) error {
		if err != nil {
			// Fucking golang and its stupid warning.
			color.Error.Printf(gotext.Get("Error accessing path %s: %v\n"), path, err)
			return err
		}

		if !info.IsDir() && strings.HasSuffix(info.Name(), ".html") {
			chenpi11_blog.RenderingTabOfHTMLFile(path)
		}
		return nil
	})

	if err != nil {
		color.Error.Print(gotext.Get("Error walking the path %q: %v\n"), POSTS_DIR, err)
	}
}
