Windows下使用 netsh 抓包
```
netsh trace start capture=yes report=disabled
<repro>
netsh trace stop
```

抓取后使用
```
etl2pcapng.exe in.etl out.pcapng
```
将其转换为网络报文
https://github.com/microsoft/etl2pcapng