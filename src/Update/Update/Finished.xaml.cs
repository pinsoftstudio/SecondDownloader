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
using System.Windows.Shapes;

namespace Update
{
    /// <summary>
    /// Finished.xaml 的交互逻辑
    /// </summary>
    public partial class Finished : Page
    {
        public Finished(string version,bool succeed)
        {
            InitializeComponent();
            if (succeed)
            {
                labVersion.Content = "最新版本：V." + version;
            }
            else {
                labState.Content = "更新失败！";
                labVersion.Content = "请向我们反馈该问题，谢谢！";
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.MainWindow.Close();
        }
    }
}
