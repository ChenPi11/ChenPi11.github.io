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

if [ -z "$PYTHON" ]; then
  PYTHON=python3
fi

if [ -z "$NPM" ]; then
  NPM=npm
fi

die()
{
    echo "$0: Error."
    rm -rf .venv
    exit 1
}

# Install requirements.
python -m venv .venv || die
# shellcheck source=/dev/null
. ./.venv/bin/activate || die
# shellcheck disable=SC2086
python3 -m pip install -r requirements.txt --verbose $PIPFLAGS || die

# Install NPM requirements.
# shellcheck disable=SC2086
$NPM install --verbose $NPMFLAGS || die

# Export xterm.js
cp -r node_modules/@xterm/xterm . || die
cp -r node_modules/@xterm/addon-fit/lib/*.js xterm/lib || die
cd xterm || die
rm -rf src typings package.json README.md lib/*.map
