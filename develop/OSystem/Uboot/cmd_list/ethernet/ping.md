```
ping - send ICMP ECHO_REQUEST to network host

Usage:
ping pingAddress
```

```demo
=> ping 192.168.1.5
Using ethernet@2188000 device
host 192.168.1.5 is alive    // 成功

=> ping 192.168.2.5
Using ethernet@2188000 device

ARP Retry count exceeded; starting again
ping failed; host 192.168.2.5 is not alive   // 失败
```
