add_library(cucumber-cpp-sources INTERFACE)
target_sources(cucumber-cpp-sources
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/GenericDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ContextManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CukeCommands.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CukeEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CukeEngineImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HookRegistrar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Regex.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scenario.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StepManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Table.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Tag.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/connectors/wire/WireServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/connectors/wire/WireProtocol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/connectors/wire/WireProtocolCommands.cpp
)

if(GTEST_FOUND)
    target_link_libraries(cucumber-cpp-sources INTERFACE GTest::GTest)
    target_sources(cucumber-cpp-sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/drivers/GTestDriver.cpp)
endif()

if(Boost_UNIT_TEST_FRAMEWORK_FOUND)
    target_sources(cucumber-cpp-sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/drivers/BoostDriver.cpp)
endif()

if(CMAKE_EXTRA_GENERATOR OR MSVC_IDE)
    message(STATUS "Adding header files to project")
    file(GLOB_RECURSE CUKE_HEADERS "${CUKE_INCLUDE_DIR}/cucumber-cpp/*.hpp")
    if(MSVC_IDE)
        source_group("Header Files" FILES ${CUKE_HEADERS})
    endif()
    target_sources(cucumber-cpp-sources INTERFACE ${CUKE_HEADERS})
endif()

if(MINGW)
    target_link_libraries(cucumber-cpp-sources INTERFACE ws2_32)
endif(MINGW)

add_library(cucumber-cpp-nomain STATIC)
add_library(cucumber-cpp STATIC main.cpp)

target_link_libraries(cucumber-cpp-nomain PRIVATE cucumber-cpp-sources)
target_link_libraries(cucumber-cpp PRIVATE cucumber-cpp-sources)
