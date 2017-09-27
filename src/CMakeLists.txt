CollectSourceFiles(
  ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE_SOURCES)
  
GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

CollectIncludeDirectories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  PUBLIC_INCLUDES)
  
add_library(logic
  ${PRIVATE_SOURCES})
target_include_directories(logic
  PUBLIC
    ${PUBLIC_INCLUDES})
