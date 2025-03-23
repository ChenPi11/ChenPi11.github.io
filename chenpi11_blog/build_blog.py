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

from chenpi11_blog.i18n import _
from chenpi11_blog.is_blog import is_chenpi11_blog_rootdir

POSTS_TEMPLATE = "posts/post-template.html.in"


def _parse_arg() -> bool:
    if "-h" in sys.argv or "--help" in sys.argv:
        sys.stdout.write(
            _("Usage: build-blog [-h|--help] [-V|--version] [-v|--verbose]\n"),
        )
        sys.stdout.write("\n")
        sys.stdout.write(_("Options:\n"))
        sys.stdout.write(_("  -h, --help     Display this help and exit.\n"))
        sys.stdout.write(_("  -V, --version  Output version information and exit.\n"))
        sys.stdout.write(_("  -v, --verbose  Verbosely report processing.\n"))
        sys.exit(0)
    elif "-V" in sys.argv or "--version" in sys.argv:
        sys.stdout.write("chenpi11-blog 0.1.0\n")
        sys.stdout.write(_("Copyright (C) 2025 ChenPi11\n"))
        sys.stdout.write(
            _(
                "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n",
            ),
        )
        sys.stdout.write(
            _("This is free software: you are free to change and redistribute it.\n"),
        )
        sys.stdout.write(_("There is NO WARRANTY, to the extent permitted by law.\n"))
        sys.stdout.write(_("Written by ChenPi11.\n"))
        sys.exit(0)
    elif "-v" in sys.argv or "--verbose" in sys.argv:
        return True

    return False


def build_blog_main() -> None:
    """Build all posts."""
    verbose = _parse_arg()

    if not is_chenpi11_blog_rootdir():
        msg = _("You must run {prog} in project's root directory!\n").format(
            prog="build-blog",
        )
        raise SystemExit(msg)

    if not Path(POSTS_TEMPLATE).exists():
        msg = _("posts/post-template.html.in is not found.")
        raise SystemExit(msg)

    build_post = shutil.which("build-post")
    if not build_post:
        # Not found if we are running outside of the venv.
        build_post = (Path.cwd() / ".venv" / "bin" / "build-post").as_posix()

    if not Path(build_post).exists():
        msg = _("build-post is not found.")
        raise SystemExit(msg)

    for postfile in Path("orig-posts").iterdir():
        if postfile.suffix != ".md":
            continue
        sys.stdout.write(
            _("========== Building {postfile} ... ==========\n").format(
                postfile=postfile,
            ),
        )
        verbose_flag = "--verbose" if verbose else ""
        cmd = f"{build_post} {POSTS_TEMPLATE} {postfile.as_posix()} {verbose_flag}"
        if verbose:
            sys.stdout.write(_("Executing {cmd} ...\n").format(cmd=cmd))
        with Popen(  # noqa: S602
            cmd,
            shell=True,
        ) as proc:
            if proc.wait() != 0:
                msg = _("Failed to build {postfile}.").format(postfile=postfile)
                raise SystemExit(msg)

    # Copy applets.
    sys.stdout.write(_("========== Copying resources ... ==========\n"))
    if Path("posts/res").exists():
        shutil.rmtree("posts/res")
    shutil.copytree("orig-posts/res", "posts/res")


if __name__ == "__main__":
    build_blog_main()
