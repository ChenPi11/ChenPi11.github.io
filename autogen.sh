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

# Generate configure script.

# shellcheck disable=SC2059
# shellcheck disable=SC2086

# shellcheck source=scripts/gettext.sh
. ./scripts/gettext.sh || exit 1

VERBOSE=

case "$1" in
    -h|--help)
        printf "$(_g "Usage: %s [-h|--help] [-V|--version] [-v|--verbose]")" "$0"
        printf "$(_g ".\n")"
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
        VERBOSE=--verbose
        shift
        ;;
    *)
        ;;
esac

GNULIB_MODULES="gettext gettext-h"
SRCBASE=srclib
DOCBASE=srcdoc
M4BASE=srcm4
AUXDIR=build-aux
GNULIB_TOOL_FLAGS="--no-libtool --macro-prefix=gl"
AUTOTOOLS_INCLUDES="-I m4 -Isrcm4"
AUTOTOOLS_WARNINGS="--warnings=all"


gnulib-tool --import $GNULIB_MODULES \
  --source-base="$SRCBASE" --m4-base="$M4BASE" --doc-base="$DOCBASE" --aux-dir="$AUXDIR" \
  $GNULIB_TOOL_FLAGS $VERBOSE || die

aclocal --output=aclocal.m4 $AUTOTOOLS_INCLUDES $AUTOTOOLS_WARNINGS $VERBOSE || die
autoheader $AUTOTOOLS_INCLUDES $AUTOTOOLS_WARNINGS $VERBOSE || die
autoconf $AUTOTOOLS_INCLUDES $AUTOTOOLS_WARNINGS $VERBOSE || die
automake --add-missing --copy $AUTOTOOLS_WARNINGS $VERBOSE || die

printf "$(_g "%s: done. Now you can run './configure'.\n")" "$0"
exit 0
