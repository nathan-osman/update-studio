set(SRC
    downloaddialog.h
    downloaddialog.cpp
    downloaddialog.rc
    main.cpp
    resource.h
    updater.exe.manifest
)

add_executable(updater WIN32 ${SRC})

target_link_libraries(updater ComCtl32 Shlwapi)

install(TARGETS updater RUNTIME DESTINATION bin)
