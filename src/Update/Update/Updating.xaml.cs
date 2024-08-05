using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net;
using System.Diagnostics;
using System.ComponentModel;
using System.Configuration;
namespace Update
{
    /// <summary>
    /// Updating.xaml 的交互逻辑
    /// </summary>
    
    
    public partial class Updating : Page
    {
        string regularSavePath;
        string pluginSavePath;
        string LatestVersion;
        string UpdateUrl;
        string ProxyUrl;
        HashSet<string> AddChangeList;
        HashSet<string> DeleteChangeList;
        HashSet<string> MessageList;
        bool UpdateQt;
        bool UpdateTr;
        bool UpDatePlugin;
        int downloadedRegular = 0;
        int totals=0;
        int totalDownloaded=0;
        WebClient clientRegular;
        WebClient clientQt;
        WebClient clientTr;
        WebClient clientPlugin;
        public async Task exactZip(string sourcePath, string destPath)
        {
            
            foreach (var entry in ZipFile.OpenRead(sourcePath).Entries)
            {
                
                string fullPath = System.IO.Path.Combine(destPath, entry.FullName);
                if (fullPath.EndsWith("/"))
                {
                    Directory.CreateDirectory(fullPath);
                }
                else
                {
                    entry.ExtractToFile(fullPath, true);
                }
                
                // 确保目录存在  
                Directory.CreateDirectory(System.IO.Path.GetDirectoryName(fullPath));

                // 解压文件  
                //
            }
        }
        public async Task cleanUp(bool succeed)
        {
            //清理文件
            
                NavigationService.Navigate(new Finished(LatestVersion,succeed));
                

            
        }
        public void prepare()
        {
            
            Process[] pocesses = Process.GetProcessesByName("SecondDownloader");
            foreach (Process process in pocesses)
            {
                try
                {
                    process.Kill();
                    process.WaitForExit();
                }
                catch { }

            }

            Process[] pocesses2 = Process.GetProcessesByName("Uninstall");
            foreach (Process process in pocesses2)
            {
                try
                {
                    process.Kill();
                    process.WaitForExit();
                }
                catch { }
            }

            Process[] pocesses3 = Process.GetProcessesByName("launcher");
            foreach (Process process in pocesses3)
            {
                try
                {
                    process.Kill();
                    process.WaitForExit();
                }
                catch { }
            }
            Process[] pocesses4 = Process.GetProcessesByName("run");
            foreach (Process process in pocesses3)
            {
                try
                {
                    process.Kill();
                    process.WaitForExit();
                }
                catch { }
            }
        }
        public  void downloadRegularUpdates()
        {
            clientRegular = new WebClient();
            clientRegular.DownloadProgressChanged +=new DownloadProgressChangedEventHandler(clientRegular_DownloadProgressChanged);
            clientRegular.DownloadFileCompleted += new AsyncCompletedEventHandler(clientRegular_DownloadFileCompleted);

        }
        public void downloadDownloadQt()
        {
           clientQt=new WebClient();
            clientQt.DownloadProgressChanged += new DownloadProgressChangedEventHandler(clientQt_DownloadProgressChanged);
            clientQt.DownloadFileCompleted += new AsyncCompletedEventHandler(clientQt_DownloadFileCompleted);
        }
        public void downloadTr()
        {
            clientTr=new WebClient();
            clientTr.DownloadProgressChanged += new DownloadProgressChangedEventHandler(clientTr_DownloadProgressChanged);
            clientTr.DownloadFileCompleted += new AsyncCompletedEventHandler(clientTr_DownloadFileCompleted);
        }
        public void downloadPlugin()
        {
            clientPlugin=new WebClient();
            clientPlugin.DownloadProgressChanged += new DownloadProgressChangedEventHandler(clientPlugin_DownloadProgressChanged);
            clientPlugin.DownloadFileCompleted += new AsyncCompletedEventHandler(clientPlugin_DownloadFileCompleted);
        }
       

        public Updating(string latestVersion, string updateUrl,
            ref HashSet<string> addChangeList, ref HashSet<string> deleteChangeList,
            ref HashSet<string> messageList, bool upDateQt, bool upDateTr, bool upDatePlugin,string proxyUrl)
        {
            LatestVersion = latestVersion;
            UpdateUrl = updateUrl;
            AddChangeList = addChangeList;
            DeleteChangeList = deleteChangeList;
            MessageList = messageList;
            UpDatePlugin = upDatePlugin;
            UpdateQt = upDateQt;
            UpdateTr = upDateTr;
            ProxyUrl = proxyUrl;
            regularSavePath= AppDomain.CurrentDomain.BaseDirectory;
            InitializeComponent();
            labVersion.Content = "最新版本:"+"V." + LatestVersion;
            prepare();
            downloadPlugin();
            downloadTr();
            downloadDownloadQt();
            downloadRegularUpdates();
            

            labelStatus.Content = "(" + (downloadedRegular).ToString() + "/" +
                   AddChangeList.Count().ToString() + ")正在更新...(0%):" +
                   AddChangeList.ElementAt(downloadedRegular);
            progressbar.Value = 0;
            string nowUrl = UpdateUrl + AddChangeList.ElementAt(downloadedRegular);
            clientRegular.DownloadFileAsync(new Uri(nowUrl), System.IO.Path.Combine(regularSavePath, AddChangeList.ElementAt(downloadedRegular)));
            
        }
        private void clientRegular_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
        {
            // 更新ProgressBar的Value属性  
            progressbar.Value = e.ProgressPercentage;
            // 更新Label显示下载百分比
            labelStatus.Content="("+downloadedRegular.ToString()+"/"+ 
                AddChangeList.Count().ToString()+ $")正在更新...({e.ProgressPercentage}%):" +
                AddChangeList.ElementAt(downloadedRegular);
              
            
        }

        private void clientRegular_DownloadFileCompleted(object sender, AsyncCompletedEventArgs e)
        {
            // 下载完成后执行的逻辑（可选）  
            if (e.Error == null)
            {
                downloadedRegular++;
                
                if(downloadedRegular != AddChangeList.Count())
                {
                   labelStatus.Content = "(" + (downloadedRegular+1).ToString() + "/" +
                   AddChangeList.Count().ToString() + ")正在更新...(0%):"+
                   AddChangeList.ElementAt(downloadedRegular);
                   progressbar.Value = 0;
                   string nowUrl=UpdateUrl+ AddChangeList.ElementAt(downloadedRegular);
                   clientRegular.DownloadFileAsync(new Uri(nowUrl),System.IO. Path.Combine(regularSavePath, AddChangeList.ElementAt(downloadedRegular)));

                }
                else
                {
                    if (UpdateQt)
                    {
                        labelStatus.Content = "(0/2)正在更新Qt组件...若更新速度较慢，请重启再试(0%)";
                        progressbar.Value = 0;
                        string nowurl = ProxyUrl+ "https://github.com/ProgramCX/QtModulesForSD/releases/download/update/qt_win.zip";
                        
                        clientQt.DownloadFileAsync(new Uri(nowurl), System.IO.Path.Combine(regularSavePath, "UpdateTemp","qt_win.zip"));



                    }
                    else if (UpdateTr)
                    {
                        labelStatus.Content = "(0/2)正在更新翻译文件...若更新速度较慢，请重启再试(0%)";

                        progressbar.Value = 0;
                        string nowurl = "https://gitee.com/ProgramCX/sdqt/raw/master/tr.zip";
                        clientRegular.DownloadFileAsync(new Uri(nowurl), System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "tempUpdate","tr.zip"));
                    }
                    else if (UpDatePlugin)
                    {
                        labelStatus.Content = "(0/2)正在更新浏览器插件...(0%)";
                        progressbar.Value = 0;
                        //TODO：更新浏览器插件
                    }
                    else
                    {
                        cleanUp(true);
                        //NavigationService.Navigate(new Finished());
                    }
                    
                }
                
            }
            else
            {
                labelStatus.Content = $"下载失败: {e.Error.Message}";
                cleanUp(false);
            }
        }

        private void clientQt_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
        {
            // 更新ProgressBar的Value属性  
            progressbar.Value = e.ProgressPercentage;
            // 更新Label显示下载百分比
            
            labelStatus.Content = $"(0/2)正在更新Qt组件... 若更新速度较慢，请重启再试({e.ProgressPercentage}%)";
        }

        private async void clientQt_DownloadFileCompleted(object sender, AsyncCompletedEventArgs e)
        {
              
            if (e.Error == null)
            {
                labelStatus.Content = $"(1/2)正在更新Qt组件... 若更新速度较慢，请重启再试(0%)";
                await exactZip(System.IO.Path.Combine(regularSavePath, "UpdateTemp", "qt_win.zip"), AppDomain.CurrentDomain.BaseDirectory);
                labelStatus.Content = $"(2/2)正在更新Qt组件... 若更新速度较慢，请重启再试(100%)";
                await Task.Delay(TimeSpan.FromSeconds(1));
                if (UpdateTr)
                {
                    labelStatus.Content = "(0/2)正在更新翻译文件...若更新速度较慢，请重启再试(0%)";

                    progressbar.Value = 0;
                    string nowurl =  "https://gitee.com/ProgramCX/sdqt/raw/master/tr.zip";
                    clientRegular.DownloadFileAsync(new Uri(nowurl), System.IO.Path.Combine(regularSavePath, "UpdateTemp", "tr.zip"));
                }else if (UpDatePlugin)
                {
                    labelStatus.Content = "(0/2)正在更新浏览器插件...(0%)";
                    progressbar.Value = 0;
                    //TODO：更新浏览器插件
                    
                }
                else
                {
                   cleanUp(true);
                    //NavigationService.Navigate(new Finished());
                }
            }
            else
            {
                labelStatus.Content = $"下载失败: {e.Error.Message}";
                cleanUp(false);
            }
        }

        private void clientTr_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
        {
            // 更新ProgressBar的Value属性  
            progressbar.Value = e.ProgressPercentage;
            // 更新Label显示下载百分比

            labelStatus.Content = $"(0/2)正在更新翻译文件... ({e.ProgressPercentage}%)";
        }

        private async void clientTr_DownloadFileCompleted(object sender, AsyncCompletedEventArgs e)
        {
            
            if (e.Error == null)
            {
                labelStatus.Content = $"(1/2)正在更新翻译文件... (0%)";
                await exactZip(System.IO.Path.Combine(regularSavePath, "UpdateTemp", "tr.zip"), AppDomain.CurrentDomain.BaseDirectory);
                labelStatus.Content = $"(2/2)正在更新翻译文件... (100%)";
                if (UpDatePlugin)
                {
                    //TODO:更新浏览器插件
                }
                else
                {
                    cleanUp(true) ;
                }

            }
            else
            {
                labelStatus.Content = $"下载失败: {e.Error.Message}";
                cleanUp(false);
            }
        }

        private void clientPlugin_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
        {
            // 更新ProgressBar的Value属性  
            progressbar.Value = e.ProgressPercentage;

            // 更新Label显示下载百分比  
            labelStatus.Content = $"下载进度: {e.ProgressPercentage}%";
        }

        private void clientPlugin_DownloadFileCompleted(object sender, AsyncCompletedEventArgs e)
        {
            
            if (e.Error == null)
            {
               
            }
            else
            {
                labelStatus.Content = $"下载失败: {e.Error.Message}";
                cleanUp(false) ;
            }
        }
    }
}
   

