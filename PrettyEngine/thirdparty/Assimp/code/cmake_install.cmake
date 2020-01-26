# Install script for directory: F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/Assimp")
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
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/lib/Debug/assimp-vc141-mtd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/lib/Release/assimp-vc141-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/lib/MinSizeRel/assimp-vc141-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/lib/RelWithDebInfo/assimp-vc141-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/anim.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/aabb.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/ai_assert.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/camera.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/color4.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/color4.inl"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/config.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/defs.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Defines.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/cfileio.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/light.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/material.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/material.inl"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/matrix3x3.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/matrix3x3.inl"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/matrix4x4.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/matrix4x4.inl"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/mesh.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/pbrmaterial.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/postprocess.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/quaternion.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/quaternion.inl"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/scene.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/metadata.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/texture.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/types.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/vector2.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/vector2.inl"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/vector3.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/vector3.inl"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/version.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/cimport.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/importerdesc.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Importer.hpp"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/DefaultLogger.hpp"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/ProgressHandler.hpp"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/IOStream.hpp"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/IOSystem.hpp"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Logger.hpp"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/LogStream.hpp"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/NullLogger.hpp"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/cexport.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Exporter.hpp"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/DefaultIOStream.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/DefaultIOSystem.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/SceneCombiner.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/fast_atof.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/qnan.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/BaseImporter.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Hash.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/MemoryIOWrapper.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/ParsingUtils.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/StreamReader.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/StreamWriter.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/StringComparison.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/StringUtils.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/SGSpatialSort.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/GenericProperty.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/SpatialSort.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/SmoothingGroups.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/SmoothingGroups.inl"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/StandardShapes.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/RemoveComments.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Subdivision.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Vertex.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/LineSplitter.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/TinyFormatter.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Profiler.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/LogAux.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Bitmap.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/XMLTools.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/IOStreamBuffer.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/CreateAnimMesh.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/irrXMLWrapper.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/BlobIOSystem.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/MathFunctions.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Exceptional.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Compiler/pushpack1.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Compiler/poppack1.h"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/Debug/assimp-vc141-mtd.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/RelWithDebInfo/assimp-vc141-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

