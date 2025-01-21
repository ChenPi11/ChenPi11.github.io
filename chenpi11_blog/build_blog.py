#!/usr/bin/env python3

# -*- mode: python -*-
# vi: set ft=python :
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

"""Build all posts."""

import shutil
import sys
from pathlib import Path
from subprocess import Popen

POSTS_TEMPLATE = "posts/post-template.html.in"


def build_blog_main() -> None:
    """Build all posts."""
    if not Path("src").exists():
        msg = "Please run this script in the root directory of the project."
        raise SystemExit(msg)

    if not Path(POSTS_TEMPLATE).exists():
        msg = "posts/post-template.html.in is not found."
        raise SystemExit(msg)

    build_post = shutil.which("build-post")
    if not build_post:
        # Not found if we are running outside of the venv.
        build_post = (Path.cwd() / ".venv/bin/build-post").as_posix()

    if not Path(build_post).exists():
        msg = "build-post is not found."
        raise SystemExit(msg)

    for postfile in Path("orig-posts").iterdir():
        if postfile.suffix != ".md":
            continue
        sys.stdout.write(f"========== Building {postfile}... ==========\n")
        cmd = f"{build_post} {POSTS_TEMPLATE} {postfile.as_posix()}"
        sys.stdout.write(f"Executing {cmd} ...\n")
        with Popen(  # noqa: S602
            cmd,
            shell=True,
        ) as proc:
            if proc.wait() != 0:
                msg = f"Failed to build {postfile}."
                raise SystemExit(msg)


if __name__ == "__main__":
    build_blog_main()
