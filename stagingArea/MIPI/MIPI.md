
四种操作模式：
- 控制模式 CLK\DATA
- 高速传输模式 CLK\DATA
- 脱离模式 DATA
- 超低功耗状态模式 CLK\DATA

![[stagingArea/MIPI/企业微信截图_17301051657470.png]]

![[stagingArea/MIPI/企业微信截图_17301065356836.png]]

CPU进入HS模式
- CLK进入高速
	1. 观察初始状态LP-11
	2. 观察LP-11 -> LP-01
	3. 观察LP-01 -> LP-00
	4. 接收LP-00 -> HS-01
	5. 接收时钟信号
- DATA进入高速
	1. 观察初始状态LP-11
	2. 观察LP-11 -> LP-01
	3. 观察LP-01 -> LP-00
	4. 接收LP-00 -> HS-01
	5. 寻找00011101开始同步

![[stagingArea/MIPI/企业微信截图_17301066297410.png]]

![[stagingArea/MIPI/企业微信截图_17301067207014.png]]

![[stagingArea/MIPI/企业微信截图_17301082072248.png]]

![[stagingArea/MIPI/企业微信截图_17301076449828.png]]