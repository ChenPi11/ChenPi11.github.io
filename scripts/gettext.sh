#!/bin/sh

# Copyright (C) 2025 ChenPi11.
# This file is part of chenpi11-blog.
#
# chenpi11-blog is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# chenpi11-blog is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with chenpi11-blog.  If not, see <https://www.gnu.org/licenses/>.

# Load gettext if available.

# shellcheck disable=SC2059

if command -v gettext >/dev/null 2>&1; then
    export TEXTDOMAIN=chenpi11-blog
    if [ -f ".venv/share/locale/zh_CN/LC_MESSAGES/$TEXTDOMAIN.mo" ]; then
        export TEXTDOMAINDIR=".venv/share/locale"
    elif [ -f "/usr/local/share/locale/zh_CN/LC_MESSAGES/$TEXTDOMAIN.mo" ]; then
        export TEXTDOMAINDIR="/usr/local/share/locale"
    else
        export TEXTDOMAINDIR="/usr/share/locale"
    fi

    _g() {
        gettext "$@"
    }
else
    _g() {
        echo "$1"
    }
fi

die() {
    _g "Error."
    exit 1
}

show_version() {
    printf "$0 0.1.0\n"
    printf "$(_g "Copyright (C) 2025 ChenPi11.\n")"
    printf "$(_g "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n")"
    printf "$(_g "This is free software: you are free to change and redistribute it.\n")"
    printf "$(_g "There is NO WARRANTY, to the extent permitted by law.\n")"
    printf "$(_g "Written by ChenPi11.\n")"
}
