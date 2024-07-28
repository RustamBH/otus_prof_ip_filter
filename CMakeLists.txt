cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

add_executable(
	ip_filter
	ip_filter.cpp
)

set_target_properties(ip_filter PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
