﻿  
<p align="center"><img src="imgs/ico.png" width="100" height="100"></p>

<h1 align="center">SecondDownloader</h1>
<p align="center">
  <a href="https://github.com/pinsoftstudio/seconddownloader/stargazers" ><img src="https://img.shields.io/github/stars/pinsoftstudio/seconddownloader?style=round-square" alt="GitHub stars"></a>
  <a href="https://github.com/pinsoftstudio/SecondDownloader/graphs/commit-activity"><img src="https://img.shields.io/github/last-commit/pinsoftstudio/seconddownloader" alt="Last Commit"></a>
   <a href="https://github.com/pinsoftstudio/SecondDownloader/pulls"><img src="https://img.shields.io/badge/PRs-welcome-red.svg" alt="GitHub Prs"></a>
  <a href="#" ><img src="https://img.shields.io/badge/Language-C++/CSharp-blue.svg" alt="Language"></a>
 <a href="#" style="text-decoration:none"><img src="https://img.shields.io/badge/Frame-Qt/WPF-purple.svg" alt="Frame"></a>
    <a href="https://github.com/pinsoftstudio/SecondDownloader/blob/master/LICENSE.txt" style="text-decoration:none"><img src="https://img.shields.io/github/license/pinsoftstudio/seconddownloader?style=round-square" alt="GitHub License"></a>
    <a href="#" style="text-decoration:none"><img src="https://img.shields.io/github/repo-size/pinsoftstudio/seconddownloader" alt="Repo Size"/></a>
</p>


> 一个强大的文件多线程下载器，支持 Windows 10/11 ~~、Linux 操作系统~~（以后会支持）。
### 前言： 我们有一个梦想

**我们有一个梦想，就是开发出跨平台的高速、多线程下载器，可以替代IDM和迅雷的那种，而且免费、开源、无广告，还有精美的界面。经过深思熟虑，我们决定用Qt6作为主要程序框架，libcurl用于下载模块。耗时是……好吧，叫不断维护。**

## 实现的功能
- [x] 可以多线程高速下载，还不能消耗系统很多资源。这是最主要的。
- [x] 可以接管浏览器的下载任务，这就要用到浏览器插件了。
- [x] 方便管理下载内容，包括下载完的、正在下载的、下载失败的。
- [ ] 挖掘浏览器中正在浏览的资源，视频啊、音乐啊……
- [ ] 可以解析m3u8文件，并且可以根据用户要求下载、转换为特定视频格式，比如mp4。
- [x] 轻巧升级。
- [ ] 能够断点续传。
- [ ] 能够支持Linux操作系统。
- [x] 能够使用浏览器插件提供的Cookie来下载一些必须登录才能下载的文件
- [ ] 使用浏览器插件下载需要Referer的文件
- [ ] 可以自己调下载线程个数。
- [ ] 实现快速更新，这个比较难。
- 还有很多，希望大家在issue里提出。

**欢迎大家的Pr，联系邮箱：ProgramCX@outlook.com;QQ:286024799。**


**1.0.0.0版本已经完成！我们计划进行重构。**


### 程序的主要模块（计划）

**1.主模块**
 
 - 主要功能：主界面、下载管理、设置、捐赠等
    
    主程序界面：
    
    - 左侧为图片式的选项卡，包含“主界面”、“下载管理”、“设置”、“捐赠”。  
    - 中央为StackedWidget，包含了“主界面”、“下载管理”、“设置”、“捐赠”的页面。
    - 右上角有“切换主题”、“菜单”、“最小化”、“关闭”按钮。
    - “主界面”：显示接管下载天数和版本号，下方还有一些功能按钮。
    - “下载管理”：可以暂停、取消正在下载的文件、查看下载中的文件的下载进度，并且能打开已经下载完成的文件。
    - “设置”：对软件进行个性化的设置。
    - 捐赠：显示捐赠二维码。
- 编写语言/框架：C++/Qt 6.7。

**下载模块**

 - 主要功能：实现多线程下载、与主程序通过D-Bus协议通信传输下载进度。
 - 编写语言/框架：C++/Qt 6.7、 C++ libcurl 库。

 **升级模块**

 - 主要功能：对程序、组件进行升级。
 - 编写语言/框架：易语言 或 .NET for C++。

 **浏览器插件**

 - 主要功能：当浏览器有下载任务时调用下载程序、发现网页中有可下载的媒体文件时显示“下载”悬浮窗。
 - 编写语言/框架：HTML、JavaScript和CSS  。

**安装和卸载程序**

 - 主要功能：安装和卸载SecondDownloader。
 - 编写语言/框架：C#/WPF(.Net Framework 4.72)  。 

### 注意事项：

- libcurl.dll需要自己先编译，放入temp/bin/文件夹内。
- 只能用msvc系列的编译器编译，minGW编译器的debug模式下无法编译。
- 编译失败时，可以试试清除编译的文件。
            


 



