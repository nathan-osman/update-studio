set(SRC
    main.cpp
)

add_executable(updater WIN32 ${SRC})

install(TARGETS updater RUNTIME DESTINATION bin)
