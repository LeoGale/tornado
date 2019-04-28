set (Observer_Srcs 
    ObserverTest.cc
)

#install (TARGETS observer DESTINATION bin)
#install (FILES observer DESTINATION include)

add_library (observer ${Observer_Srcs})
