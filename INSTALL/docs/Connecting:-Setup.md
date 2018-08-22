## Connection Setup Instructions

The following set of instructions pertain to establishing a connection between the DT7816 DAQ module and a Unix-based, specifically Linux, PC. There are two ways for a user to connect the host computer (PC) to the client computer (the DT7816). The first, which is documented at length in the Getting Started guide from the manufacturer, relies on using the `web-server` example application. In this method the client and host are connected to the same network and the terminal of the client can be accessed from the host via an serial console application like [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) or even in the Unix shell (e.g., Ubuntu Budgie's [Tilix](https://gnunn1.github.io/tilix-web/) or Ubuntu's GNOME Terminal). However, this is cumbersome in the field and in general, especially when transferring or copying files (e.g., custom programs). 

The second, alternative method is to locally network the client and host. This is achieved by using the host as a NFS server and the client a NFS client. The Serial-USB cable allows the host to connect to the board so the user can access the terminal interface necessary to perform any and all operations on the DT7816 module, again using a serial console terminal. The conduit for the transfer of data is an Ethernet cable that creates the local network (LAN). (Note: older PCs may require a crossover Ethernet cable, although most modern do not.) This section will provide a step-by-step guide to setting up the LAN and NFS mounting. 

### Preliminaries

1. Connect a Linux PC to the DT7816 (DAQ) board via the USB-Serial cable (see this [Adafruit guide](https://learn.adafruit.com/welcome-to-circuitpython/advanced-serial-console-on-mac-and-linux) for instructions how; alternatively, via PuTTY). If the PC has one Ethernet port, wirelessly connect to the Internet by WiFi. Otherwise connect however you desire. On the serial end, connect the female header to the J10 pins (the centre row of the parallel row pin trio). Have the black lead attach to pin 1 (the pin closest to the J10 label and microSD card reader. Pair the PC and board with a male-to-male Ethernet cable.

2. Plug the DC power cable to the board so it boots up. In Terminal on the PC, run the command `screen /dev/ttyUSB0 115200` to connect to the serial console of the DAQ. You may have to run `sudo apt-get install screen` first. To see which serial port the board is connected, on the host computer, with the Serial-USB cable unplugged run the command `ls /dev/ttyUSB*`. Make note of the listing. Then plug in the cable and run the command again. The new appearance on the listing is the ttyUSB* that should be used in lieu of USB0.

   The terminal console will initially be blank; be patient and after a few moments press the 'return' carriage key. A soft reboot by pressing the reset button on the board will always work. Now some boot messages should be displayed. When it asks for a username (after waiting for the board to cycle through the booting process), type `root` and type `root` for the password. You now are accessing the serial console. 

3. Open another Terminal window and proceed to the sharing the host PC's Internet connection.

### Internet Connection Sharing (ICS)   

4. On the host computer, run the `ip -4 addr show scope global` command. Note the at least two network interfaces listed, one for each Ethernet port and WiFi connection. For example, if the PC has a WiFi interface called `wlp3s0` and an Ethernet interface called `enp4s0f1`, we will be connecting the board as the diagram below shows. In short the host PC serves as the gateway for the client PC, or board.

   > Internet <<==`wlp3s0`==>>|-- Host PC --|<<==`enp4s0f1`==>>----Ethernet----<<==`eth0`==>>|-- Client PC --|

   The Ethernet interface will have 'ether' somewhere beneath it. Note the IP addresses (following 'inet') for the two interfaces. (Refer to [this tutorial](http://www.somewhereville.com/2010/08/29/internet-connection-sharing-ubuntu-10-04-nat-gateway-setup-abridged-version/comment-page-1/) and [this forum post](https://ubuntuforums.org/showthread.php?t=713874)) for help.)

5. Before we can proceed to the command line, we must create a new wired connection for the host using a built-in GUI. 

   After running `nano /etc/resolv.conf` make note of the lines in the file. That is,
   ```
   nameserver ee.ff.gg.hh
   ...
   ```
   We will be reusing these later in the next steps and toward the end of this step. Exit.
 

   Under 'Settings' go to the 'Network' menu. Under the 'Wired' sub-menu, click on the gear icon. Go to the 'IPv4' tab. Set the 'IPv4 Method' to 'Manual', and add  the address `10.0.0.1` and netmask `255.0.0.0` under the 'Addresses' heading. Leave the 'Gateway' blank. Under the 'DNS' heading insert the `nameserver`.

6. Now run the command `nano /etc/network/interfaces` to edit the configurations of the interfaces such that it looks like:
   ```
   auto lo
   iface lo inet loopback

   auto wlp3s0
   iface eth0 inet dhcp

   auto enp4s0f1
   iface eth0 inet static
   address aa.bb.cc.dd
   netmask 255.255.255.0
   network aa.bb.cc.0
   broadcast aa.bb.cc.255
   ```
   where `aa.bb.cc.dd` := 10.0.0.1. We assume that the WiFi connection is assigned an IP by DHCP.

7. Next, edit `/etc/sysctl.conf` such that `# net.ipv4.ip_forward=1` is uncommented as `net.ipv4.ip_forward=1`. Write out and exit. Then run `sudo sysctl -w net.ipv4.ip_forward=1`.

8. Edit `/etc/rc.local` so that it looks like this:
   ```
   #!/bin/sh -e
   #
   # rc.local
   #
   # This script is executed at the end of each multiuser runlevel.
   # Make sure that the script will "exit 0" on success or any other
   # value on error.
   #
   # In order to enable or disable this script just change the execution
   # bits.
   #
   # By default this script does nothing.

   /sbin/iptables -P FORWARD ACCEPT
   /sbin/iptables --table nat -A POSTROUTING -o wlp3s0 -j MASQUERADE

   exit 0
   ```
   Write out and exit, and then update these changes with:
   ```
   iptables -P FORWARD ACCEPT
   iptables -t nat -A POSTROUTING -o wlp3s0 -j MASQUERADE
   ```
9. Install this package with `sudo apt-get install isc-dhcp-server` and then `nano /etc/dhcp/dhcpd.conf` in order to edit it to be:
   ```
   ddns-update-style none;
   option domain-name "mynetwork";
   option domain-name-servers ee.ff.gg.hh
   option routers 10.0.0.1;

   default-lease-time 42300;
   max-lease-time 84600;
   authoritative;

   log-facility local7;

   subnet 10.0.0.0 netmask 255.0.0.0 {
     range 10.0.0.AA to 10.0.0.ZZ;
   }
   ```
   where `AA` := 2 and `ZZ` := 255.
10. Run `nano /etc/default/isc-dhcp-server` and add `INTERFACESv4="eth0"` and, then run `/etc/init.d/isc-dhcp-server start`.

11. We now move on to the client PC. Run `nano /etc/network/interfaces` to edit it to look like:
    ```
    auto lo
    iface lo inet loopback

    auto eth0
    iface eth0 inet static
    address aa.bb.cc.AA
    netmask 255.255.255.0
    ```
    We will also edit `/etc/resolv.conf` so it has the same lines we made note of in step 4.

12. Lastly we run `/etc/init.d/networking restart` (`/etc/init.d/network-manager restart`) or and check that the board now has an internet connection by successfully running `sudo apt-get update`. 

   **Troubleshooting**

   Restart the network interface with `/etc/init.d/networking restart` on both the host and client. These steps in should work in principle. If they do not, perform these steps and then restart (reboot) both the client and host.
   For the host try running these commands:
   * Under `ifconfig`:
     * `ifconfig enp4s0f1 inet 10.0.0.1`
     * `ifconfig enp4s0f1 broadcast 10.0.0.255`
     * `ifconfig enp4s0f1 netmask 255.255.255.0`
   * Under `ip`:
     * `ip addr add 10.0.0.1/8 broadcast 10.0.0.255 dev enp4s0f1 `
     * `ip route add 10.0.0.1/8 dev enp4s0f1`
   * Run `nm-connection-editor`:
     * Edit 'Wired connection 1' -> 'IPv4 Settings' -> Select 'Shared to other computers' under 'Method' and
     * Add the address `10.0.0.1` and netmastk `8`; leave the gateway empty.

   For the client try running these commands:
   * Under `ip`:
     * `ip addr add 10.0.0.1/8 broadcast 10.0.0.255 dev eth0`
     * `ip route add 10.0.0.2/8 dev eth0`
     * `ip route add default via 10.0.0.1 dev eth0`

   If these fail, try following this official Ubuntu [guide](https://help.ubuntu.com/community/Internet/ConnectionSharing#Ubuntu_Internet_Gateway_Method_.28iptables.29).

### Network File System (NFS)

13. Now we need to set up the NFS server so we can easily transfer our programs to the board. The host PC will have an IP address of `10.0.0.1` while IP address of client PC will be `10.0.0.2`, assuming the previous steps were successful. 

14. First, make sure NFS is installed on the Linux host computer by running `sudo apt-get install nfs-kernel-server`.  Second, we need to install the client server package on the client PC. Run `sudo apt-get install nfs-common` to do so.

15.  Add the line `/opt/ti-sdk-am335x-evm-07.00.00.00 10.0.0.2/8(rw,sync,no_root_squash,no_subtree_check)` to `/etc/exports`. Restart the NFS server with `systemctl restart nfs-kernel-server`. 

16. Due to the preexisting firewall rules on the host, we need to permit port access for the client. The command `sudo ufw allow from 10.0.0.2 to any port nfs` gives permission. Check that this was successful with `sudo ufw status`. The client can now traffic through the host port `2049`. 

17. On the client PC, we need to create a directory for the NFS mount point. Create a folder with `mkdir -p /nfs/dt7816`). 

18. We then must mount the shared folder with `mount 10.0.0.1:/opt/ti-sdk-am335x-evm-07.00.00.00 /nfs/dt7816`. Now when we run `df -h` we should see the NFS directory listed. To further confirm, check with `ls -l /nfs/dt7816/`.

19. So the NFS is automatically mounted at boot up, edit the file `/etc/fstab` on the client to have the lines
    ```
    10.0.0.1:/opt/ti-sdk-am335x-evm-07.00.00.00 /nfs/dt7816 nfs auto,nofail,noatime,nolock,intr,tcp,actimeo=1800 0 0
    ```
    If you experience troubles consult [this tutorial](https://www.digitalocean.com/community/tutorials/how-to-set-up-an-nfs-mount-on-ubuntu-18-04) or [this guide](https://help.ubuntu.com/community/SettingUpNFSHowTo#NFS_quick_start).

### Network Time Protocol (NTP)

20. To synchronise the board's clock to official US Government ([NIST](https://tf.nist.gov/tf-cgi/servers.cgi)) time, set up the NTP server and client by refering the instructions on [this page](http://www.ubuntugeek.com/network-time-protocol-ntp-server-and-clients-setup-in-ubuntu.html). When editing `/etc/ntp.conf` add the following lines for the host:
    * `server time.nist.gov`
    * `restrict time.nist.gov mask 255.255.255.255 nomodify notrap noquery`
    * `restrict 10.0.0.0 mask 255.255.255.0 nomodify notrap`
    * `restrict 127.0.0.1`

    and then after saving run `/etc/init.d/ntp restart`. And for the client's `/etc/ntp.conf`, after installing `ntpdate`, add the lines:
    * `server 10.0.0.1`
    * `restrict default notrust nomodify nopeer`
    * `restrict 10.0.0.1`
    * `restrict 127.0.0.1`
   
    and then after saving run `/etc/init.d/ntp restart` on the client.
   
    To update the client's time to the host's time run these commands in the following order on the client: `service ntp stop`, `ntpdate 10.0.0.1`, `service ntp start`. This should update the local time on the client/board. You can check that it is the case by running the command `date` on the client. Should that fail, likely you'll need to add a firewall exception rule on the host. On the host run the commands:
    * `ufw disable`
    * `ufw allow from 10.0.0.2 to any port 123`
    * `ufw enable`
    * `ufw status`

    As a last resort, granted the board is connected to the internet, try again but substitute `ntpdate time.nist.gov`. If the board is restarted for any reason before deployment the `date` command likely will not return a properly synchronised time. ~To ensure the clocks are synchronised to the host field-laptop, set the current system time to the hardware clock. In order for the time to be recoverable after reboots, run `hwclock --systohc` command on the board.~ Setting the hardware clock to the current system time has thus far proved unsuccessful.