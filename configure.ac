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
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE
AC_PREFIX_DEFAULT([$(pwd)/.venv])

dnl Constants.
TITLE="ChenPi11's Blog"
AC_SUBST([TITLE])

SIDEBAR=$(cat sidebar.html)
AC_SUBST([SIDEBAR])

CURRENT_YEAR=$(date +%Y)
COPYRIGHT="Copyright &copy; $CURRENT_YEAR ChenPi11, All Rights Reserved."
AC_SUBST([COPYRIGHT])

AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug],
                  [enable debug build])],
  [AC_DEFINE([BUILD_TYPE], debug,
             [enable debug build])
   BUILD_TYPE=DEBUG],
  [BUILD_TYPE=RELEASE])
AC_SUBST([BUILD_TYPE])

dnl Configure automake.
AC_CONFIG_MACRO_DIRS([srcm4])

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
CB_PROG_CARGO
CB_PROG_CMAKE
CB_PROG_NPM
CB_PROG_PYTHON3
CL_PROG_CP
gl_EARLY
gl_INIT

dnl Checks for compiler output filename suffixes.

AC_OBJEXT
AC_EXEEXT

dnl Flags.
AC_ARG_VAR([PYTHON_BUILDVERBOSE], [python -m build's verbose flag])
AC_SUBST([PYTHON_BUILDVERBOSE])

AC_ARG_VAR([PYTHON_BUILDFLAGS], [python -m build's flags])
AC_SUBST([PYTHON_BUILDFLAGS])

AC_ARG_VAR([CCVERBOSE], [C compiler verbose flag])
AC_SUBST([CCVERBOSE])

AC_ARG_VAR([CXXVERBOSE], [C++ compiler verbose flag])
AC_SUBST([CXXVERBOSE])

AC_ARG_VAR([LDVERBOSE], [linker verbose flag])
AC_SUBST([LDVERBOSE])

AC_ARG_VAR([CMAKE_MAKEVERBOSE], [cmake --build verbose flag])
AC_SUBST([CMAKE_MAKEVERBOSE])

AC_ARG_VAR([CB_UTILSVERBOSE], [ChenPi11's Blog utils verbose flag])
AC_SUBST([CB_UTILSVERBOSE])

dnl Verbose settings.
AC_ARG_WITH([verbose],
            AS_HELP_STRING([--with-verbose], [verbose level]),
            [VERBOSE_LEVEL=$withval],
            [VERBOSE_LEVEL=1]
)
AC_SUBST([VERBOSE_LEVEL])

AC_MSG_CHECKING([verbose level])
AS_IF([test x"$VERBOSE_LEVEL" = x],
      [AC_MSG_RESULT([ok $VERBOSE_LEVEL])],
      [VERBOSE_LEVEL=1])

if test "$VERBOSE_LEVEL" -ge 1; then
  CARGOVERBOSE=--verbose
  PIPVERBOSE=--verbose
  PYTHON_BUILDVERBOSE=--verbose
  NPMVERBOSE=--verbose
  CB_UTILSVERBOSE=--verbose
elif test "$VERBOSE_LEVEL" -ge 2; then
  CARGOVERBOSE=--verbose
  PIPVERBOSE=--verbose
  PYTHON_BUILDVERBOSE=--verbose
  NPMVERBOSE=--verbose
  CMAKE_MAKEVERBOSE="VERBOSE=1"
  CB_UTILSVERBOSE=--verbose
elif test "$VERBOSE_LEVEL" -ge 3; then
  CARGOVERBOSE=-vv
  PIPVERBOSE="--verbose --verbose"
  PYTHON_BUILDVERBOSE="--verbose --verbose"
  NPMVERBOSE=--verbose
  CMAKE_MAKEVERBOSE="VERBOSE=1"
  CB_UTILSVERBOSE=--verbose
elif test "$VERBOSE_LEVEL" -ge 4; then
  CARGOVERBOSE=-vv
  CMAKEVERBOSE=--trace
  PYTHON3VERBOSE=-v
  PIPVERBOSE="--verbose --verbose --verbose"
  PYTHON_BUILDVERBOSE="--verbose --verbose --verbose"
  CCVERBOSE=-v
  CXXVERBOSE=-v
  LDVERBOSE=-v
  NPMVERBOSE=--verbose
  CMAKE_MAKEVERBOSE="VERBOSE=1"
  CB_UTILSVERBOSE=--verbose
else
  CARGOVERBOSE=--verbose
  PIPVERBOSE=--verbose
  PYTHON_BUILDVERBOSE=--verbose
  NPMVERBOSE=--verbose
  CB_UTILSVERBOSE=--verbose
fi

dnl Hack.
dnl Automake don't support variable with line break. So remove thr variables
dnl with line break.
sed -i "s|SIDEBAR = @SIDEBAR@||g" srclib/Makefile.in

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
AC_CHECK_HEADERS([libintl.h])
AC_CHECK_HEADERS([linux/limits.h])
AC_CHECK_FUNCS([setlocale])
AM_GNU_GETTEXT_REQUIRE_VERSION([0.20])
AM_GNU_GETTEXT([external])

dnl Configure C++ part.
AC_CONFIG_SUBDIRS([mkpostlists])

dnl Output.
AC_CONFIG_FILES([bin/Makefile])
AC_CONFIG_FILES([lib/Makefile])
AC_CONFIG_FILES([srclib/Makefile])
AC_CONFIG_FILES([posts/post-template.html.in])
AC_CONFIG_FILES([posts/Makefile])
AC_CONFIG_FILES([index.html.in])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([po/Makefile])
AC_CONFIG_FILES([src/Makefile])
AC_CONFIG_FILES([mkpostlists/configure])
AC_OUTPUT
