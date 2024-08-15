using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;

namespace Update
{
    /// <summary>
    /// App.xaml 的交互逻辑
    /// </summary>
    public partial class App : Application
    {
        private static Mutex mutex = new Mutex(false, "UpdateSder");
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);
            bool silent=false;
            // 尝试获取互斥锁  
            if (!mutex.WaitOne(TimeSpan.Zero, true))
            {
                // 如果无法获取互斥锁，说明程序已经在运行  
                Application.Current.Shutdown();
                return;
            }
            // 检查是否有命令行参数  
            if (e.Args.Length > 0)
            {
                // 遍历并处理每个参数  
                if (e.Args[0] == "1")
                {

                    silent = true;
                    
                }

            
            }

            // 接下来，你可以创建并显示你的主窗口  
            MainWindow mainWindow = new MainWindow(silent);
            if (silent)
            {
                mainWindow.Hide();
            }
            else {
                mainWindow.Show();
            }
            
        }
    }
}
