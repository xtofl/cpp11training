cmake_minimum_required(VERSION 3.11.0)

include(FetchContent)

function(fetch_google_test)
	FetchContent_Declare(
	  googletest
	  GIT_REPOSITORY https://github.com/google/googletest.git
	  GIT_TAG        release-1.8.0
	)
	FetchContent_MakeAvailable(googletest)
	FetchContent_GetProperties(googletest)
	if(NOT googletest_POPULATED)
	  message(Fetching googletest)
	  FetchContent_Populate(googletest)
	  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
	endif()
endfunction()

