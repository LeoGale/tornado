set(INSPECT_SRCS
   )

add_library(tornado_net_inspect ${INSPECT_SRCS})

install(TARGETS tornado_net_inspect DESTINATION lib)

set(HEADERS 
	)

install(FILES ${HEADERS} DESTINATION include/tornado/net/http)
