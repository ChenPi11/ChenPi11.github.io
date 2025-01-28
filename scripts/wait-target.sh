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

# Wait for a file or directory to exist.

TARGET=$1
TIMEOUT=60

echo "Waiting for $TARGET ..."

TIME=0
while [ ! -e "$TARGET" ]; do
    sleep 2
    TIME=$((TIME + 2))
    if [ $TIME -gt $TIMEOUT ]; then
        echo "Timeout waiting for $TARGET."
        exit 1
    fi
done
