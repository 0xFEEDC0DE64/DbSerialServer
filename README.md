# DbSerialServer
Makes a local serial port accessible by listening on a tcp port and forwarding all traffic in both directions.

[![Build Status](https://travis-ci.org/0xFEEDC0DE64/DbSerialServer.svg?branch=master)](https://travis-ci.org/0xFEEDC0DE64/DbSerialServer) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/f700d27ff3034879ac865cc7c8151e77)](https://www.codacy.com/app/0xFEEDC0DE64/DbSerialServer?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=0xFEEDC0DE64/DbSerialServer&amp;utm_campaign=Badge_Grade)

## Building from source
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

