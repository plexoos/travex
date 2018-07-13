cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(travex)


# Add to path in order to pick up the FindXXX.cmake files included in this project
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# This project depends on ROOT
find_package(ROOT COMPONENTS HistPainter)

if( ${ROOT_CXX_FLAGS} MATCHES "-m32" )
	message(STATUS "Found -m32 option in $ROOT_CXX_FLAGS (root-config). Will add it to $CMAKE_CXX_FLAGS")
	set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS FALSE)
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32" )
	set(ENV{PKG_CONFIG_PATH} "/usr/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
endif()

# This project depends on Boost
find_package(Boost 1.54.0 COMPONENTS program_options regex filesystem)

add_definitions(-D__ROOT__)

set(CMAKE_CXX_STANDARD 11)

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

target_link_libraries(travex ${Boost_LIBRARIES} ${ROOT_LIBRARIES} pthread)

add_executable(test-lib tests/test-lib.cxx)

target_link_libraries(test-lib travex)


install(DIRECTORY "include/travex" DESTINATION "include")

install( TARGETS
	test-lib travex
	RUNTIME DESTINATION "bin"
	LIBRARY DESTINATION "lib"
)
