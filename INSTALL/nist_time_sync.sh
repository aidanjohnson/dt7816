#!/bin/sh

service ntp stop

ntpdate 10.0.0.1

service ntp start
