cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(travex)


# Add to path in order to pick up the FindXXX.cmake files included in this project
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# This project depends on Boost
set(Boost_USE_MULTITHREADED OFF)
find_package(Boost 1.54.0 REQUIRED COMPONENTS program_options regex filesystem)

# This project depends on ROOT
find_package(ROOT)

if (NOT ROOT_FOUND)
   message(FATAL_ERROR "Fatal error: ROOT package not found")
endif()

add_definitions(-D__ROOT__)
# Add common compiler options
add_compile_options(-std=c++0x)


include_directories (
	${Boost_INCLUDE_DIR}
	${ROOT_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_library (
	travex
	SHARED
	src/Hit.cxx
	src/TrackNode.cxx
	src/Track.cxx
	src/Event.cxx
)

add_executable(test-lib tests/test-lib.cxx)

target_link_libraries(test-lib travex ${Boost_LIBRARIES} ${ROOT_LIBRARIES} pthread)


# Installation section
set(ADDITIONAL_INSTALL_PREFIX ".")

# This hack is here just for the STAR users
if(DEFINED ENV{STAR_HOST_SYS})
   set(ADDITIONAL_INSTALL_PREFIX ".$ENV{STAR_HOST_SYS}")
endif()

install(DIRECTORY "include/travex" DESTINATION "${ADDITIONAL_INSTALL_PREFIX}/include")
install(TARGETS travex DESTINATION "${ADDITIONAL_INSTALL_PREFIX}/lib")
install(TARGETS test-lib DESTINATION "${ADDITIONAL_INSTALL_PREFIX}/bin")
