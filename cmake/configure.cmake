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

macro ( check_def NAME )
    if ( NOT DEFINED ${NAME} )
        message ( FATAL_ERROR "${NAME} not defined" )
    endif ()
endmacro ()

macro ( resolve_file VAL )
    if ( ${VAL} MATCHES "^FILE=(.*)$" )
        file ( READ "${CMAKE_MATCH_1}" FILE_CONTENT )
        set ( ${VAL} "${FILE_CONTENT}" )
        unset ( FILE_CONTENT )
    endif ()
endmacro ()

check_def ( FROM )
check_def ( TO )

check_def ( K0 )
check_def ( V0 )
resolve_file ( V0 )
set ( ${K0} ${V0} )

if ( DEFINED K1 )
    check_def ( V1 )
    resolve_file ( V1 )
    set ( ${K1} ${V1} )
endif ()

message ( STATUS "Configuring ${TO} ..." )
configure_file ( ${FROM} ${TO} @ONLY )
