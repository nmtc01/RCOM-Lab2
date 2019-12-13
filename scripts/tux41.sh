/bin/bash
ifconfig eth0 up
ifconfig eth0 172.16.40.1/24
route add -net 172.16.41.0/24 gw 172.16.40.254
route add default gw 172.16.40.254
vi /etc/resolv.conf search netlab.fe.up.pt nameserver 172.16.1.1