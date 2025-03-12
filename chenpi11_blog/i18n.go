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
	"path/filepath"
	"strings"

	"github.com/Xuanwo/go-locale"
	"github.com/leonelquinteros/gotext"
	"golang.org/x/text/language"
)

// Package name.
const PACKAGE_NAME = "chenpi11-blog"

// Returns true if the path is a directory.
func isChenPi11BlogLocaleDir(path string) bool {
	return isDir(path) && isFile(filepath.Join(path, "zh_CN", "LC_MESSAGES", PACKAGE_NAME+".mo"))
}

// Initialize i18n module.
func InitI18n() {
	var localeDir string
	if isChenPi11BlogLocaleDir(".venv/share/locale") {
		localeDir = ".venv/share/locale"
	} else if isChenPi11BlogLocaleDir("/usr/local/share/locale") {
		localeDir = "/usr/local/share/locale"
	} else {
		localeDir = "/usr/share/locale"
	}

	localeTag, errd := locale.Detect()
	if errd != nil || localeTag == language.Und {
		localeTag = language.English
	}

	localeTagName := localeTag.String()
	localeTagName = strings.ReplaceAll(localeTagName, "-", "_")

	gotext.Configure(localeDir, localeTagName, PACKAGE_NAME)
}
