#!/bin/sh

# This distribution contains contributions or derivatives under copyright
# as follows:
#
# Copyright (c) 2010, Texas Instruments Incorporated
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# - Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
# - Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
# - Neither the name of Texas Instruments nor the names of its
#   contributors may be used to endorse or promote products derived
#   from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

cwd=`dirname $0`
. $cwd/common.sh

do_expect() {
    echo "expect {" >> $3
    check_status
    echo "    $1" >> $3
    check_status
    echo "}" >> $3
    check_status
    echo $2 >> $3
    check_status
    echo >> $3
}


echo
echo "--------------------------------------------------------------------------------"
echo "This step will set up the u-boot variables for booting the EVM."
echo "Becuase the not all AM335x devices have a NAND, the u-boot variables will"
echo "be stored in uEnv.txt on the boot partition. U-boot will read this"
echo "file on boot."
echo

ipdefault=`ifconfig | grep 'inet addr:'| grep -v '127.0.0.1' | cut -d: -f2 | awk '{ print $1 }'`
platform=`grep PLATFORM= $cwd/../Rules.make | cut -d= -f2`


echo "Autodetected the following ip address of your host, correct it if necessary"
read -p "[ $ipdefault ] " ip
echo

if [ ! -n "$ip" ]; then
    ip=$ipdefault
fi

if [ -f $cwd/../.targetfs ]; then
    rootpath=`cat $cwd/../.targetfs`
else
    echo "Where is your target filesystem extracted?"
    read -p "[ ${HOME}/targetNFS ]" rootpath

    if [ ! -n "$rootpath" ]; then
        rootpath="${HOME}/targetNFS"
    fi
    echo
fi

kernelimage="zImage-""$platform"".bin"
kernelimagesrc=`ls -1 $cwd/../board-support/prebuilt-images/$kernelimage`
kernelimagedefault=`basename $kernelimagesrc`


echo "Select Linux kernel location:"
echo " 1: TFTP"
echo " 2: SD card"
echo
read -p "[ 1 ] " kernel

if [ ! -n "$kernel" ]; then
    kernel="1"
fi

echo
echo "Select root file system location:"
echo " 1: NFS"
echo " 2: SD card"
echo
read -p "[ 1 ] " fs

if [ ! -n "$fs" ]; then
    fs="1"
fi



if [ "$kernel" -eq "1" ]; then
    echo
    echo "Available kernel images in /tftproot:"
    for file in /tftpboot/*; do
	basefile=`basename $file`
	echo "    $basefile"
    done
    echo
    echo "Which kernel image do you want to boot from TFTP?"
    read -p "[ $kernelimagedefault ] " kernelimage

    if [ ! -n "$kernelimage" ]; then
	kernelimage=$kernelimagedefault
    fi
fi

isBB="n"
isBBBlack="n"
isBBrevA3="n"
configBB="n"

check_for_beaglebone() {
    # First check if there is a rev A3 board which uses the custom VID/PID
    # combination
    lsusb -d 0403:a6d0 > /dev/null

    if [ "$?" = "0" ]
    then
        # We found a beaglebone
        isBB="y"
        isBBrevA3="y"
        return
    fi

    # Now let's check for a standard VID/PID like newer BeagleBones have
    sudo lsusb -vv -d 0403:6010 | grep "Product" | grep "BeagleBone" > /dev/null

    if [ "$?" = "0" ]
    then
        isBB="y"
        return
    fi

    # Now let's check for EVM-SK
    sudo lsusb -vv -d 0403:6010 | grep "Product" | grep "EVM-SK" > /dev/null

    if [ "$?" = "0" ]
    then
        isBB="y"
        return
    fi


    # Now let's check for BeagleBone Black
    sudo lsusb -vv -d 0403:6001 > /dev/null

    if [ "$?" = "0" ]
    then
        isBB="y"
        isBBBlack="y"
        return
     fi

}

check_for_beaglebone

if [ "$isBB" = "y" ]
then
    echo ""
    echo ""
    echo "This SDK supports both the AM335x EVM and the BeagleBone/EVM-SK."
    echo "A BeagleBone/EVM-SK has been detected as attached to your host system"
    echo "Are you wanting to configure u-boot for this device?  An"
    echo "answer of 'n' will configure u-boot for the AM335x EVM instead"
    read -p "(y/n) " configBB
fi

if [ "$configBB" = "y" ]; then
#The BeagleBone has been detected, write information to uEnv.txt


	if [ "$kernel" -eq "1" ]; then
		 if [ "$fs" -eq "1" ]; then
			#TFTP and NFS Boot
			echo "serverip=$ip" > $cwd/uEnv.txt
			echo "rootpath=$rootpath" >> $cwd/uEnv.txt
			echo "bootfile=$kernelimage" >> $cwd/uEnv.txt
			echo "ip_method=dhcp" >> $cwd/uEnv.txt
			echo "tftp_nfs_boot=run findfdt; setenv autoload no;dhcp; tftp \${loadaddr} $kernelimage; run findfdt; tftp \${fdtaddr} \${fdtfile};  run netargs; bootz \${loadaddr} - \${fdtaddr}" >> $cwd/uEnv.txt
			echo "uenvcmd=run tftp_nfs_boot" >> $cwd/uEnv.txt
		    else
			#TFTP and SD Boot
			echo "serverip=$ip" > $cwd/uEnv.txt
			echo "bootfile=$kernelimage" >> $cwd/uEnv.txt
			echo "ip_method=none" >> $cwd/uEnv.txt
			echo "tftp_sd_boot=run findfdt; setenv autoload no; dhcp ; tftp \${loadaddr} $kernelimage; tftp \${fdtaddr} \${fdtfile}; run mmcargs; bootz \${loadaddr} - \${fdtaddr}" >> $cwd/uEnv.txt
			echo "uenvcmd=run tftp_sd_boot" >> $cwd/uEnv.txt

		    fi
		else
		    if [ "$fs" -eq "1" ]; then
			#SD and NFS Boot
			echo "serverip=$ip" > $cwd/uEnv.txt
			echo "rootpath=$rootpath" >> $cwd/uEnv.txt
			echo "ip_method=dhcp" >> $cwd/uEnv.txt
			echo "uenvcmd=setenv autoload no; mmc rescan; run loadimage; run findfdt; run loadfdt; run netargs; bootz \${loadaddr} - \${fdtaddr}" >> $cwd/uEnv.txt
		    else
			#SD and SD boot
			echo "ip_method=none" > $cwd/uEnv.txt
			echo "uenvcmd=mmc rescan; run loadimage; run findfdt; run loadfdt; run mmcargs; bootz \${loadaddr} - \${fdtaddr} " >> $cwd/uEnv.txt
		    fi
	fi



	#Copy uEnv.txt to the mounted /media/boot partition
	if [ ! -d /media/boot ]; then
		echo "The boot partition doesn't appear to be mounted on the host."
		echo "If you're using a virtual machine, please ensure it has been imported to Linux"
		echo "Please ensure the boot partition is mounted and run setup.sh again."
		if [ "$isBBBlack" = "y" ]; then
			echo "We have detected that you are using a BeagleBone Black. Please ensure that the Micro USB cable is plugged in."
			echo "For more information please see: "
			echo "    http://processors.wiki.ti.com/index.php/Sitara_Linux_SDK_Setup_Script#BeagleBone_Black_Users"
		fi
		read -p "Press Enter to exit" pressEnter
		exit
	fi

	echo "Copying uEnv.txt to boot partition..."

	#Let's check to make sure it's /media/boot/ and not /media/boot_
	boots=`ls -1 /media/ | grep boot`
	if [ ! "$boots" = "boot" ]; then
		echo "There are multiple boot partions mounted in /media/."
		echo "Please unmount these partitions, reset the board, and run setup.sh again."
		read -p "Press Enter to exit" pressEnter
		exit
	fi

	cp $cwd/uEnv.txt /media/boot/
	sync
	sync



	ftdiInstalled=`lsmod | grep ftdi_sio`
	if [ -z "$ftdiInstalled" ]; then
	#Add the ability to regconize the BeagleBone as two serial ports
        if [ "$isBBrevA3" = "y" ]
        then
            echo "Finishing install by adding drivers for Beagle Bone..."
            sudo modprobe -q ftdi_sio vendor=0x0403 product=0xa6d0

            #Create uDev rule
            echo "# Load ftdi_sio driver including support for XDS100v2." > $cwd/99-custom.rules
            echo "SYSFS{idVendor}=="0403", SYSFS{idProduct}=="a6d0", \\" >>  $cwd/99-custom.rules
            echo "RUN+=\"/sbin/modprobe -q ftdi_sio vendor=0x0403 product=0xa6d0\"" >> $cwd/99-custom.rules
            sudo cp $cwd/99-custom.rules /etc/udev/rules.d/
            rm $cwd/99-custom.rules
        else
            sudo modprobe -q ftdi_sio
        fi
	fi

	#infinite loop to look for board unless user asks to stop
	while [ yes ]
	do
		echo "Detecting connection to board..."
		loopCount=0
		port=`dmesg | grep FTDI | grep "tty" | tail -1 | grep "attached" |  awk '{ print $NF }'`
		while [ -z "$port" ] && [ "$loopCount" -ne "10" ]
		do
			#count to 10 and timeout if no connection is found
			loopCount=$((loopCount+1))

			sleep 1
			port=`dmesg  | grep FTDI | grep "tty" | tail -1 | grep "attached" |  awk '{ print $NF }'`
		done

		#check to see if we actually found a port
		if [ -n "$port" ]; then
			break;
		fi

		#if we didn't find a port and reached the timeout limit then ask to reconnect
		if [ -z "$port" ] && [ "$loopCount" = "10" ]; then
			echo ""
			echo "Unable to detect which port the board is connected to."
			echo "Please reconnect your board."
			echo "Press 'y' to attempt to detect your board again or press 'n' to continue..."
			read -p "(y/n)" retryBoardDetection
		fi

		#if they choose not to retry, ask user to reboot manually and exit
		if [ "$retryBoardDetection" = "n" ]; then
			echo ""
			echo "Please reboot your board manually and connect using minicom."
			exit;
		fi
	done

	#Change minicom to accurately reflect the bone
	minicomcfg=${HOME}/.minirc.dfl
	echo "pu port             /dev/$port
	pu baudrate         115200
	pu bits             8
	pu parity           N
	pu stopbits         1
	pu minit
	pu mreset
	pu mdialpre
	pu mdialsuf
	pu mdialpre2
	pu mdialsuf2
	pu mdialpre3
	pu mdialsuf3
	pu mconnect
	pu mnocon1          NO CARRIER
	pu mnocon2          BUSY
	pu mnocon3          NO DIALTONE
	pu mnocon4          VOICE
	pu rtscts           No" | tee $minicomcfg > /dev/null
	check_status

	echo
	echo
	echo "--------------------------------------------------------------------------------"
	echo "uEnv.text has been saved to the boot partition. uEnv.txt contains:"
	cat $cwd/uEnv.txt
	echo
	echo "On the next boot, the BeagleBone will boot with these settings."
	echo "Would you like to restart now (y/n)?"
	read -p "[ y ]" restartNow

	if [ ! -n "$restartNow" ]; then
	  restartNow="y"
	fi

	if [ "$restartNow" = "y" ]; then
		echo "timeout 300" > $cwd/resetBoard.minicom
		echo "verbose on" >> $cwd/resetBoard.minicom
		echo "send \"\""  >> $cwd/resetBoard.minicom
		do_expect "\"am335x-evm login: \"" "send \"root\"" $cwd/resetBoard.minicom
		echo "send \"init 6\""  >> $cwd/resetBoard.minicom
		do_expect "\"Restarting system.\"" "! killall -s SIGHUP minicom" $cwd/resetBoard.minicom
	        # Change directory into cwd because minicom does not like . in the
	        # path to the script
	        cd $cwd
		sudo minicom -w -S resetBoard.minicom
	        cd -

	fi

	echo "--------------------------------------------------------------------------------"
	sudo minicom -w

else
#This is an AM335x EVM and thus has a NAND. Flash information to NAND.


	echo "timeout 300" > $cwd/setupBoard.minicom
	echo "verbose on" >> $cwd/setupBoard.minicom
	do_expect "\"stop autoboot:\"" "send \" \"" $cwd/setupBoard.minicom
	if [ "$kernel" -eq "1" ]; then
		if [ "$fs" -eq "1" ]; then
			#TFTP and NFS Boot
			do_expect "\"U-Boot#\"" "send \"setenv serverip $ip\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send setenv rootpath '$rootpath'" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"setenv bootfile $kernelimage\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"setenv ip_method dhcp\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send setenv bootcmd 'run findfdt; setenv autoload no;dhcp ;tftp \${loadaddr} $kernelimage; tftp \${fdtaddr} \${fdtfile}; run netargs; bootz \${loadaddr} - \${fdtaddr}'" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"saveenv\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"boot\"" $cwd/setupBoard.minicom
		else
			#TFTP and SD Boot
			do_expect "\"U-Boot#\"" "send \"setenv serverip $ip\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"setenv bootfile $kernelimage\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"setenv ip_method none\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send setenv bootcmd 'run findfdt; setenv autoload no; dhcp ; tftp \${loadaddr} $kernelimage; tftp \${fdtaddr} \${fdtfile}; run mmcargs; bootz \${loadaddr} - \${fdtaddr}'" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"saveenv\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"boot\"" $cwd/setupBoard.minicom
		fi
	else
		if [ "$fs" -eq "1" ]; then
			#SD and NFS Boot
			do_expect "\"U-Boot#\"" "send \"setenv serverip $ip\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send setenv rootpath '$rootpath'" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"setenv bootfile zImage\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"setenv ip_method dhcp\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send setenv bootcmd 'setenv autoload no; mmc rescan; run loadimage; run findfdt; run loadfdt; run netargs; bootz \${loadaddr} - \${fdtaddr}'" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"saveenv\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"boot\"" $cwd/setupBoard.minicom
		    else
			#SD and SD boot.
			do_expect "\"U-Boot#\"" "send \"setenv ip_method none\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"setenv bootfile zImage\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send setenv bootcmd 'mmc rescan; run loadimage; run findfdt; run loadfdt; run mmcargs; bootz \${loadaddr} - \${fdtaddr}'" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"saveenv\"" $cwd/setupBoard.minicom
			do_expect "\"U-Boot#\"" "send \"boot\"" $cwd/setupBoard.minicom

		fi
	fi
	echo "! killall -s SIGHUP minicom" >> $cwd/setupBoard.minicom

	echo "--------------------------------------------------------------------------------"
	echo "Would you like to create a minicom script with the above parameters (y/n)?"
	read -p "[ y ] " minicom
	echo

	if [ ! -n "$minicom" ]; then
	    minicom="y"
	fi

	if [ "$minicom" = "y" ]; then

	    echo -n "Successfully wrote "
	    readlink -m $cwd/setupBoard.minicom

	    echo "Would you like to run the setup script now (y/n)? This requires you to connect"
	    echo "the RS-232 cable between your host and EVM as well as your ethernet cable as"
	    echo "described in the Quick Start Guide. Once answering 'y' on the prompt below"
	    echo "you will have 300 seconds to connect the board and power cycle it"
	    echo "before the setup times out"
	    echo
	    echo "After successfully executing this script, your EVM will be set up. You will be "
	    echo "able to connect to it by executing 'minicom -w' or if you prefer a windows host"
	    echo "you can set up Tera Term as explained in the Software Developer's Guide."
	    echo "If you connect minicom or Tera Term and power cycle the board Linux will boot."
	    echo
	    read -p "[ y ] " minicomsetup

            if [ ! -n "$minicomsetup" ]; then
               minicomsetup="y"
            fi

            if [ "$minicomsetup" = "y" ]; then
              cd $cwd
	      sudo minicom -w -S setupBoard.minicom
              cd -
	    fi

            echo "You can manually run minicom in the future with this setup script using: minicom -S $cwd/setupBoard.minicom"
            echo "--------------------------------------------------------------------------------"

      fi
fi