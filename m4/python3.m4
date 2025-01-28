dnl python3.m4: Checking for Python3.
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

AC_DEFUN([CB_PROG_PYTHON3],
[
AC_ARG_VAR([PYTHON3], [Path to Python3 executable])
AC_ARG_VAR([PYTHON3FLAGS], [Python3 interpreter flags])
AC_ARG_VAR([PIPFLAGS], [Pip flags])

AS_IF([test x$PYTHON3 = x],
      [AC_PATH_PROGS([PYTHON3], [python3 python])])

AC_MSG_CHECKING([Python is Python3])
AS_IF([test x$PYTHON3 = x],
      [AC_MSG_RESULT([no])]
      [AC_MSG_FAILURE([No python3 executable found])])

AS_IF([$PYTHON3 --version 2>&1 | grep -q "^Python 3"],
      [AC_MSG_RESULT([yes])],
      [AC_MSG_RESULT([no])]
      [AC_MSG_FAILURE([Python executable is not Python3])])

AC_MSG_CHECKING([Python3 has pip])
AS_IF([$PYTHON3 -m pip --version > /dev/null 2>&1],
      [AC_MSG_RESULT([yes])],
      [AC_MSG_RESULT([no])]
      [AC_MSG_FAILURE([Python3 don't have Pip])])

AC_MSG_CHECKING([Python3 has venv])
AS_IF([$PYTHON3 -m venv -h > /dev/null 2>&1],
      [AC_MSG_RESULT([yes])],
      [AC_MSG_RESULT([no])]
      [AC_MSG_FAILURE([Python3 don't have venv])])

AC_SUBST([PYTHON3])
AC_SUBST([PYTHON3FLAGS])
AC_SUBST([PIPFLAGS])
]
)
