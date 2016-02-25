cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(travex)


# Add to path in order to pick up the FindXXX.cmake files included in this project
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# This project depends on Boost
find_package(Boost 1.54.0 REQUIRED COMPONENTS program_options regex filesystem)

# This project depends on ROOT
find_package(ROOT)

# Since this projects heavily depend on ROOT check the ROOT's '-m' compilation flag
# and use the same
if(ROOT_FOUND)
	string(REGEX MATCH "(^|[\t ]+)-m([\t ]*)(32|64)([\t ]+|$)" TRAVEX_ROOT_CXX_FLAGS_M ${ROOT_CXX_FLAGS})

	if (TRAVEX_ROOT_CXX_FLAGS_M)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m${CMAKE_MATCH_3}")
		message(STATUS "Found -m${CMAKE_MATCH_3} option in $ROOT_CXX_FLAGS (root-config). Will add it to $CMAKE_CXX_FLAGS")
	endif()
else()
	message(FATAL_ERROR "Fatal error: ROOT package not found")
endif()

add_definitions(-D__ROOT__)


# Check whether the compiler supports c++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


include_directories (
	${Boost_INCLUDE_DIR}
	${ROOT_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/travex/config.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/include/travex/config.h)


root_generate_dictionary(travex_dict
	travex/Hit.h
	travex/Event.h
	travex/Track.h
	travex/TrackNode.h
	LINKDEF travex/LinkDef.h
)

add_library (
	travex
	SHARED
	src/Hit.cxx
	src/TrackNode.cxx
	src/Track.cxx
	src/Event.cxx
	src/ProgramOptions.cxx
	src/HistContainer.cxx
	src/RootFile.cxx
	travex_dict.cxx
)

link_directories(${ROOT_LIBRARY_DIR})

add_executable(test-lib tests/test-lib.cxx)

target_link_libraries(test-lib travex ${Boost_LIBRARIES} ${ROOT_LIBRARIES} HistPainter pthread)


# Installation section
set(ADDITIONAL_INSTALL_PREFIX ".")

# This hack is here just for the STAR users
if(DEFINED ENV{STAR_HOST_SYS})
   set(ADDITIONAL_INSTALL_PREFIX ".$ENV{STAR_HOST_SYS}")
endif()

install(DIRECTORY "include/travex" DESTINATION "${ADDITIONAL_INSTALL_PREFIX}/include")
install(TARGETS travex DESTINATION "${ADDITIONAL_INSTALL_PREFIX}/lib")
install(TARGETS test-lib DESTINATION "${ADDITIONAL_INSTALL_PREFIX}/bin")
