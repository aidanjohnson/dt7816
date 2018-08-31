#!/bin/sh

cd /opt/ti-sdk-am335x-evm-07.00.00.00/
sudo mkdir INSTALL/docs
sudo cp wiki/* INSTALL/docs
sudo tar --exclude=INSTALL.tar.gz -czvf INSTALL/INSTALL.tar.gz INSTALL
