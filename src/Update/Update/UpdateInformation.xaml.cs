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
using System.IO;
using System.Threading.Tasks;
using System.Net.Http;
using Microsoft.Win32;
namespace Update
{
    /// <summary>
    /// UpdateInformation.xaml 的交互逻辑
    /// </summary>
    /// 
    
    public partial class UpdateInformation : Page
    {
        string LatestVersion;
        string UpdateUrl;
        string ProxyUrl;
        HashSet<string> AddChangeList;
        HashSet<string> DeleteChangeList;
        HashSet<string> MessageList;
        bool UpdateQt;
        bool UpdateTr;
        bool UpDatePlugin;
        
        public UpdateInformation(string latestVersion,string updateUrl,
            ref HashSet<string> addChangeList,ref HashSet<string> deleteChangeList,
            ref HashSet<string> messageList,bool upDateQt,bool upDateTr,bool upDatePlugin,string proxyUrl)
        {
            InitializeComponent();
            LatestVersion = latestVersion;
            UpdateUrl = updateUrl;
            ProxyUrl = proxyUrl;
            AddChangeList = addChangeList;
            DeleteChangeList = deleteChangeList;
            MessageList = messageList;
            UpdateQt = upDateQt;
            UpdateTr = upDateTr;
            UpDatePlugin = upDatePlugin;
            labVersion.Content = "最新版本:" +" V."+ latestVersion;
            for(int i = 0; i < messageList.Count(); i++)
            {
                txtUpdate.AppendText((i+1).ToString()+"."+messageList.ElementAt(i)+"\n");
            }
            
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new Updating(LatestVersion, UpdateUrl,ref AddChangeList,ref DeleteChangeList,
                ref MessageList, UpdateQt, UpdateTr, UpDatePlugin,ProxyUrl));
        }
    }
}
