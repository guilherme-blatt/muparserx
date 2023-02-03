include(FetchContent)
FetchContent_Declare(GTest
                     GIT_REPOSITORY https://github.com/google/googletest.git
                     GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850
                     FIND_PACKAGE_ARGS CONFIG)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(GTest)

if (GTest_FOUND OR gtest_POPULATED)
  set(TESTS_SRC
      src/ElementWiseOperatorsTest.cpp
      src/ElementWiseLogicalOperatorsTest.cpp
      src/ElementWiseLogicalOperatorsTest.cpp
      src/ElementWiseFunctionsTest.cpp
      src/MotecBasicFunctionsTest.cpp src/ChooseTest.cpp)
  
  #add_executable(${PROJECT_NAME}_Tests ${TESTS_SRC})
  add_executable(${PROJECT_NAME}_Tests ${TESTS_SRC} )
  
  #set_target_properties(${PROJECT_NAME}_Tests PROPERTIES
  #                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
  
  target_link_libraries(${PROJECT_NAME}_Tests PUBLIC muparserx GTest::gtest_main GTest::gtest)
  
#  if (WIN32)
#    add_custom_command(
#            TARGET ${PROJECT_NAME}_Tests POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}_Tests>
#            $<TARGET_FILE_DIR:${PROJECT_NAME}_Tests>
#            COMMAND_EXPAND_LISTS
#    )
#  endif ()
  
#  if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
#    include(GoogleTest)
#    gtest_add_tests(TARGET ${PROJECT_NAME}_Tests
#                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
#  endif ()
else ()
  message(WARNING "Could not find GTest, tests targets won't be available.")
endif ()