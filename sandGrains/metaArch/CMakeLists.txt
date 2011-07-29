################################################################################
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.8)

project(metaArch)

include(FindBoost)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

if(Boost_FOUND)
  set(INCLUDES ${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR "Boost not Found !")
endif()

set(INCLUDES ${PROJECT_SOURCE_DIR}/include/ ${INCLUDES})

include_directories(${INCLUDES})

file( GLOB_RECURSE source_files
      ${PROJECT_SOURCE_DIR}/src/*
    )

add_executable(metaArch EXCLUDE_FROM_ALL ${source_files} )

set_property(TARGET metaArch PROPERTY 
             RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
            )

set_property(TARGET metaArch PROPERTY 
             OUTPUT_NAME "metaArch.run" 
             )