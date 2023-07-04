
## 串行并行
	假设现在有8位数据，分别是bit0--bit7
### 串行
                            t7      t6      t5      t4      t3      t2      t1      t0
	(device0_port0) -> bit7 -> bit6 -> bit5 -> bit4 -> bit3 -> bit2 -> bit1 -> bit0 -> (device1_port0)

### 并行
                        t0
	(device0_port0) -> bit0 -> (device1_port0)
    (device0_port1) -> bit1 -> (device1_port1)
    (device0_port2) -> bit2 -> (device1_port2)
    (device0_port3) -> bit3 -> (device1_port3)
    (device0_port4) -> bit4 -> (device1_port4)
    (device0_port5) -> bit5 -> (device1_port5)
    (device0_port6) -> bit6 -> (device1_port6)
    (device0_port7) -> bit7 -> (device1_port7)

### CPOL 和 CPHA
#### CPOL(0)  CPHA(0)
      (read)
          ______           ______
         |      |         |      |         ....... SCK
    _____|      |_________|      |_________
              (lock)

#### CPOL(0)  CPHA(1)
             (read)
          ______           ______
         |      |         |      |         ....... SCK
    _____|      |_________|      |_________
                        (lock)

#### CPOL(1)  CPHA(0)
       (read)
    _____        _________        _________
         |      |         |      |         ....... SCK
         |______|         |______|
              (lock)

#### CPOL(1)  CPHA(1)
              (read)
    _____        _________        _________
         |      |         |      |         ....... SCK
         |______|         |______|
                        (lock)