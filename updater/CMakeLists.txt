set(SRC
    main.cpp
    resource.h
    updatedialog.h
    updatedialog.cpp
    updatedialog.rc
    updater.exe.manifest
)

add_executable(updater WIN32 ${SRC})

target_link_libraries(updater ComCtl32 Shlwapi)

install(TARGETS updater RUNTIME DESTINATION bin)
