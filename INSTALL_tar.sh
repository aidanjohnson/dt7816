#!/bin/sh

cd /opt/ti-sdk-am335x-evm-07.00.00.00/
sudo cp -r /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/* /opt/ti-sdk-am335x-evm-07.00.00.00/INSTALL/
sudo tar --exclude=INSTALL.tar.gz -czvf INSTALL/INSTALL.tar.gz INSTALL
