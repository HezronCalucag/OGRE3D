# Install script for directory: D:/OGREBullet/o3d_1-12_bull_3_base

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/OGREBullet/o3d_1-12_bull_3_base/build/dist")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./" TYPE DIRECTORY FILES "D:/OGREBullet/o3d_1-12_bull_3_base/dist/media")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "D:/OGREBullet/o3d_1-12_bull_3_base/dist/bin/resources.cfg")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE RENAME "resources.cfg" FILES "D:/OGREBullet/o3d_1-12_bull_3_base/dist/bin/resources_d.cfg")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES
      "D:/OGREBullet/ogre/build/sdk/bin/Codec_Assimp.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/Codec_STBI.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/DefaultSamples.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/OgreBites.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/OgreMain.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/OgreMeshLodGenerator.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/OgreOverlay.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/OgrePaging.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/OgreProperty.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/OgreRTShaderSystem.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/OgreTerrain.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/OgreVolume.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/Plugin_BSPSceneManager.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/Plugin_DotScene.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/Plugin_OctreeSceneManager.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/Plugin_OctreeZone.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/Plugin_PCZSceneManager.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/Plugin_ParticleFX.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/RenderSystem_Direct3D11.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/RenderSystem_GL.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/RenderSystem_GL3Plus.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/SDL2.dll"
      "D:/OGREBullet/ogre/build/sdk/bin/zlib.dll"
      )
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Dd][Ee][Bb][Uu][Gg])$")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/OGREBullet/o3d_1-12_bull_3_base/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
