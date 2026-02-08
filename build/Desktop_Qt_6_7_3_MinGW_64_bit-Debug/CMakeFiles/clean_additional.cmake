# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\conteneur_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\conteneur_autogen.dir\\ParseCache.txt"
  "conteneur_autogen"
  )
endif()
