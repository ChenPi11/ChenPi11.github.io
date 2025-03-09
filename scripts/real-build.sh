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

# Build chenpi11-blog.

# shellcheck disable=SC2059

# shellcheck source=gettext.sh
. ./scripts/gettext.sh || exit 1

V=0
VERBOSE=

case "$1" in
    -h|--help)
        printf "$(_g "Usage: %s [-h|--help] [-V|--version] [-v|--verbose]")" "$0"
        printf "$(_g "Build chenpi11-blog.\n")"
        printf "\n"
        printf "$(_g "Options:\n")"
        printf "$(_g "  -h, --help      Display this help and exit.\n")"
        printf "$(_g "  -V, --version   Output version information and exit.\n")"
        printf "$(_g "  -v, --verbose   Verbosely report processing.\n")"
        exit 0
        ;;
    -V|--version)
        show_version
        exit 0
        ;;
    -v|--verbose)
        V=1
        VERBOSE=--verbose
        ;;
esac

USER=user HOSTNAME=BuildRunner neofetch || die

./autogen.sh $VERBOSE || die
./configure CFLAGS="-Wall -Wextra $CFLAGS" CPPFLAGS="-Wall -Wextra $CPPFLAGS" || die
if [ "$V" -ne 0 ]; then
    echo "========== config.log =========="
    cat config.log || die
    echo "========== config.log =========="
fi
make all || die
