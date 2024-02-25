```bash
sudo apt update
```

```bash
sudo apt install build-essential zlib1g-dev libncurses5-dev libgdbm-dev libnss3-dev libssl-dev libsqlite3-dev libreadline-dev libffi-dev curl libbz2-dev
```

```bash
wget https://www.python.org/ftp/python/3.9.1/Python-3.9.1.tgz
```

```bash
tar -xzf Python-3.9.1.tgz
```

```bash
cd Python-3.9.1

./configure --enable-optimizations
```

```bash
make -j 20
```

```bash
sudo make install
```
