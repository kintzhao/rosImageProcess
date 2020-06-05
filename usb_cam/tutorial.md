

## 1. v4l2-ctl: not found
 sudo apt-get install v4l-utils


## 2. List available controls

参考： https://www.kurokesu.com/main/2016/01/16/manual-usb-camera-settings-in-linux/

v4l2-ctl -d /dev/video1 -c exposure_auto=1 
```
yhzhao@yhzhao:~/ros_ws/vision_ws/src/rosImageProcess/usb_cam/launch$ v4l2-ctl -d /dev/video0 --list-ctrls
                     brightness (int)    : min=-64 max=64 step=1 default=4 value=4
                       contrast (int)    : min=0 max=95 step=1 default=20 value=20
                     saturation (int)    : min=0 max=100 step=1 default=0 value=0
                            hue (int)    : min=-2000 max=2000 step=1 default=0 value=0
 white_balance_temperature_auto (bool)   : default=1 value=1
                          gamma (int)    : min=100 max=300 step=1 default=100 value=100
                           gain (int)    : min=16 max=255 step=1 default=32 value=32
           power_line_frequency (menu)   : min=0 max=3 default=1 value=1
      white_balance_temperature (int)    : min=2800 max=6500 step=1 default=4600 value=4600 flags=inactive
                      sharpness (int)    : min=0 max=7 step=1 default=0 value=0
         backlight_compensation (int)    : min=28 max=201 step=1 default=112 value=112
                  exposure_auto (menu)   : min=0 max=3 default=3 value=3
              exposure_absolute (int)    : min=1 max=8188 step=1 default=156 value=156 flags=inactive


```

Reading current value

```
yhzhao@yhzhao:~/ros_ws/vision_ws/src/rosImageProcess/usb_cam/launch$ v4l2-ctl --get-ctrl=white_balance_temperature
white_balance_temperature: 4600

```

Setting new value

```
> v4l2-ctl --set-ctrl=gain=00
> v4l2-ctl --set-ctrl=exposure_auto=1
> v4l2-ctl --set-ctrl=exposure_absolute=10

```





