###箱线图
	Max
	Q3　　　Number~Q3~ = (Number~Max~ + 1) \* 0.75　　　　if ((Number~Q3~ % 1) == 0)
　　　　　　　　　　　　　　　　　　　　　　　　Value~Q3~ =  Value~(Number~Q3~)~
　　　　　　　　　　　　　　　　　　　　　　else
　　　　　　　　　　　　　　　　　　　　　　　　Value~Q3~ =  Value~(Number~Q3~)~ + (Value~(Number~Q3 + 1~)~ - Value~(Number~Q3~)~) * 0.75
	Mid
	Q1　　　Number~Q1~ = (Number~Max~ + 1) * 0.25
	Min
	
四分位距
　IQR = Q3 - Q1
 
 
Value~Man~ = Q3 + 1.5 * IQR
Value~Min~ = Q1 - 1.5 * IQR

1 2 3 4 5 6 7

min 1
q1  2
mid 4
q3  6
max 7

IRQ = 4

min = 0
max = 6





###散布
	极差法
	
	1 离差
	2 离差平方
	3 离差平方和  总散布层度
	4 离差平方和 / (n-1)   平均散布层度
	5 离差平方和开方 标准偏差    散布量纲化
	
	3 + 4 + 5 = 变差（或变异或波动） Variation
	