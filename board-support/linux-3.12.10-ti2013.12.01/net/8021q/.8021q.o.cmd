cmd_net/8021q/8021q.o := /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-ld -EL    -r -o net/8021q/8021q.o net/8021q/vlan.o net/8021q/vlan_dev.o net/8021q/vlan_netlink.o net/8021q/vlan_gvrp.o net/8021q/vlan_mvrp.o net/8021q/vlanproc.o 