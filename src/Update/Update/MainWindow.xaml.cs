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
using System.Runtime.InteropServices;
using System.Windows.Interop;

namespace Update
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow(bool silent)
        {

            InitializeComponent();
            MouseLeftButtonDown += (o, e) => { DragMove(); };
            WindowStartupLocation = WindowStartupLocation.CenterScreen;
            frame.Navigate(new CheckForUpdate(silent));
            
        }
        private void frame_Navigated(object sender, NavigationEventArgs e)
        {

        }

    }
}
