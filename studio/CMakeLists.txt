set(SRC
    main.cpp
)

add_executable(studio WIN32 ${SRC})
set_target_properties(studio PROPERTIES
    CXX_STANDARD          11
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(studio Qt5::Widgets)

install(TARGETS studio RUNTIME DESTINATION bin)
