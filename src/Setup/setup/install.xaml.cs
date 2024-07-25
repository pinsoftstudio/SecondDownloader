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
using System.Diagnostics;
using Microsoft.Win32;
namespace setup
{
    /// <summary>
    /// install.xaml 的交互逻辑
    /// </summary>
    /// 


    public partial class install : Page
    {
        public async Task copy(string p,string t)
        {
            await Task.Delay(200);
            if (!Directory.Exists(t))
            {
                Directory.CreateDirectory(t);
            }

            string[] files = System.IO.Directory.GetFiles(p);
            foreach (string file in files)
            {
                string name = System.IO.Path.GetFileName(file);
                string dest = System.IO.Path.Combine(t, name);
                File.Copy(file, dest,true);
                pb.Value++;

            }
            string[] folders = System.IO.Directory.GetDirectories(p);
            foreach (string folder in folders)
            {
                string name = System.IO.Path.GetFileName(folder);
                string dest = System.IO.Path.Combine(t, name);
                copy(folder, dest);
            }
        }
        public int count(string p)
        {
            var ret = Directory.GetFiles(p).Length;
            
            string[] folders = System.IO.Directory.GetDirectories(p);
            foreach (string folder in folders)
            {
                ret += count(folder);
            }
            return ret;
        }

        public void creatShortcut(string loc, string exeFileName, string uninstallExeName, string folderName)
        {
            //public void creatShortcut(string loc, string exeFileName,  string folderName)
            //{

             var shellType = Type.GetTypeFromProgID("WScript.Shell");
            dynamic shell = Activator.CreateInstance(shellType);
            //创建主程序桌面快捷方式
            var shortcut = shell.CreateShortcut(Path.Combine
                (Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory),  exeFileName+".lnk"));
            shortcut.TargetPath = Path.Combine(loc, exeFileName + ".exe");
            shortcut.WorkingDirectory = loc;
            shortcut.Save();

            //创建主程序开始菜单快捷方式
            
            if (!Directory.Exists(Path.Combine("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs", folderName  )))
            {
                Directory.CreateDirectory(Path.Combine("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs", folderName ));
            }
               
            shortcut = shell.CreateShortcut(Path.Combine("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs", folderName ,exeFileName + ".lnk"));
            shortcut.TargetPath = Path.Combine(loc, exeFileName + ".exe");
            shortcut.WorkingDirectory = loc;
            shortcut.Save();

            //创建卸载程序开始菜单快捷方式
            shortcut = shell.CreateShortcut(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.StartMenu), folderName + "/", uninstallExeName + ".lnk"));
            shortcut.TargetPath = Path.Combine(loc, uninstallExeName + ".exe");
            shortcut.WorkingDirectory = loc;
            shortcut.Save();

        }
        public void addRegForUnistall(string loc,string exeFileName, string uninstallExeName,
            string publisher,string displayversion)
        {

            Registry.SetValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + exeFileName,
                "DisplayIcon", Path.Combine(loc, exeFileName + ".exe"));
            Registry.SetValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + exeFileName,
                "UninstallString", Path.Combine(loc, uninstallExeName + ".exe"));
            Registry.SetValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + exeFileName,
                "DisplayName", exeFileName);
            Registry.SetValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + exeFileName,
                "Publisher", publisher);
            Registry.SetValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + exeFileName,
                "DisplayVersion", displayversion);
           
            



        }
        public void exfile(string loc)
        {
            Assembly assembly = System.Reflection.Assembly.GetEntryAssembly();

            //列出所有资源名称
                                       //string fileName = assembly.GetName().Name + ".Resources.Rc1.grf";

            BufferedStream input = new BufferedStream(assembly.GetManifestResourceStream("setup.cnt.zip"));
            
            Application.Current.Dispatcher.Invoke(() =>
            {
            pb.Maximum = input.Length/1024;
                // Access or modify UI elements here
            });
            FileStream output = new FileStream(Path.Combine(loc,"tmp.zip"), FileMode.Create);
            byte[] data = new byte[1024];
            int lengthEachRead;
            int k = 0;
            while ((lengthEachRead = input.Read(data, 0, data.Length)) > 0)
            {
                output.Write(data, 0, lengthEachRead);
                k++;

                Application.Current.Dispatcher.Invoke(() =>
                {
                    pb.Value++;
                    // Access or modify UI elements here
                });
            }

            Application.Current.Dispatcher.Invoke(() =>
            {
                pb.IsIndeterminate = true;
            });
            output.Flush();
            output.Close();
        }
        
        public void deleteForReInstall(string loc)
        {
            
                Process[] pocesses = Process.GetProcessesByName("SecondDownloader");
                foreach (Process process in pocesses)
                {
                    try {
                    process.Kill();
                    process.WaitForExit();
                    }  
                    catch {}
                    
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
            string[] filePaths = Directory.GetFiles(loc);
                foreach (string filePath in filePaths)
                {

                    File.Delete(filePath);
                }
                string[] directories = Directory.GetDirectories(loc);
                foreach (string directory in directories)
                {
                    if (directory.PadRight(directory.Length - directory.LastIndexOf("\\") - 1) != "data")
                    {
                        deleteForReInstall(directory);
                    }

                }
            

        }
        public install(string loc)
        {
            InitializeComponent();
            loc = Path.Combine(loc, "Pinsoft\\SecondDownloader");
            if (!Directory.Exists(loc))
            {
                Directory.CreateDirectory(loc);
            }
            
            Task task = new Task(() => {
                deleteForReInstall(loc);
                exfile(loc);
                Console.Write("释放完成\n");
                ZipFile.ExtractToDirectory(Path.Combine(loc, "tmp.zip"), loc);
                Application.Current.Dispatcher.Invoke(() =>
                {
                    NavigationService.Navigate(new finish());
                });
                creatShortcut(loc, "SecondDownloader",  "Uninstall","Pinsoft\\SecondDownloader");
                addRegForUnistall(loc, "SecondDownloader", "Uninstall", "Pinsoft Studio organisation.冰软工作室", "1.0.0.0");
                File.Delete(Path.Combine(loc, "tmp.zip"));
                Process.Start(Path.Combine(loc, "SecondDownloader.exe"));
            });
            //启动任务,并安排到当前任务队列线程中执行任务
            task.Start();

            //pb.Maximum=count("pack://cnt");
            //ResourceManager rm = new ResourceManager();
            //Task tasks = copy("pack://cnt", loc);

        }
    }
}
