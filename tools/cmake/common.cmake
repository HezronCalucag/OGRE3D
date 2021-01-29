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

project(${APP})


if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")

#set(OGRE_DEPENDENCIES_DIR /home/gljenkins/Documents/Development/ogre1_12/ogre/build/Dependencies)

#find_package(OGRE 1.12 REQUIRED)

find_package(OGRE 1.12 REQUIRED COMPONENTS Bites RTShaderSystem)

#DEBUGGING -
message(STATUS "Current OGRE_CONFIG_DIR")
message(STATUS ${OGRE_CONFIG_DIR})

message(STATUS "Current OGRE_MEDIA DIR")
message(STATUS ${OGRE_MEDIA_DIR})

message(STATUS "Current CMAKE_BINARY_DIR")
message(STATUS ${CMAKE_BINARY_DIR})

# Removed in 1.11
# message(STATUS "Current  OGRE_PLUGIN_DIR_DB")
# message(STATUS  ${OGRE_PLUGIN_DIR_DBG})

# message(STATUS "Current  OGRE_PLUGIN_DIR_REL")
# message(STATUS  ${OGRE_PLUGIN_DIR_REL})

#include_directories( ${OIS_INCLUDE_DIRS}
#	${OGRE_INCLUDE_DIRS}
#	${OGRE_SAMPLES_INCLUDEPATH}
#	${OGRE_Overlay_INCLUDE_DIRS}
#)

# For later Bullet3 tutorials
find_package(Bullet REQUIRED)

# Debugging
# message("BULLET_INCLUDE_DIRS:")
# message(${BULLET_INCLUDE_DIRS})

# message("BULLET_LIBRARIES:")
# message(${BULLET_LIBRARIES})

# message(STATUS "OGRE_DEPENDENCIES_DIR:")
# message(STATUS ${OGRE_DEPENDENCIES_DIR})

# message(STATUS "OGRE_DEP_DIR:")
# message(STATUS ${OGRE_DEP_DIR})

include_directories(${BULLET_INCLUDE_DIRS})

add_executable(${APP} WIN32 ${HDRS} ${SRCS})

set_target_properties(${APP} PROPERTIES DEBUG_POSTFIX _d)

target_link_libraries(${APP} OgreBites OgreRTShaderSystem)
target_link_libraries(${APP} ${OGRE_LIBRARIES} ${OGRE_Overlay_LIBRARIES} ${BULLET_LIBRARIES})

# Don't need these, Bullet3 is static!
#link_directories(${BULLET_LIBRARIES})
#target_link_libraries(${APP} BulletDynamics BulletCollision LinearMath)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)

# post-build copy for win32
if(WIN32 AND NOT MINGW)
	add_custom_command( TARGET ${APP} PRE_BUILD
		COMMAND if not exist .\\dist\\bin mkdir .\\dist\\bin )
	add_custom_command( TARGET ${APP} POST_BUILD
		COMMAND copy \"$(TargetPath)\" .\\dist\\bin )
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
endif(MINGW OR UNIX)

if(WIN32)
   set_target_properties(${APP} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
   set_target_properties(${APP} PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
   set_target_properties(${APP} PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
   set_target_properties(${APP} PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
   set_target_properties(${APP} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
   set_target_properties(${APP} PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
endif(WIN32)


if(WIN32)
	install(TARGETS ${APP}
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)

	# https://stackoverflow.com/questions/23950887/does-cmake-offer-a-method-to-set-the-working-directory-for-a-given-build-system
	set_target_properties(${APP} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dist/bin")

	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)

	install(FILES
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)

	install(FILES
		${CMAKE_SOURCE_DIR}/dist/bin/resources_d.cfg
		DESTINATION bin
		CONFIGURATIONS Debug
		RENAME resources.cfg
	)

	# Got lazy - going stuff all the dlls in for the release. 
	file(GLOB_RECURSE OG_DLL_FILES  ${OGRE_CONFIG_DIR}/*.dll)
	
	install(FILES ${OG_DLL_FILES}
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
	
        # NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of libOIS.dll
        # so you'll have to change that to make it work with 1.7.1
		# Removed in 1.11 now SDL.
	#install(FILES ${OGRE_CONFIG_DIR}/OgreMain.dll
	#	${OGRE_CONFIG_DIR}/RenderSystem_Direct3D11.dll
	#	${OGRE_CONFIG_DIR}/RenderSystem_GL.dll
#		${OGRE_PLUGIN_DIR_REL}/libOIS.dll
	#	DESTINATION bin
	#	CONFIGURATIONS Release RelWithDebInfo Debug
	#)

	# install(FILES ${OGRE_CONFIG_DIR}/OgreMain_d.dll
	#	${OGRE_CONFIG_DIR}/RenderSystem_Direct3D11_d.dll
	#	${OGRE_CONFIG_DIR}/RenderSystem_GL_d.dll
	#	${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
	#	DESTINATION bin
	#	CONFIGURATIONS Debug
	#)

	# Extra bits for Ogre Examples - GLJ
	#install(FILES ${OGRE_CONFIG_DIR}/OgreBites.dll
	#	${OGRE_CONFIG_DIR}/OgreRTShaderSystem.dll
	#	${OGRE_CONFIG_DIR}/OgreOverlay.dll
	#	DESTINATION bin
	#	CONFIGURATIONS Release RelWithDebInfo Debug
	#)

	# Extra bits for Ogre Examples - GLJ
	# Dec 2019 - Moved to using RelWithDebug 
	# install(FILES ${OGRE_CONFIG_DIR}/OgreBites_d.dll
	#	${OGRE_CONFIG_DIR}/OgreRTShaderSystem_d.dll
	#	${OGRE_CONFIG_DIR}/OgreOverlay_d.dll
	#	DESTINATION bin
	#	CONFIGURATIONS Debug
	#)

	# Extra bits for examples - GLJ
	#install(FILES ${OGRE_CONFIG_DIR}/SDL2.dll
	#	${OGRE_CONFIG_DIR}/zlib.dll
	#	DESTINATION bin
	#	CONFIGURATIONS Release RelWithDebInfo Debug
	#)

   # as of sdk 1.7.2 we need to copy the boost dll's as well
   # because they're not linked statically (it worked with 1.7.1 though)
   #install(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
    #  ${Boost_THREAD_LIBRARY_RELEASE}
    #  DESTINATION bin
    #  CONFIGURATIONS Release RelWithDebInfo
   #)


   install(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
      ${Boost_THREAD_LIBRARY_DEBUG}
      DESTINATION bin
      CONFIGURATIONS Debug
   )
endif(WIN32)

if(UNIX)

	install(TARGETS ${APP}
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)

	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)

  install(FILES
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)

  install(FILES
		${CMAKE_SOURCE_DIR}/dist/bin/resources_d.cfg
		DESTINATION bin
		CONFIGURATIONS Debug
    RENAME resources.cfg
	)

endif(UNIX)
