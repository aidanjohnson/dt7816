#!/bin/sh

ping -q -c8 10.0.0.1 > /dev/null

if [ $? -eq 0 ]
then
	echo "host to client ping success"
else
	echo "check connection"
fi


ping -q -c8 10.0.0.2 > /dev/null

if [ $? -eq 0 ]
then
	echo "client to host ping success"
else
	echo "check connection"
fi

