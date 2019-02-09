cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS "../components")

set(TEST_COMPONENTS "loopp" CACHE STRING "List of components to test")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(loopp_test)
