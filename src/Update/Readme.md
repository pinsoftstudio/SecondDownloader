# SecondDownloader 软件更新方案

## 提供更新文件存储的平台以及基本思路

- 平台：Gitee.com ，位于 https://gitee.com/pinsoft/sdup 。

- 基本思路
  
  1. 更新程序检查更新时，从 https://gitee.com/pinsoft/sdup/raw/master/VERSION.zip 地址下载文件后解压出 VERSION.txt 文件，文件内就是最新的版本号。
  2. 程序从 HKEY_LOCAL_MACHINE\Software\Pinsoft\SecondDownloader\Common\Version 读取当前版本号，与最新版本号进行比对，如果当前版本号小于最新版本号，且qt=0，就下载 https://gitee.com/pinsoft/sdup/raw/master/[当前版本号后的一个版本]/detail.zip 到 https://gitee.com/pinsoft/sdup/raw/master/[最新版本]/detail.zip 的所有文件，并且解压，会看到这些内容（比如）：
     
     

```ini
[global] 
addchangenumbers=3
delnumbers=1
plugin=1
qt=0
tr=1
[addchange]
file0=SecondDownloader.exe
file1=libDownload.dll 
file2=libDialog.dll 
[delete]
file0=a.exe
[proxy]
url=https://mirror.ghproxy.com/
```

，如果当前版本号小于最新版本号，且qt=1，还需要下载https://github.com/ProgramCX/QtModulesForSD/releases/download/update/qt_win.zip ，并且解压替换；如果如果当前版本号小于最新版本号，且```tr=1``` ，还需要下载 https://github.com/ProgramCX/QtModulesForSD/releases/download/update/tr.zip ，然后解压替换；如果``` plugin=1 ```，则还需要下载最新版的浏览器插件进行替换。
    其中, ``` addchangenumbers=3 ```上一个版本到这个版本一共有3个文件需要更新，``` file0=SecondDownloader.exe ``` 指的是第一个需要更新的文件名称，以此类推……，并且加入更新集合中。如果当前版本号与最新版本号相差两个及以上的版本，那么就要再次下载  https://gitee.com/pinsoft/sdup/raw/master/[当前版本号后的第二个版本]/detail.zip ,提取其中要更新的文件，加入更新另一个集合中，以此类推……最后将这些集合做一个交集，得到要下载的所有文件，然后到 https://gitee.com/pinsoft/sdup/raw/master/[最新版本]/ 目录下下载所需更新的文件，进行增加或替换。
    需要删除的文件与其类似，区别是需要将需要删除文件的集合与”需要添加或更新文件的集合“进行比对，如果需要“添加或更新文件的集合里”有“需要删除文件的集合”的文件，该文件就不删除，而是更新。
- 备注：更新Qt的组件和翻译文件时，需要使用的代理网站地址在```[proxy]``` 的url键的值