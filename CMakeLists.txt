project(DbSerialServer)

set(HEADERS
    master.h
    slave.h
)

set(SOURCES
    main.cpp
    master.cpp
    slave.cpp
)

add_executable(serialserver ${HEADERS} ${SOURCES})

target_link_libraries(serialserver Qt5::Core Qt5::Network Qt5::SerialPort dbnetworklib)
