# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/OSI-Invoicing_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/OSI-Invoicing_autogen.dir/ParseCache.txt"
  "OSI-Invoicing_autogen"
  )
endif()
