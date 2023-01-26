cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(bayan VERSION ${PROJECT_VERSION})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

#find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(Boost REQUIRED COMPONENTS filesystem regex)

add_executable(bayan_cli main.cpp SearchParameters.cpp FileList.cpp DuplicateSearch.cpp FileReader.cpp HashCalculator.cpp)

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(bayan_cli ${Boost_LIBRARIES})

set_target_properties(bayan_cli PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

if (MSVC)
    target_compile_options(bayan_cli PRIVATE
            /W4
            )
else ()
    target_compile_options(bayan_cli PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()

install(TARGETS bayan_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
