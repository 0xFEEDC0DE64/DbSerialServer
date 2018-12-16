project(DbSerialServer)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(Qt5SerialPort CONFIG REQUIRED)

set(HEADERS
    master.h
    slave.h
)

set(SOURCES
    main.cpp
    master.cpp
    slave.cpp
)

set(DISTFILES
    serialserver.ini
)

add_executable(serialserver ${HEADERS} ${SOURCES} ${DISTFILES})

target_link_libraries(serialserver Qt5::Core Qt5::Network Qt5::SerialPort dbnetworklib)

#list(TRANSFORM DISTFILES
#     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

PREPEND(DISTFILES ${CMAKE_CURRENT_SOURCE_DIR}/ ${DISTFILES})

file(COPY ${DISTFILES}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
