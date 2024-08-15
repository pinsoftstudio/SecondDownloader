using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Net.Http;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using System.Diagnostics;
namespace Update
{
    /// <summary>
    /// CheckForUpdate.xaml 的交互逻辑
    /// </summary>
    public partial class CheckForUpdate : Page
    {
        bool Silent = false;
        [DllImport("kernel32")] //返回0表示失败，非0为成功
        private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);
        [DllImport("kernel32")] //返回取得字符串缓冲区的长度
        private static extern int GetPrivateProfileString(string section, string key, string def, byte[] retVal, int size, string filePath);
        string currentVersion = "v.1.0.0.0";
        public async Task<string> GetLatestVersion()
        {


            string latestVersion;
            string savedFilePath;
            string tempPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "UpdateTemp");
            string versiontxtPath = System.IO.Path.Combine(tempPath, "VERSION.txt");
            if (File.Exists(versiontxtPath))
            {
                File.Delete(versiontxtPath);
            }
            if (!Directory.Exists(tempPath))
            {
                Directory.CreateDirectory(tempPath);
            }

            using (RegistryKey regKey = Registry.LocalMachine.OpenSubKey("SOFTWARE\\Pinsoft\\SecondDownloader", true))
            {
                //获取注册表中当前版本号
                if (regKey != null)
                {

                    currentVersion = regKey.GetValue("Version", "v.1.0.0.1") as string;
                }
            }
            try
            {
                using (HttpClient client = new HttpClient())
                {
                    //获取服务器最新版本信息
                    string versionQueryUrl = "https://gitee.com/pinsoft/sdup/raw/master/VERSION.zip";
                    using (HttpResponseMessage response = await client.GetAsync(versionQueryUrl, HttpCompletionOption.ResponseHeadersRead))
                    {
                        response.EnsureSuccessStatusCode();
                        string filename = "VERSION.zip";
                        savedFilePath = System.IO.Path.Combine(tempPath, filename);
                        using (Stream contentStream = await response.Content.ReadAsStreamAsync(), fstream = new FileStream(savedFilePath, FileMode.Create, FileAccess.Write, FileShare.None, 4096, true))
                        {
                            await contentStream.CopyToAsync(fstream);

                        }

                        ZipFile.ExtractToDirectory(savedFilePath, tempPath);

                        latestVersion = File.ReadAllText(versiontxtPath).ToLower();



                    }

                }
                return latestVersion;

            }
            catch (HttpRequestException e)
            {
                // 处理HTTP请求异常  
                MessageBox.Show($"HTTP请求失败: {e.Message}");
                return null;
            }
            catch (Exception e)
            {
                // 处理其他异常  
                MessageBox.Show($"发生错误: {e.Message}");
                return null;
            }

        }
        
        public async Task getVersionDetailsToFile(string Version)
        {
            string detail;
            string tempPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "UpdateTemp", Version);
            string tempTxtFilePath = System.IO.Path.Combine(tempPath, "detail.txt");
            string tempZipFilePath = System.IO.Path.Combine(tempPath, "detail.zip"); ;
            if (!Directory.Exists(tempPath))
            {
                Directory.CreateDirectory(tempPath);
            }
            if (File.Exists(tempTxtFilePath))
            {
                File.Delete(tempTxtFilePath);   
            }
            try
            {
                using (HttpClient client = new HttpClient())
                {
                    string queryUrl = "https://gitee.com/pinsoft/sdup/raw/master/" + Version + "/detail.zip";
                    using (HttpResponseMessage response = await client.GetAsync(queryUrl, HttpCompletionOption.ResponseHeadersRead))
                    {
                        response.EnsureSuccessStatusCode();
                        using (Stream stream = await response.Content.ReadAsStreamAsync(), fstream = new FileStream(tempZipFilePath, FileMode.Create, FileAccess.Write, FileShare.None, 4096, true))
                        {
                            //下载对应版本号更新详细信息文件
                            await stream.CopyToAsync(fstream);
                        }
                        ZipFile.ExtractToDirectory(tempZipFilePath, tempPath);

                        
                    }
                }
            }
            catch (HttpRequestException e)
            {
                // 处理HTTP请求异常  
                MessageBox.Show($"HTTP请求失败: {e.Message}");

            }
            catch (Exception e)
            {
                // 处理其他异常  
                MessageBox.Show($"发生错误: {e.Message}");

            }

        }
        public async Task<string> getIniValue(string section, string key, string filePathName)
        {
            //StringBuilder sb = new StringBuilder(255);
            
            byte[] Buffer = new byte[1024];
            int i = GetPrivateProfileString(section, key, "", Buffer, 1024, filePathName);
            string result = Encoding.UTF8.GetString(Buffer, 0, i);
            return result;
        }
        public async Task getToDownloads()
        {
            await Task.Delay(TimeSpan.FromSeconds(1.8));

            
            string latestVersion = await GetLatestVersion();
            HashSet<string> listAddOrChange = new HashSet<string>();
            HashSet<string> listDelete = new HashSet<string>();
            HashSet<string> listMessage= new HashSet<string>();
            List<bool> needUpdateQt = new List<bool>();
            List<bool> needUpdateTr=new List<bool>();
            List<bool> needUpdatePlugin = new List<bool>();
            bool updateQt=false;
            bool updateTr=false;
            bool updatePlugin=false;
            //bool[] needUpdateQt = null;
            
            
            string QtUpdateUrl = "https://github.com/ProgramCX/QtModulesForSD/releases/download/update/qt_win.zip";
            string TrUpdateUrl = "https://github.com/ProgramCX/QtModulesForSD/releases/download/update/tr.zip";
            string proxyUrl = null;
            string CommonUpdateUrl = null;
            int[] currentSingleVersion = { 1, 0, 0, 0 };
            int[] latestSingleVersion = { 1, 0, 0, 0 };
            //提取当前版本号
            Match currentMatch = Regex.Match(currentVersion, "v\\.((\\d)(?:.)(\\d)(?:.)(\\d)(?:.)(\\d))");
            if (currentMatch.Success)
            {
                int major = int.Parse(currentMatch.Groups[2].Value);
                int minor = int.Parse(currentMatch.Groups[3].Value);
                int patch = int.Parse(currentMatch.Groups[4].Value);
                int date = int.Parse(currentMatch.Groups[5].Value);
                currentSingleVersion[0] = major;
                currentSingleVersion[1] = minor;
                currentSingleVersion[2] = patch;
                currentSingleVersion[3] = date;
            }
            //提取最新版本号
            Match latestMatch = Regex.Match(latestVersion, "v\\.((\\d)(?:.)(\\d)(?:.)(\\d)(?:.)(\\d))");
            if (latestMatch.Success)
            {
                int major = int.Parse(latestMatch.Groups[2].Value);
                int minor = int.Parse(latestMatch.Groups[3].Value);
                int patch = int.Parse(latestMatch.Groups[4].Value);
                int date = int.Parse(latestMatch.Groups[5].Value);
                latestSingleVersion[0] = major;
                latestSingleVersion[1] = minor;
                latestSingleVersion[2] = patch;
                latestSingleVersion[3] = date;
            }
            if (latestSingleVersion[0] == currentSingleVersion[0] &&
                latestSingleVersion[1] == currentSingleVersion[1] &&
                latestSingleVersion[2] == currentSingleVersion[2])
            {
                if (Silent)
                {
                    App.Current.Shutdown();
                }
                else
                {
                    string v = "V." + latestSingleVersion[0].ToString() + "." +
                                   latestSingleVersion[1].ToString() + "." + latestSingleVersion[2].ToString() + "." + latestSingleVersion[3].ToString();
                    NavigationService.Navigate(new NoNeed(v));
                    return;
                }
                
            }
            string Version = latestSingleVersion[0].ToString() + "." +
                                    latestSingleVersion[1].ToString() + "." + latestSingleVersion[2].ToString() + "." + latestSingleVersion[3].ToString();
            string LatestTempPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "UpdateTemp", Version);
            string LatestTempTxtFilePath = System.IO.Path.Combine(LatestTempPath, "detail.txt");
            await getVersionDetailsToFile(Version);
            int[] lastSupported = { int.Parse(await getIniValue("lastsupported","major",LatestTempTxtFilePath)),
                int.Parse(await getIniValue("lastsupported","minor",LatestTempTxtFilePath)),
                int.Parse(await getIniValue("lastsupported","patch",LatestTempTxtFilePath)),
                int.Parse(await getIniValue("lastsupported","date",LatestTempTxtFilePath)),
            };
            

          


            if (currentSingleVersion[0] < lastSupported[0])
            {
                MessageBox.Show("抱歉，由于您的版本SecondDownloader软件版本太旧，已经不受支持。请到 https://github.com/pinsoftstudio/SecondDownloader/releases 下载最新版本。我们对给您带来的不便深感抱歉。", "您的SecondDownloader版本不受支持", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                Process.Start("https://github.com/pinsoftstudio/SecondDownloader/releases");
                Application.Current.Shutdown();
                //TODO:下载新的安装包
                return;
            }
            else
            {
                if (currentSingleVersion[1] < lastSupported[1])
                {
                    MessageBox.Show("抱歉，由于您的SecondDownloader软件版本太旧，已经不受支持。请到 https://github.com/pinsoftstudio/SecondDownloader/releases 下载最新版本。我们对给您带来的不便深感抱歉。", "您的SecondDownloader版本不受支持", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    Process.Start("https://github.com/pinsoftstudio/SecondDownloader/releases");
                    Application.Current.Shutdown();
                    //TODO:下载新的安装包
                    return;
                }
                else
                {
                    if (currentSingleVersion[2] < lastSupported[2])
                    {
                        MessageBox.Show("抱歉，由于您的SecondDownloader软件版本太旧，已经不受支持。请到 https://github.com/pinsoftstudio/SecondDownloader/releases 下载最新版本。我们对给您带来的不便深感抱歉。", "您的SecondDownloader版本不受支持", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                        Process.Start("https://github.com/pinsoftstudio/SecondDownloader/releases");
                        Application.Current.Shutdown();
                        //TODO:下载新的安装包
                        return;
                    }
                    else
                    {
                        if (currentSingleVersion[3] < lastSupported[3])
                        {
                            MessageBox.Show("抱歉，由于您的SecondDownloader软件版本太旧，已经不受支持。请到 https://github.com/pinsoftstudio/SecondDownloader/releases 下载最新版本。我们对给您带来的不便深感抱歉。", "您的SecondDownloader版本不受支持", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                            Process.Start("https://github.com/pinsoftstudio/SecondDownloader/releases");
                            Application.Current.Shutdown();
                            //TODO:下载新的安装包
                            return;
                        }
                    }
                }
            }

            if (currentSingleVersion[0] == latestSingleVersion[0])
            {
                if (currentSingleVersion[1] == latestSingleVersion[1])
                {
                    if (currentSingleVersion[2] == latestSingleVersion[2])
                    {
                        if (currentSingleVersion[3] == latestSingleVersion[3])
                        {
                            if (Silent)
                            {
                                Application.Current.Shutdown();
                            }
                            else
                            {
                                string v="V."+ latestSingleVersion[0].ToString() + "." +
                                    latestSingleVersion[1].ToString() + "." + latestSingleVersion[2].ToString() + "." + latestSingleVersion[3].ToString();
                                NavigationService.Navigate(new NoNeed(v));
                                return;
                            }
                           
                        }
                        else
                        {
                            //只有日期版本号不一样
                            int differNums = latestSingleVersion[3] - currentSingleVersion[3];

                            for (int i = currentSingleVersion[3] + 1; i <= latestSingleVersion[3]; i++)
                            {
                                string version = latestSingleVersion[0].ToString() + "." +
                                    latestSingleVersion[1].ToString() + "." + latestSingleVersion[2].ToString() + "." + i.ToString();
                                await getVersionDetailsToFile(version);
                                string tempPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "UpdateTemp", version);
                                string tempTxtFilePath = System.IO.Path.Combine(tempPath, "detail.txt");
                                //获取增加或修改文件个数
                                int addCounts = int.Parse(await getIniValue("global", "addchangenumbers", tempTxtFilePath));
                                //获取增加文件集合
                                for (int j = 0; j < addCounts; j++)
                                {
                                    string keyName = "file" + j.ToString();
                                    string aDetail = await getIniValue("addchange", keyName, tempTxtFilePath);
                                    listAddOrChange.Add(aDetail);
                                }
                                //获取减少文件个数
                                int delCounts = int.Parse(await getIniValue("global", "delnumbers", tempTxtFilePath));
                                //获取减少文件集合
                                for (int j = 0; j < delCounts; j++)
                                {
                                    string keyName = "file" + j.ToString();
                                    string aDetail = await getIniValue("delete", keyName, tempTxtFilePath);
                                    listDelete.Add(aDetail);
                                }
                                //获取更新信息个数
                                int messageCount = int.Parse(await getIniValue("global", "messagenum", tempTxtFilePath));
                                //获取更新信息集合
                                for (int j = 0; j < messageCount; j++)
                                {
                                    string keyName = "msg" + j.ToString();
                                    string aDetail = await getIniValue("message", keyName, tempTxtFilePath);
                                    listMessage.Add(aDetail);
                                }

                                string needUpdateQtStr = await getIniValue("global", "qt", tempTxtFilePath);
                                needUpdateQt.Add(bool.Parse(needUpdateQtStr));
                                //needUpdateQt[i] = bool.Parse(needUpdateQtStr);
                                //检查是否需要更新翻译文件
                                string needUpdateTrStr = await getIniValue("global", "tr", tempTxtFilePath);
                                needUpdateTr.Add(bool.Parse(needUpdateTrStr));
                                string needUpdatePluginStr = await getIniValue("global", "plugin", tempTxtFilePath);
                                needUpdatePlugin.Add(bool.Parse(needUpdatePluginStr));


                            }
                            //检查最终是否需要更新Qt插件
                            bool final_needUpdateQt = false;
                            bool final_needUpdateTr = false;
                            bool final_needUpdatePlugin = false;
                            final_needUpdateQt = needUpdateQt[0];
                            final_needUpdateTr = needUpdateTr[0];
                            final_needUpdatePlugin = needUpdatePlugin[0];

                            for (int k = 1; k < needUpdateQt.Count(); k++)
                            {
                                final_needUpdateQt = final_needUpdateQt || needUpdateQt[k];
                            }
                            for (int l = 1; l < needUpdateTr.Count(); l++)
                            {
                                final_needUpdateTr = final_needUpdateTr || needUpdateTr[l];
                            }
                            for (int m = 1; m < needUpdateTr.Count(); m++)
                            {
                                final_needUpdatePlugin = final_needUpdatePlugin || needUpdatePlugin[m];
                            }

                            if (final_needUpdateQt || final_needUpdateTr)
                            {


                                LatestTempTxtFilePath = System.IO.Path.Combine(LatestTempPath, "detail.txt");
                                proxyUrl = await getIniValue("proxy", "url", LatestTempTxtFilePath);

                            }

                            CommonUpdateUrl = "https://gitee.com/pinsoft/sdup/raw/master/" + Version + "/";
                            updateQt = final_needUpdateQt;
                            updateTr = final_needUpdateTr;
                            updatePlugin = final_needUpdatePlugin;



                        }
                    }
                    else
                    {
                        //获取patch版本号的差
                        int patchDiffer = latestSingleVersion[2] - currentSingleVersion[2];
                        //先对与最新版本号的patch版本号不同的所有版本号进行遍历
                        for (int i = currentSingleVersion[2]; i <= latestSingleVersion[2]; i++)
                        {
                            int startDateVersion = -1;
                            int endDateVersion = 9;
                            //如果是当前日期版本号（可能当前日期版本号不为0）
                            if (i == currentSingleVersion[2])
                            {
                                startDateVersion = currentSingleVersion[3];
                            }
                            //如果是最新日期版本号（可能最新日期版本号不为9）
                            if (i == latestSingleVersion[2])
                            {
                                endDateVersion = latestSingleVersion[3];
                            }

                            //对版本号进行遍历
                            while (startDateVersion < endDateVersion)
                            {
                                startDateVersion++;
                                string version = latestSingleVersion[0].ToString() + "." + latestSingleVersion[1].ToString() + "." +
                                    i.ToString() + "." + startDateVersion.ToString();
                                await getVersionDetailsToFile(version);
                                string tempPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "UpdateTemp", version);
                                string tempTxtFilePath = System.IO.Path.Combine(tempPath, "detail.txt");
                                //获取增加或修改文件个数
                                int addCounts = int.Parse(await getIniValue("global", "addchangenumbers", tempTxtFilePath));
                                //获取增加文件集合
                                for (int j = 0; j < addCounts; j++)
                                {
                                    string keyName = "file" + j.ToString();
                                    string aDetail = await getIniValue("addchange", keyName, tempTxtFilePath);
                                    listAddOrChange.Add(aDetail);
                                }
                                //获取减少文件个数
                                int delCounts = int.Parse(await getIniValue("global", "delnumbers", tempTxtFilePath));
                                //获取减少文件集合
                                for (int j = 0; j < delCounts; j++)
                                {
                                    string keyName = "file" + j.ToString();
                                    string aDetail = await getIniValue("delete", keyName, tempTxtFilePath);
                                    listDelete.Add(aDetail);
                                }
                                //获取更新信息个数
                                int messageCount = int.Parse(await getIniValue("global", "messagenum", tempTxtFilePath));
                                //获取更新信息集合
                                for (int j = 0; j < messageCount; j++)
                                {
                                    string keyName = "msg" + j.ToString();
                                    string aDetail = await getIniValue("message", keyName, tempTxtFilePath);
                                    listMessage.Add(aDetail);
                                }

                                string needUpdateQtStr = await getIniValue("global", "qt", tempTxtFilePath);
                                needUpdateQt.Add(bool.Parse(needUpdateQtStr));
                                //needUpdateQt[i] = bool.Parse(needUpdateQtStr);
                                //检查是否需要更新翻译文件
                                string needUpdateTrStr = await getIniValue("global", "tr", tempTxtFilePath);
                                needUpdateTr.Add(bool.Parse(needUpdateTrStr));
                                string needUpdatePluginStr = await getIniValue("global", "plugin", tempTxtFilePath);
                                needUpdatePlugin.Add(bool.Parse(needUpdatePluginStr));

                            }
                        }
                        //检查最终是否需要更新Qt插件
                        bool final_needUpdateQt = false;
                        bool final_needUpdateTr = false;
                        bool final_needUpdatePlugin = false;
                        final_needUpdateQt = needUpdateQt[0];
                        final_needUpdateTr = needUpdateTr[0];
                        final_needUpdatePlugin = needUpdatePlugin[0];

                        for (int k = 1; k < needUpdateQt.Count(); k++)
                        {
                            final_needUpdateQt = final_needUpdateQt || needUpdateQt[k];
                        }
                        for (int l = 1; l < needUpdateTr.Count(); l++)
                        {
                            final_needUpdateTr = final_needUpdateTr || needUpdateTr[l];
                        }
                        for (int m = 1; m < needUpdateTr.Count(); m++)
                        {
                            final_needUpdatePlugin = final_needUpdatePlugin || needUpdatePlugin[m];
                        }

                        if (final_needUpdateQt || final_needUpdateTr)
                        {


                            LatestTempTxtFilePath = System.IO.Path.Combine(LatestTempPath, "detail.txt");
                            proxyUrl = await getIniValue("proxy", "url", LatestTempTxtFilePath);

                        }

                        CommonUpdateUrl = "https://gitee.com/pinsoft/sdup/raw/master/" + Version + "/";
                        updateQt = final_needUpdateQt;
                        updateTr = final_needUpdateTr;
                        updatePlugin = final_needUpdatePlugin;
                    }

                }
                else {
                    //获取Minor版本号的差
                    int minorDiffer = latestSingleVersion[1] - currentSingleVersion[1];
                    for (int i = currentSingleVersion[1]; i <= latestSingleVersion[1]; i++)
                    {
                        int startPatchVersion = -1;
                        int endPatchVersion = 9;
                        if (i == currentSingleVersion[1])
                        {
                            startPatchVersion = currentSingleVersion[2];
                        }
                        if (i == latestSingleVersion[1])
                        {
                            endPatchVersion = latestSingleVersion[2];
                        }
                        while (startPatchVersion < endPatchVersion)
                        {
                            startPatchVersion++;
                            int startDateVersion = -1;
                            int endDateVersion = 9;
                            if (startPatchVersion == currentSingleVersion[2])
                            {
                                startDateVersion = currentSingleVersion[3];
                            }
                            if (endPatchVersion == latestSingleVersion[2])
                            {
                                endDateVersion = latestSingleVersion[3];
                            }
                            string version = latestSingleVersion[0].ToString() + "." + i.ToString() + "." +
                                startPatchVersion.ToString() + "." + startDateVersion.ToString();
                            await getVersionDetailsToFile(version);
                            string tempPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "UpdateTemp", version);
                            string tempTxtFilePath = System.IO.Path.Combine(tempPath, "detail.txt");
                            //获取增加或修改文件个数
                            int addCounts = int.Parse(await getIniValue("global", "addchangenumbers", tempTxtFilePath));
                            //获取增加文件集合
                            for (int j = 0; j < addCounts; j++)
                            {
                                string keyName = "file" + j.ToString();
                                string aDetail = await getIniValue("addchange", keyName, tempTxtFilePath);
                                listAddOrChange.Add(aDetail);
                            }
                            //获取减少文件个数
                            int delCounts = int.Parse(await getIniValue("global", "delnumbers", tempTxtFilePath));
                            //获取减少文件集合
                            for (int j = 0; j < delCounts; j++)
                            {
                                string keyName = "file" + j.ToString();
                                string aDetail = await getIniValue("delete", keyName, tempTxtFilePath);
                                listDelete.Add(aDetail);
                            }
                            //获取更新信息个数
                            int messageCount = int.Parse(await getIniValue("global", "messagenum", tempTxtFilePath));
                            //获取更新信息集合
                            for (int j = 0; j < messageCount; j++)
                            {
                                string keyName = "msg" + j.ToString();
                                string aDetail = await getIniValue("message", keyName, tempTxtFilePath);
                                listMessage.Add(aDetail);
                            }

                            string needUpdateQtStr = await getIniValue("global", "qt", tempTxtFilePath);
                            needUpdateQt.Add(bool.Parse(needUpdateQtStr));
                            //needUpdateQt[i] = bool.Parse(needUpdateQtStr);
                            //检查是否需要更新翻译文件
                            string needUpdateTrStr = await getIniValue("global", "tr", tempTxtFilePath);
                            needUpdateTr.Add(bool.Parse(needUpdateTrStr));
                            string needUpdatePluginStr = await getIniValue("global", "plugin", tempTxtFilePath);
                            needUpdatePlugin.Add(bool.Parse(needUpdatePluginStr));


                        }
                    }
                    //检查最终是否需要更新Qt插件
                    bool final_needUpdateQt = false;
                    bool final_needUpdateTr = false;
                    bool final_needUpdatePlugin = false;
                    final_needUpdateQt = needUpdateQt[0];
                    final_needUpdateTr = needUpdateTr[0];
                    final_needUpdatePlugin = needUpdatePlugin[0];

                    for (int k = 1; k < needUpdateQt.Count(); k++)
                    {
                        final_needUpdateQt = final_needUpdateQt || needUpdateQt[k];
                    }
                    for (int l = 1; l < needUpdateTr.Count(); l++)
                    {
                        final_needUpdateTr = final_needUpdateTr || needUpdateTr[l];
                    }
                    for (int m = 1; m < needUpdateTr.Count(); m++)
                    {
                        final_needUpdatePlugin = final_needUpdatePlugin || needUpdatePlugin[m];
                    }

                    if (final_needUpdateQt || final_needUpdateTr)
                    {


                        LatestTempTxtFilePath = System.IO.Path.Combine(LatestTempPath, "detail.txt");
                        proxyUrl = await getIniValue("proxy", "url", LatestTempTxtFilePath);

                    }

                    CommonUpdateUrl = "https://gitee.com/pinsoft/sdup/raw/master/" + Version + "/";
                    updateQt = final_needUpdateQt;
                    updateTr = final_needUpdateTr;
                    updatePlugin = final_needUpdatePlugin;

                }
            }
            else
            {
                //获取major版本号差
                int majorDiffer = latestSingleVersion[0] - currentSingleVersion[0];
                for (int i = currentSingleVersion[0]; i <= latestSingleVersion[0]; i++)
                {
                    int startMinor = -1;
                    int endMinor = 9;
                    if (i == currentSingleVersion[0])
                    {
                        startMinor = currentSingleVersion[1];
                    }
                    if (i == latestSingleVersion[0])
                    {
                        endMinor=latestSingleVersion[1];
                    }
                    while (startMinor < endMinor)
                    {
                        startMinor++;
                        int startPatch = -1;
                        int endPatch = 9;
                        if (startMinor == currentSingleVersion[1])
                        {
                            startPatch = currentSingleVersion[2];
                        }
                        if(endMinor == currentSingleVersion[1])
                        {
                            endPatch = latestSingleVersion[2];
                        }
                        while(startPatch < endPatch)
                        {
                            startPatch++;
                            int startDate = -1;
                            int endDate = 9;
                            if (startPatch == currentSingleVersion[2])
                            {
                                startDate = currentSingleVersion[3];
                            }
                            if(endPatch == currentSingleVersion[2])
                            {
                                endDate = latestSingleVersion[3];
                            }
                            string version = i.ToString() + "." + startMinor.ToString() + "."
                                + startPatch.ToString() + "." + startDate.ToString();
                            await getVersionDetailsToFile(version);
                            string tempPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "UpdateTemp", version);
                            string tempTxtFilePath = System.IO.Path.Combine(tempPath, "detail.txt");
                            //获取增加或修改文件个数
                            int addCounts = int.Parse(await getIniValue("global", "addchangenumbers", tempTxtFilePath));
                            //获取增加文件集合
                            for (int j = 0; j < addCounts; j++)
                            {
                                string keyName = "file" + j.ToString();
                                string aDetail = await getIniValue("addchange", keyName, tempTxtFilePath);
                                listAddOrChange.Add(aDetail);
                            }
                            //获取减少文件个数
                            int delCounts = int.Parse(await getIniValue("global", "delnumbers", tempTxtFilePath));
                            //获取减少文件集合
                            for (int j = 0; j < delCounts; j++)
                            {
                                string keyName = "file" + j.ToString();
                                string aDetail = await getIniValue("delete", keyName, tempTxtFilePath);
                                listDelete.Add(aDetail);
                            }
                            //获取更新信息个数
                            int messageCount = int.Parse(await getIniValue("global", "messagenum", tempTxtFilePath));
                            //获取更新信息集合
                            for (int j = 0; j < messageCount; j++)
                            {
                                string keyName = "msg" + j.ToString();
                                string aDetail = await getIniValue("message", keyName, tempTxtFilePath);
                                listMessage.Add(aDetail);
                            }

                            string needUpdateQtStr = await getIniValue("global", "qt", tempTxtFilePath);
                            needUpdateQt.Add(bool.Parse(needUpdateQtStr));
                            //needUpdateQt[i] = bool.Parse(needUpdateQtStr);
                            //检查是否需要更新翻译文件
                            string needUpdateTrStr = await getIniValue("global", "tr", tempTxtFilePath);
                            needUpdateTr.Add(bool.Parse(needUpdateTrStr));
                            string needUpdatePluginStr = await getIniValue("global", "plugin", tempTxtFilePath);
                            needUpdatePlugin.Add(bool.Parse(needUpdatePluginStr));
                        }
                    }
                }
                //检查最终是否需要更新Qt插件
                bool final_needUpdateQt = false;
                bool final_needUpdateTr = false;
                bool final_needUpdatePlugin = false;
                final_needUpdateQt = needUpdateQt[0];
                final_needUpdateTr = needUpdateTr[0];
                final_needUpdatePlugin = needUpdatePlugin[0];

                for (int k = 1; k < needUpdateQt.Count(); k++)
                {
                    final_needUpdateQt = final_needUpdateQt || needUpdateQt[k];
                }
                for (int l = 1; l < needUpdateTr.Count(); l++)
                {
                    final_needUpdateTr = final_needUpdateTr || needUpdateTr[l];
                }
                for (int m = 1; m < needUpdateTr.Count(); m++)
                {
                    final_needUpdatePlugin = final_needUpdatePlugin || needUpdatePlugin[m];
                }

                if (final_needUpdateQt || final_needUpdateTr)
                {


                    LatestTempTxtFilePath = System.IO.Path.Combine(LatestTempPath, "detail.txt");
                    proxyUrl = await getIniValue("proxy", "url", LatestTempTxtFilePath);

                }

                CommonUpdateUrl = "https://gitee.com/pinsoft/sdup/raw/master/" + Version + "/";
                updateQt = final_needUpdateQt;
                updateTr = final_needUpdateTr;
                updatePlugin = final_needUpdatePlugin;
            }
            if (!Silent)
            {
                NavigationService.Navigate(new UpdateInformation(Version, CommonUpdateUrl,
                               ref listAddOrChange, ref listDelete, ref listMessage, updateQt, updateTr, updatePlugin, proxyUrl, Silent));
            }
            else
            {
                NavigationService.Navigate(new Updating(latestVersion, CommonUpdateUrl, ref listAddOrChange, ref listDelete,
                    ref listMessage, updateQt, updateTr, updatePlugin, proxyUrl,Silent));
            }
           
        }
        public CheckForUpdate(bool silent)
        {
            Silent=silent;
            InitializeComponent();
            getToDownloads();


        }

       
    }
}
