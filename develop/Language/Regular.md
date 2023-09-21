
###    de[?]o
###    '[^?]oo'
###    '[^a-z]oo'
###    grep -n '[^[:lower:]]oo' regular_express.txt
###    grep -n '^the' regular_express.txt
    grep -n 'goo*g' regular_express.txt    o*
	g.g

### [^?] ?取反
### ^[?] ?首行

	特殊符号　　　　　　  　代表意义
	[:alnum:]　　　　　　　代表英文大小写字符及数字，亦即 0-9, A-Z, a-z
	[:alpha:]　　　　　　　代表任何英文大小写字符，亦即 A-Z, a-z
	[:blank:]　　　　　　　代表空白键与 [Tab] 按键两者
	[:cntrl:]　　　　　　　代表键盘上面的控制按键，亦即包括 CR, LF, Tab, Del.. 等等
	[:digit:]　　　　　　　代表数字而已，亦即 0-9
	[:graph:]　　　　　　　除了空白字符 （空白键与 [Tab] 按键） 外的其他所有按键
	[:lower:]　　　　　　　代表小写字符，亦即 a-z
	[:print:]　　　　　　　代表任何可以被打印出来的字符
	[:punct:]　　　　　　　代表标点符号 （punctuation symbol），亦即：" ' ? ! ; : # $...
	[:upper:]　　　　　　　代表大写字符，亦即 A-Z
	[:space:]　　　　　　　任何会产生空白的字符，包括空白键, [Tab], CR 等等
	[:xdigit:]　　　　　　　代表 16 进位的数字类型，因此包括： 0-9, A-F, a-f 的数字与字符