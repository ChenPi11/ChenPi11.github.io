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

import (
	"os"
	"os/exec"
	"strings"

	"github.com/gookit/color"
	"github.com/leonelquinteros/gotext"
)

var markdownItExecutable []string = []string{"markdown-it"}

// Returns true if the command can be executed properly.
func checkCommandExists(cmd []string) bool {
	cmdCopy := make([]string, len(cmd)+1)
	copy(cmdCopy, cmd)
	cmdCopy[len(cmd)] = "--version"

	instance := exec.Command(cmd[0], cmdCopy[1:]...)
	if err := instance.Run(); err != nil {
		return false
	}
	return true
}

// Find the markdown-it executable.
func InitMarkdownIt() {
	color.Notice.Print(gotext.Get("Checking for markdown-it ... "))

	if checkCommandExists([]string{"npx", "markdown-it"}) {
		markdownItExecutable = []string{"npx", "markdown-it"}
	} else if checkCommandExists([]string{".venv/bin/markdown-it"}) {
		markdownItExecutable = []string{".venv/bin/markdown-it"}
	} else if checkCommandExists([]string{"venv/bin/markdown-it"}) {
		markdownItExecutable = []string{"venv/bin/markdown-it"}
	} else if checkCommandExists([]string{"markdown-it"}) {
		markdownItExecutable = []string{"markdown-it"}
	} else {
		markdownItEnv := os.Getenv("MARKDOWN_IT")
		splittedMarkdownItEnv := strings.Split(markdownItEnv, " ")
		if markdownItEnv == "" || checkCommandExists(splittedMarkdownItEnv) {
			markdownItExecutable = splittedMarkdownItEnv
		} else {
			markdownItEnv = os.Getenv("MARKDOWNIT")
			splittedMarkdownItEnv = strings.Split(markdownItEnv, " ")
			if markdownItEnv == "" || checkCommandExists(splittedMarkdownItEnv) {
				color.Notice.Print(gotext.Get("not found\n"))
				color.Error.Print(gotext.Get("Can't find markdown-it. Did you forget to run setup?\nYou can also set the MARKDOWN_IT environment variable.\n"))
				os.Exit(1)
			}
		}
	}

	if markdownItExecutable == nil {
		markdownItExecutable = []string{"markdown-it"}
	}

	color.Notice.Println(strings.Join(markdownItExecutable, " "))
}

// Render the markdown text using markdown-it.
func MarkdownIt(markdownText string) string {
	// Create temporary source file.
	tempInputFile, err := os.CreateTemp("", "post-tab-render-*.md")
	if err != nil {
		color.Error.Printf(gotext.Get("Error creating temporary file: %v\n"), err)
		os.Exit(1)
	}
	defer os.Remove(tempInputFile.Name())
	_, err = tempInputFile.WriteString(markdownText)
	if err != nil {
		color.Error.Printf(gotext.Get("Error writing to temporary file: %v\n"), err)
		os.Exit(1)
	}
	tempInputFile.Close()

	// Run the MarkdownIt command.
	args := append(markdownItExecutable[1:], tempInputFile.Name())
	if GetVerbose() {
		color.Notice.Printf(gotext.Get("Executing command %s %s ...\n"), markdownItExecutable[0], strings.Join(args, " "))
	}

	cmd := exec.Command(markdownItExecutable[0], args...)
	output, err := cmd.Output()
	if err != nil {
		color.Error.Printf(gotext.Get("Error while executing command: %v\n"), err)
		os.Exit(1)
	}

	return string(output)
}
