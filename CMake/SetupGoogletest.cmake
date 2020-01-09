set(_PATH_OF_CMAKE_INCLUDES "${CMAKE_CURRENT_LIST_DIR}")

function (setup_googletest)
	# Source of this function's implementation and its dependencies is https://github.com/Crascit/DownloadProject

	if (CMAKE_VERSION VERSION_LESS 3.2)
		set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
	else()
		set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
	endif()

	include("${_PATH_OF_CMAKE_INCLUDES}/DownloadProject.cmake")
	download_project(PROJ                googletest
	                 GIT_REPOSITORY      https://github.com/google/googletest.git
	                 GIT_TAG             master
	                 PREFIX              "${_PATH_OF_CMAKE_INCLUDES}/../third_party"
	                 ${UPDATE_DISCONNECTED_IF_AVAILABLE})

	# Prevent GoogleTest from overriding our compiler/linker options
	# when building with Visual Studio
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	add_subdirectory("${googletest_SOURCE_DIR}"
	                 "${googletest_BINARY_DIR}")

	# When using CMake 2.8.11 or later, header path dependencies
	# are automatically added to the gtest and gmock targets.
	# For earlier CMake versions, we have to explicitly add the
	# required directories to the header search path ourselves.
	if (CMAKE_VERSION VERSION_LESS 2.8.11)
		include_directories("${gtest_SOURCE_DIR}/include"
		                    "${gmock_SOURCE_DIR}/include")
	endif()

endfunction()

function (setup_cpp_project_with_googletest SOURCE_DIR_PREFIX)

	if (NOT _SETUP_GOOGLETEST_DONE)
		# Only setup once
		setup_googletest()
		set(_SETUP_GOOGLETEST_DONE "1" CACHE INTERNAL "_SETUP_GOOGLETEST_DONE")
	endif()

	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	# Unique target names for exercises and solutions
	get_directory_property(PARENT_DIRECTORY_PATH PARENT_DIRECTORY)
	get_filename_component(PARENT_DIRECTORY_NAME "${PARENT_DIRECTORY_PATH}" NAME)
	set(TARGET_NAME ${PARENT_DIRECTORY_NAME}-${PROJECT_NAME})

	include_directories("${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR_PREFIX}")
	file (GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR_PREFIX}*/*.cpp")
	add_executable(${TARGET_NAME} ${SOURCES})
	set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
	target_link_libraries(${TARGET_NAME} gtest gmock_main)

endfunction()
