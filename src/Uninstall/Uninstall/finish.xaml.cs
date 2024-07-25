using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
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
using System.IO;
using System.Diagnostics;
namespace setup
{
    /// <summary>
    /// finish.xaml 的交互逻辑
    /// </summary>
    public partial class finish : Page
    {
        public finish()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string currentAssemblyPath = Assembly.GetExecutingAssembly().Location; 
            string loc = System.IO.Path.GetDirectoryName(currentAssemblyPath);
            //MessageBox.Show( "cmd.exe /c timeout /t 3 & rmdir /s /q \"" + loc + "\" &pause", loc);
            Process process = Process.Start("cmd.exe", " /c timeout /t 3 & rmdir /s /q \"" + loc+ "\"");
            Application.Current.MainWindow.Close();
        }
    }
}
