# Install script for directory: F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.0.0-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.0" TYPE FILE FILES
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/assimp-config.cmake"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/assimp-config-version.cmake"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/assimpTargets.cmake"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/assimpTargets-debug.cmake"
    "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/assimpTargets-release.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.0.0-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/assimp.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/contrib/zlib/cmake_install.cmake")
  include("F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/contrib/cmake_install.cmake")
  include("F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/code/cmake_install.cmake")
  include("F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/tools/assimp_cmd/cmake_install.cmake")
  include("F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/test/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "F:/Uni Modules/Programming/301CR/301CREngine/PrettyEngine/vendor/Assimp/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
