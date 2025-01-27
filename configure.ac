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
AC_INIT([chenpi11-blog], [0.1.0] [https://github.com/ChenPi11/ChenPi11.github.io/issues])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_PREFIX_DEFAULT([$(pwd)/.venv])

dnl Constants.
TITLE="ChenPi11's Blog"
AC_SUBST([TITLE])

SIDEBAR=$(cat sidebar.html)
AC_SUBST([SIDEBAR])

CURRENT_YEAR=$(date +%Y)
COPYRIGHT="Copyright &copy; $CURRENT_YEAR ChenPi11, All Rights Reserved."
AC_SUBST([COPYRIGHT])

dnl Checks for basic programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
CB_PROG_CARGO
CB_PROG_CMAKE
CB_PROG_NPM
CB_PROG_PYTHON3

dnl Checks for header files.
AC_CHECK_HEADERS([malloc.h unistd.h])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

dnl Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strchr strrchr strstr])

dnl Configure C++ part with CMake.
AC_ARG_ENABLE([build-type],
  [AS_HELP_STRING([--build-type],
                  [enable build type: debug, release])],
  [AC_DEFINE([BUILD_TYPE], Release,
             [enable build type: debug, release])
   BUILD_TYPE=Release],
  [BUILD_TYPE=Debug])
AC_SUBST([BUILD_TYPE])

AC_MSG_NOTICE([configuring C++ part ...])
AS_IF([$CMAKE -S . -B build $CMAKEFLAGS],
      [],
      [AC_MSG_FAILURE([CMake configure failed])])

dnl Output.
AC_CONFIG_FILES([posts/post-template.html.in])
AC_CONFIG_FILES([index.html.in])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/Makefile])
AC_OUTPUT
