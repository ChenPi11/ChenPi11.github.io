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

var _VERBOSE = false

// Set verbose mode.
func SetVerbose(verbose bool) {
	_VERBOSE = verbose
}

// Get verbose mode.
func GetVerbose() bool {
	return _VERBOSE
}
