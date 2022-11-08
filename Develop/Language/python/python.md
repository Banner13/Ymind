[TOC]

#### Could not fetch URL https://pypi.org/simple/pip/
```bash
python3 -m pip install --upgrade pip		// 出现错误
python3 -m pip install --upgrade pip -i http://pypi.douban.com/simple --trusted-host pypi.douban.com		// 解决
```