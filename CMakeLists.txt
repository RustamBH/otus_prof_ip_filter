cmake_minimum_required(VERSION 3.5)

project(02.homework)

add_executable(
	IP_filter
	ip_filter.cpp
)

set_target_properties(IP_filter PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)