set( NET_SRCS
	Test.cc
   )

add_library(tornado_net ${NET_SRCS})
target_link_libraries(tornado_net tornado_base)

add_library(tornado_net_cxx ${NET_SRCS})
target_link_libraries(tornado_net_cxx tornado_base_cxx)
set_target_properties(tornado_net_cxx PROPERTIES COMPILE_FLAGS "-std=c++0x")

install(TARGETS tornado_net DESTINATION lib)
install(TARGETS tornado_net_cxx DESTINATION lib)

set(HEADERS
   )

install(FILES ${HEADERS} DESTINATION include/tornado/net)

#add_subdirectory(inspect)
#add_subdirectory(http)

