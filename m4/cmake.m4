dnl cmake.m4: Checking for CMake.
dnl
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

AC_DEFUN([CB_PROG_CMAKE],
[
AC_ARG_VAR([CMAKE], [Path to CMake executable])
AC_ARG_VAR([CMAKEVERBOSE], [CMake verbose flags])
AC_ARG_VAR([CMAKEFLAGS], [CMake flags])

AS_IF([test x$CMAKE = x],
      [AC_PATH_PROGS([CMAKE], [cmake])])

AC_MSG_CHECKING([CMake is working properly])

AS_IF([$CMAKE $CMAKEVERBOSE $CMAKEFLAGS --version > /dev/null 2>&1],
      [AC_MSG_RESULT([yes])],
      [AC_MSG_RESULT([no])]
      [AC_MSG_FAILURE([CMake cannot working properly])])

AC_SUBST([CMAKE])
AC_SUBST([CMAKEVERBOSE])
AC_SUBST([CMAKEFLAGS])
]
)
