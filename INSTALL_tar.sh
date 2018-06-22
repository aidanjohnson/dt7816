#!/bin/sh

cd /opt/ti-sdk-am335x-evm-07.00.00.00/
sudo cp /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/bat-array/* /opt/ti-sdk-am335x-evm-07.00.00.00/INSTALL/
cd INSTALL
sudo tar --exclude=INSTALL.tar.gz -czvf INSTALL.tar.gz *
