### 固件烧录(STM32)

```bash
$ openocd \
> -f /usr/share/openocd/scripts/interface/stlink-v2.cfg \
> -f /usr/share/openocd/scripts/target/stm32f1x.cfg \
> -c init \
> -c halt \
> -c "flash write_image erase T.bin 0x80000000" \
> -c reset \
> -c shutdown
```

