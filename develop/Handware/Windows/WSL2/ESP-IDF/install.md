```bash
sudo apt-get install git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
# Tip python3 version need >= 3.8
```

```bash
mkdir -p ~/esp
cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git
```

```bash
cd ~/esp/esp-idf
./install.sh all
# may be encounter error, if use python3.9 install
# ModuleNotFoundError: No module named '_lzma'
......
All done! You can now run:

  . ./export.sh
```

```bash
$ . ./export.sh
```

##### Ref
[[WSL1/Python3.9/install|python3.9 install]]




