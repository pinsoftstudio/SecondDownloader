using System;
using System.Collections.Generic;
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
using System.IO.Compression;
using System.IO;
using System.Diagnostics;
using System.Threading;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TrackBar;
using System.Resources;
using System.Reflection;
using Microsoft.Win32;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace setup
{
    /// <summary>
    /// install.xaml 的交互逻辑
    /// </summary>
    /// 


    public partial class uninstall : System.Windows.Controls.Page
    {
        public static int totalFileNum = 0;
        public static int finishedFileNum = 0;
     
        public void deleteForUninstall(string loc)
        {
            Process[] pocesses = Process.GetProcessesByName("SecondDownloader");
            foreach (Process process in pocesses)
            {
                process.Kill();
                process.WaitForExit();
            }
            string[] filePaths = Directory.GetFiles(loc);
            foreach(string filePath in filePaths)
            {

                if (filePath!= Assembly.GetExecutingAssembly().Location) {
                    try { File.Delete(filePath); }
                    catch { }
                    finishedFileNum++;

                }
               
                Application.Current.Dispatcher.Invoke(() =>
                {
                    pb.Maximum = totalFileNum;
                    pb.Value = finishedFileNum;
                });
            }
            string[] directories = Directory.GetDirectories(loc);
            foreach (string directory in directories)
            {
                deleteForUninstall(directory);
 
               
            }

        }
        public int getTotalFiles(string loc)
        {
            int fileCount = 0;
            string[] filePaths = Directory.GetFiles(loc);
            fileCount += filePaths.Count();
            string[] directories = Directory.GetDirectories(loc);
            foreach (string directory in directories)
            {
                fileCount+=getTotalFiles(directory);
            }
            
            return fileCount;
        }

        public void deleteRegAndPlugins() {

            using (RegistryKey Runkey = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", true))
            {
                if (Runkey != null)
                {
                    // 删除注册表项
                    Registry.CurrentUser.DeleteValue("SecondDownloader", false);
                }
            }
            
            
            using (RegistryKey SecondDownloaderkey = Registry.CurrentUser.OpenSubKey("SOFTWARE\\Pinsoft\\SecondDownloader", true))
            {
                if (SecondDownloaderkey != null)
                {
                    // 删除注册表项
                    Registry.CurrentUser.DeleteSubKeyTree("SOFTWARE\\Pinsoft\\SecondDownloader", false);
                }
            }
            using (RegistryKey ChromePluginkey = Registry.LocalMachine.OpenSubKey("SOFTWARE\\Google\\Chrome\\NativeMessagingHosts\\com.pinsoft.sder", true))
            {
                if(ChromePluginkey != null)
                {
                    Registry.CurrentUser.DeleteSubKeyTree("SOFTWARE\\Google\\Chrome\\NativeMessagingHosts\\com.pinsoft.sder",false);

                }
            }
            using (RegistryKey EdgePluginkey = Registry.LocalMachine.OpenSubKey("SOFTWARE\\Microsoft\\Edge\\NativeMessagingHosts\\com.pinsoft.sder", true))
            {
                if (EdgePluginkey != null)
                {
                    Registry.CurrentUser.DeleteSubKeyTree("SOFTWARE\\Microsoft\\Edge\\NativeMessagingHosts\\com.pinsoft.sder",false);

                }
            }
            using (RegistryKey MozillaPluginkey = Registry.LocalMachine.OpenSubKey("SOFTWARE\\Mozilla\\NativeMessagingHosts\\com.pinsoft.sder", true))
            {
                if (MozillaPluginkey != null)
                {
                    Registry.CurrentUser.DeleteSubKeyTree("SOFTWARE\\Mozilla\\NativeMessagingHosts\\com.pinsoft.sder", false);

                }
            }

       
            using (RegistryKey UninstallPluginkey = Registry.LocalMachine.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\SecondDownloader", true))
            {
                if (UninstallPluginkey != null)
                {
                    Registry.CurrentUser.DeleteSubKeyTree("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\SecondDownloader", false);
                }
            }

            

        }
        public void deleteShortcuts(string exeName,string folderName)
        {
            if (File.Exists(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory), exeName + ".lnk"))){
                File.Delete(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory), exeName + ".lnk"));
            }
            if (Directory.Exists(Path.Combine("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs", folderName)))
            {
                if(File.Exists(Path.Combine("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs", folderName, "SecondDownloader.lnk")))
                {
                    File.Delete(Path.Combine("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs", folderName, "SecondDownloader.lnk"));
                }
                if (File.Exists(Path.Combine("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs", folderName, "Uninstall.lnk")))
                {
                    File.Delete(Path.Combine("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs", folderName, "Uninstall.lnk"));
                }
                Directory.Delete(Path.Combine("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs", folderName));
            }

        }
        public uninstall()
        {
            InitializeComponent();
            string currentAssemblyPath = Assembly.GetExecutingAssembly().Location;
            string loc = Path.GetDirectoryName(currentAssemblyPath);          
            Task task = new Task(() => {
                totalFileNum=getTotalFiles(loc)-1;
                deleteForUninstall(loc);
                Application.Current.Dispatcher.Invoke(() =>
                {
                    pb.IsIndeterminate = true;
                });
                deleteRegAndPlugins();
                deleteShortcuts("SecondDownloader", "Pinsoft\\SecondDownloader");
                Application.Current.Dispatcher.Invoke(() =>
                {
                    NavigationService.Navigate(new finish());
                });
            });
            //启动任务,并安排到当前任务队列线程中执行任务
            task.Start();

            //pb.Maximum=count("pack://cnt");
            //ResourceManager rm = new ResourceManager();
            //Task tasks = copy("pack://cnt", loc);

        }
    }
}
