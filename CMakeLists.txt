#/*
#-----------------------------------------------------------------------------
# Filename:    common.cmake
#-----------------------------------------------------------------------------
#
# This source file is based on
#   ___                 __    __ _ _    _
#  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
# //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
#/ \_// (_| | | |  __/  \  /\  /| |   <| |
#\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
#      |___/
#      Tutorial Framework
#      http://www.ogre3d.org/tikiwiki/
#
# Modified for CMU students.
#-----------------------------------------------------------------------------
#*/

cmake_minimum_required(VERSION 2.6)

set(APP "SimpleGame")

find_package(Threads)

set(HDRS
	./src/Game.h
)

set(SRCS
	./src/Game.cpp
	./src/main.cpp
)

include("tools/cmake/common.cmake")
