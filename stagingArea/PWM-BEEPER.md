### Setp1: 设计用户层接口

需求分析：提供蜂鸣器的频率、响铃次数、响铃间隔、响铃持续时长、PWM占空比控制、使能控制接口。

### Setp2: 编写用户层demo

实现功能前，确认用户使用流程，编写demo程序。

![企业微信截图_17248120748447.png](https://cdn.nlark.com/yuque/0/2024/png/26311272/1724812082954-06afbebc-36c0-49fc-b3d2-f265289584b6.png#averageHue=%23f9f9f9&clientId=ua4534da9-4539-4&from=paste&height=900&id=u39b7a190&originHeight=900&originWidth=568&originalType=binary&ratio=1&rotation=0&showTitle=false&size=44151&status=done&style=none&taskId=u24e5510b-ea1c-48f7-b85f-2ab8296fa6a&title=&width=568)

  

### Setp3: 驱动接口实现

#### Setp3.1: 文件系统接口

通过添加属性，使参数接口在sysfs中暴露，方便进行调试和问题排查
``` bash
pi@MACHINE:/sys/bus/platform/devices/beeper$ ls -l
total 0
-rw-r--r-- 1 root root 4096 Feb 15 10:27 counts
lrwxrwxrwx 1 root root    0 Feb 15 10:27 driver -> ../../../bus/platform/drivers/beeper
-rw-r--r-- 1 root root 4096 Feb 15 10:27 driver_override
-rw-r--r-- 1 root root 4096 Feb 15 10:27 duration
-rw-r--r-- 1 root root 4096 Feb 15 10:27 duty
-rw-r--r-- 1 root root 4096 Feb 15 10:27 freq
-rw-r--r-- 1 root root 4096 Feb 15 10:27 intervals
-r--r--r-- 1 root root 4096 Feb 15 10:27 modalias
lrwxrwxrwx 1 root root    0 Feb 15 10:27 of_node -> ../../../firmware/devicetree/base/beeper
drwxr-xr-x 2 root root    0 Feb 15 10:27 power
-rw-r--r-- 1 root root 4096 Feb 15 10:27 status
lrwxrwxrwx 1 root root    0 Feb 14 18:11 subsystem -> ../../../bus/platform
-rw-r--r-- 1 root root 4096 Feb 14 18:11 uevent
```

#### Setp3.2: IO ctrl接口

自定义open、ioctrl接口，注册misc设备。

注：通过sysfs或ioctl的方式访问的都是相同的参数接口。

### Setp4: 接口调试

1. 确保驱动能被正常加载和卸载。
2. 确保sysfs和ioctl接口参数设置和获取均正常。

### Setp5: 驱动绑定PWM

#### Setp5.1: 设备树添加节点
确定蜂鸣器连接引脚及对应的PWM，设备树添加节点
``` dts
beeper {
    compatible = "beeper";
    pwms = <&pwmx 0 5000 1>;
};
```

#### Step5.2: PWM功能验证

### Step6: 逻辑功能开发

#### Step6.1: 功能开发
``` c
static int ringing(struct beeper *device)
{
    struct pwm_state state;
    u32 counts, duration, intervals;
    counts      = device->configs.ringing_counts;
    duration    = device->configs.ringing_duration;
    intervals   = device->configs.ringing_intervals;

    pwm_get_state(device->pwm, &state);

    state.enabled = false;
    state.period = device->period;
    pwm_set_relative_duty_cycle(&state, device->configs.ringing_duty_cycle, 100);

    while (counts-- && device->is_running)
    {
        dev_dbg(device->dev, "%s: next count is %d\n", __func__, counts);
        pwm_beeper_on(device->pwm, &state);
        device->beeper_status = BEEPER_RINGING;
        msleep(duration);
        pwm_beeper_off(device->pwm);

        dev_dbg(device->dev, "%s: is_running is %d\n", __func__, device->is_running);
        if (counts && device->is_running)
        {
            device->beeper_status = BEEPER_AWAITING;
            msleep(intervals);
        }
    }
    device->beeper_status = BEEPER_UNUSED;
    device->is_running = false;
    return 0;
}
```
#### Step6.2: 代码调试
1. 避免阻塞用户层：因为驱动中包含sleep操作，如果不进行处理，用户层会被阻塞。
	添加 struct work_struct *work，通过schedule_work(&device->work);
	让振铃线程异步运行。

1. 解决sleep期间，线程不能被停止：当ringing进入sleep后，即使有stop动作，也要等到sleep完成后才能停止。
	使用wait_event_interruptible_timeout替换sleep。stop时通过wake_up唤醒wait。

### Step7: 蜂鸣器功能验证

使用用户demo进行测试。