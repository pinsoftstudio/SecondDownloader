// background.js  
  
function updateIcon(isEnabled) {  
  let iconPath = {  
    16: 'path/to/icons/icon_on_16.png',  // 16x16 图标  
    48: 'path/to/icons/icon_on_48.png'   // 48x48 图标  
  };  
  
  // 如果插件被禁用，则使用另一套图标  
  if (!isEnabled) {  
    iconPath = {  
      16: 'path/to/icons/icon_off_16.png',  
      48: 'path/to/icons/icon_off_48.png'  
    };  
  }  
  
  chrome.browserAction.setIcon({path: iconPath});  
}  
// 初始化插件的启用状态（如果尚未设置）  
chrome.storage.local.get('isPluginEnabled', function(items) {  
  if (!('isPluginEnabled' in items)) {  
    chrome.storage.local.set({'isPluginEnabled': true}); // 默认启用插件  
  }  
});  
  
// 监听插件图标的点击事件  
chrome.browserAction.onClicked.addListener(function(tab) {  
  chrome.storage.local.get('isPluginEnabled', function(result) {  
    let isEnabled = result.isPluginEnabled;  
    // 切换状态  
    isEnabled = !isEnabled;  
  
    // 将新状态存回storage  
    chrome.storage.local.set({'isPluginEnabled': isEnabled}, function() {  
      // 可以在这里添加额外的逻辑，比如发送消息给内容脚本  
      console.log('Plugin is now', isEnabled ? 'enabled' : 'disabled');  
  
      // 注意：这里的console.log仅用于演示，实际上它不会在浏览器的控制台中显示  
      // 除非你以某种方式（如通过DevTools）打开了背景脚本的调试  
    });  
  });  
});

chrome.downloads.onDeterminingFilename.addListener(function(item, suggest) {
    chrome.downloads.cancel(item.id);
    var downloadUrl = item.url;
    chrome.runtime.sendNativeMessage('com.pinsoft.sder', { url: downloadUrl }, function(response) {
      console.log('Message sent to native app:', response);
    });
  });
