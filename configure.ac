dnl Copyright (C) 2025 ChenPi11.
dnl This file is part of chenpi11-blog.
dnl
dnl chenpi11-blog is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl chenpi11-blog is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with chenpi11-blog.  If not, see <https://www.gnu.org/licenses/>.

AC_PREREQ([2.64])
AC_INIT([chenpi11-blog], [0.1.0])
AC_CONFIG_AUX_DIR([build-aux])
AC_PREFIX_DEFAULT([$(pwd)/.venv])

TITLE="ChenPi11's Blog"
AC_SUBST([TITLE])

SIDEBAR=$(cat sidebar.html)
AC_SUBST([SIDEBAR])

CURRENT_YEAR=$(date +%Y)

COPYRIGHT="Copyright &copy; $CURRENT_YEAR ChenPi11, All Rights Reserved."
AC_SUBST([COPYRIGHT])

AC_PROG_CC
AC_PROG_INSTALL

cb_PYTHON3
cb_NPM
cb_CARGO
cb_CMAKE

AC_SUBST([PYTHON3])
AC_SUBST([NPM])
AC_SUBST([NPX])
AC_SUBST([CARGO])
AC_SUBST([CMAKE])

AC_CONFIG_FILES([posts/post-template.html.in])
AC_CONFIG_FILES([index.html.in])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/Makefile])
AC_OUTPUT
