[![license][1]][2]

[1]: https://img.shields.io/badge/license-GPLV3-brightgreen.svg?style=plastic
[2]: https://github.com/Mleaf/rk3399/blob/main/COPYING.LGPL

## 关于本项目：
本项目是通过逆向SWH-5190-V2.2（一款RK3399主控的高性能智能主板）的看门狗程序（iic_watchdog）后，分析具体控制流程，重新实现的看门狗控制程序。

本程序和原版程序无关，非破解注入修改，实现方式也不一样，本程序完全运行于用户空间，可移植性更高。

- SWH-5190-V2.2的安卓适配设备树请参考当前目录下的dts目录。
- 此目录文件为安卓专用，请将watchdog 目录放置在rk3399-android/vendor/rockchip/common/目录下，使用mmm vendor/rockchip/common/watchdog 编译。
- 关于安卓i2c_watchdog权限的添加请参考sepolicy目录下的patch，并将 i2c_watchdog.te 放置于device/rockchip/common/sepolicy/vendor/目录即可。
- 安卓版本代码默认启动会自动禁用SWH-5190-V2.2的硬件看门狗功能。
- 注意：本程序禁止用于商业用途去破坏原厂固件相关功能，仅限于重新适配此主板的固件使用。
- android10固件下载地址：请关注微信公众号：【WiFi物联网】，回复 SWH-5190 获取下载地址。

[SWH-5190 AIoT高性能智能主板介绍](http://www.njxwst.com/html/Androidboard/SWH/246.html)

---

## 声明：

本程序仅供学习交流，严禁用于商业用途，如有侵权请联系作者删除。

----

## 参考资料：

- https://mirrors.edge.kernel.org/pub/software/utils/i2c-tools/


----


## 欢迎加qq群讨论： [788090522](https://jq.qq.com/?_wv=1027&k=xVAMKfKH)

## 欢迎关注微信公众号获取最新动态
<p align="center">
<img 
    src="../../wx.png" 
    width="500" height="500" border="0" alt="wx">
</p>


## 如果该项目对您有帮助，请毫不犹豫点star，谢谢！
