开机自动配置网络
```bash
root@imx6ull14x14evk:~# cat /etc/network/interfaces
# /etc/network/interfaces -- configuration file for ifup(8), ifdown(8)

# The loopback interface
auto lo
iface lo inet loopback

# Wireless interfaces
iface wlan0 inet dhcp
        wireless_mode managed
        wireless_essid any
        wpa-driver wext
        wpa-conf /etc/wpa_supplicant.conf

iface atml0 inet dhcp

# Wired or wireless interfaces
auto eth0
iface eth0 inet static
address 192.168.1.100
netmask 255.255.255.0
dns-servers 8.8.8.8
gateway 192.168.1.1

iface eth1 inet dhcp

# Ethernet/RNDIS gadget (g_ether)
# ... or on host side, usbnet and random hwaddr
iface usb0 inet static
        address 192.168.7.2
        netmask 255.255.255.0
        network 192.168.7.0
        gateway 192.168.7.1

# Bluetooth networking
iface bnep0 inet dhcp

root@imx6ull14x14evk:~#
root@imx6ull14x14evk:~# cat /etc/init.d/user-huke.sh
#!/bin/bash
echo "Hi, My Q!"
ifup eth0
root@imx6ull14x14evk:~#
root@imx6ull14x14evk:~# cat /etc/systemd/user/huke.service
[Unit]
Description=It's Huke server

[Service]
Type=simple
ExecStart=/bin/bash -c "/etc/init.d/user-huke.sh;"

[Install]
WantedBy=multi-user.target

```