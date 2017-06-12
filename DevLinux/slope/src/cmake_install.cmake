# Install script for directory: /media/DATA/projects/spl/SmartStreetLight/slope/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/libslope.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/lib" TYPE SHARED_LIBRARY FILES "/media/DATA/projects/spl/SmartStreetLight/slope/src/libslope.so")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/include/slope/drawing.h;/usr/include/slope/figure.h;/usr/include/slope/global.h;/usr/include/slope/item.h;/usr/include/slope/scale.h;/usr/include/slope/slope.h;/usr/include/slope/view.h;/usr/include/slope/xyscale.h;/usr/include/slope/xyseries.h;/usr/include/slope/xyaxis.h;/usr/include/slope/xyaxis-sampler.h;/usr/include/slope/sampler.h;/usr/include/slope/view.h;/usr/include/slope/chart.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/include/slope" TYPE FILE FILES
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/drawing.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/figure.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/global.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/item.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/scale.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/slope.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/view.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/xyscale.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/xyseries.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/xyaxis.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/xyaxis-sampler.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/sampler.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/view.h"
    "/media/DATA/projects/spl/SmartStreetLight/slope/src/slope/chart.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/include/slope/config.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/include/slope" TYPE FILE FILES "/media/DATA/projects/spl/SmartStreetLight/slope/config.h")
endif()

