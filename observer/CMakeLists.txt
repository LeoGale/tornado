set (Observer_Srcs 
    Observer.cc
)

#install (TARGETS observer DESTINATION bin)
#install (FILES observer DESTINATION include)

add_library (observer ${Observer_Srcs})
