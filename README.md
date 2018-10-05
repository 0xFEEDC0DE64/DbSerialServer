# DbSerialServer
Makes a local serial port accessible by listening on a tcp port and forwarding all traffic in both directions.

# Building from source
This project can only be built as part of the project structure [DbSoftware](https://github.com/0xFEEDC0DE64/DbSoftware)

```Shell
git clone https://github.com/0xFEEDC0DE64/DbSoftware.git
cd DbSoftware
git submodule update --init --recursive DbSerialServer libs/DbNetworkLib
cd ..
mkdir build_DbSoftware
cd build_DbSoftware
qmake CONFIG+=ccache ../DbSoftware
make -j$(nproc) sub-DbSerialServer
make sub-DbSerialServer-install_subtargets
./bin/serialserver
```

