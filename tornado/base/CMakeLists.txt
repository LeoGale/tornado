set(BASE_SRCS
	Thread.cpp
	ThreadPool.cpp
   )
add_library(tornado_base ${BASE_SRCS})
target_link_libraries(tornado_base pthread)

add_library(tornado_base_cxx ${BASE_SRCS})
target_link_libraries(tornado_base_cxx pthread)
set_target_properties(tornado_base_cxx PROPERTIES COMPILE_FLAGS "-std=c++0x")

install(TARGETS tornado_base DESTINATION lib)
install(TARGETS tornado_base_cxx DESTINATION lib)

#https://cmake.org/cmake/help/latest/command/file.html
# filesystem, generate a list of files that match the globbing-expression
# and store it into the <variable>. 
# file(GLOB <variable> <globbing-expression>)
# file(GLOB_RECURSE <variable> <globbing-expression>)

file(GLOB_RECURSE HEADERS "*.hh")
install(FILES ${HEADERS} DESTINATION include/tornado/base)

