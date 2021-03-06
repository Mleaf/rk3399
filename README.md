[![license][1]][2]

[1]: https://img.shields.io/badge/license-GPLV3-brightgreen.svg?style=plastic
[2]: https://github.com/Mleaf/rk3399/blob/main/COPYING.LGPL

## 关于本项目：
本项目是各种RK3399主板的研究，逆向分析，以及Android，openwrt，LibreELEC，Armbian的适配。


## 已经适配的主板介绍：
#### 1：SWH-5190-V2.2
目前已经通过逆向SWH-5190-V2.2（一款RK3399主控的高性能智能主板）的看门狗程序（iic_watchdog）后，分析具体控制流程，重新实现的看门狗控制程序。

本程序和原版程序无关，非破解注入修改，实现方式也不一样，本程序完全运行于用户空间，可移植性更高。

注意：本程序禁止用于商业用途去破坏原厂固件相关功能，仅限于重新适配此主板的固件使用。

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
    src="wx.png" 
    width="500" height="500" border="0" alt="wx">
</p>

## 如果该项目对您有帮助，请毫不犹豫点star，谢谢！

## 强烈推荐佐大的 OpenWrt 培训班
想学习 OpenWrt 开发，但是摸不着门道？自学没毅力？基础太差？怕太难学不会？
不用怕大牛手把手教你OpenWrt，快来参加<跟着佐大学 OpenWrt 开发入门培训班> 佐大助你能学有所成，培训班报名地址：https://forgotfun.org/2018/04/openwrt-training-2018.html
