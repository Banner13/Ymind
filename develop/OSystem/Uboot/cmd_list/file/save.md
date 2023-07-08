```
save - save file to a filesystem

Usage:
save <interface> <dev[:part]> <addr> <filename> bytes [pos]
    - Save binary file 'filename' to partition 'part' on device
      type 'interface' instance 'dev' from addr 'addr' in memory.
      'bytes' gives the size to save in bytes and is mandatory.
      'pos' gives the file byte position to start writing to.
      If 'pos' is 0 or omitted, the file is written from the start.
```
