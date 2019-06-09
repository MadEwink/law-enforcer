cmake_minimum_required(VERSION 3.13)
project(Law_Enforcer)

set(CMAKE_CXX_STANDARD 14)

include_directories("Law Enforcer")
include_directories("Main Law Enforcer")
include_directories(Test)

add_executable(Law_Enforcer
        "Law Enforcer/Law Enforcer.cpp"
        "Main Law Enforcer/Main Law Enforcer.cpp" "Law Enforcer/LevelObject.cpp" "Law Enforcer/LevelObject.h" "Law Enforcer/Platform.cpp" "Law Enforcer/Platform.h" "Law Enforcer/Entity.cpp" "Law Enforcer/Entity.h" "Law Enforcer/Level.cpp" "Law Enforcer/Level.h" "Law Enforcer/Inputs.cpp" "Law Enforcer/Inputs.h" "Law Enforcer/Player.cpp" "Law Enforcer/Player.h" "Law Enforcer/Boss.cpp" "Law Enforcer/Boss.h" "Law Enforcer/global_definitions.h" "Law Enforcer/global_definitions.cpp" "Law Enforcer/PlayerContactListener.cpp" "Law Enforcer/PlayerContactListener.h")

add_executable(gtest_LE
        "Law Enforcer/Law Enforcer.cpp"
        "Test/test.cpp" "Law Enforcer/LevelObject.cpp" "Law Enforcer/LevelObject.h" "Law Enforcer/Platform.cpp" "Law Enforcer/Platform.h" "Law Enforcer/Entity.cpp" "Law Enforcer/Entity.h" "Law Enforcer/Level.cpp" "Law Enforcer/Level.h" "Law Enforcer/Inputs.cpp" "Law Enforcer/Inputs.h" "Law Enforcer/Player.cpp" "Law Enforcer/Player.h" "Law Enforcer/Boss.cpp" "Law Enforcer/Boss.h" "Law Enforcer/global_definitions.h" "Law Enforcer/global_definitions.cpp" "Law Enforcer/PlayerContactListener.cpp" "Law Enforcer/PlayerContactListener.h")

find_package(GTest REQUIRED)
if(GTest_FOUND)
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "GTest pas trouvé")
endif()

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
if(SFML_FOUND)
    target_link_libraries(Law_Enforcer sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
endif()

find_path(PugiXML_INCLUDE_DIR pugixml.hpp)
include_directories(${PugiXML_INCLUDE_DIR})
target_link_directories(Law_Enforcer PRIVATE ${PugiXML_INCLUDE_DIR})

find_package(Box2D REQUIRED)
if(Box2D_FOUND)
    target_link_libraries(Law_Enforcer Box2D)
endif()
