# babyxml - tiny parser for XML-like dialect
# Copyright (C) 2009-2020 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.6)
project(babyxml VERSION 0.0.0)

set(TINYCMMC_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/tinycmmc/modules/")
find_package(tinycmmc CONFIG)
message(STATUS "tinycmmc module path: ${TINYCMMC_MODULE_PATH}")
list(APPEND CMAKE_MODULE_PATH ${TINYCMMC_MODULE_PATH})

include(MaximumWarnings)

add_library(babyxml STATIC
  src/babyxml.cpp
  src/reader.cpp)
target_include_directories(babyxml PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_options(babyxml PRIVATE ${WARNINGS_CXX_FLAGS})
set_target_properties(babyxml PROPERTIES
  PUBLIC_HEADER "include/babyxml.hpp")
set_target_properties(babyxml PROPERTIES
  CXX_STANDARD 20
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON)

if(BUILD_TESTS)
  add_executable(babyxml_test test/babyxml_test.cpp)
  target_link_libraries(babyxml_test PRIVATE babyxml)
  target_compile_options(babyxml_test PRIVATE ${WARNINGS_CXX_FLAGS})
  set_target_properties(babyxml_test PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON)
endif()

include(ExportAndInstallLibrary)

# EOF #
