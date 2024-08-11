// background.js  
function removeNewLinesFromJson(jsonStr) {  
  // 使用正则表达式匹配所有的换行符（\n, \r\n, \r）  
  // g 标志表示全局搜索，即匹配字符串中所有的换行符，而不仅仅是第一个  
  return jsonStr.replace(/[\r\n\t ]+/g, '');  
}  
function updateIcon(isEnabled) {  
  let iconPath = {  
    "16": "icons/icon16.png", 
    "36": "icons/icon36.png", 
    "48": "icons/icon48.png",  
    "128": "icons/icon128.png" 
  };  

  if (!isEnabled) {  
    console.log("hereIconDis");
    iconPath = {  
      "16": "icons/disabled_16.png", 
      "36": "icons/disabled_36.png", 
      "48": "icons/disabled_48.png",  
      "128": "icons/disabled_128.png"  
    };  
    chrome.notifications.create('update_notification', {
      type: 'basic',
      iconUrl: 'icons/disabled.png', // 您扩展的图标
      title: 'SecondDownloader 拓展',
      message: 'SecondDownloader 拓展已经停止接管您的浏览器。点我以继续，否则以后可能无法收到通知。'
    }, function(notificationId) {});
  }else{
    chrome.notifications.create('update_notification', {
      type: 'basic',
      iconUrl: 'icons/ico.png', // 您扩展的图标
      title: 'SecondDownloader 拓展',
      message: 'SecondDownloader 拓展开始接管您的浏览器。点我以继续，否则以后可能无法收到通知。'
    }, function(notificationId) {});
  }
  


  chrome.action.setIcon({path: iconPath}, () => {
    if (chrome.runtime.lastError) {
      console.error("设置图标失败:", chrome.runtime.lastError);
    } else {
      console.log("图标更新成功！");
    }
  });  
}  
// 初始化插件的启用状态（如果尚未设置）  

chrome.storage.local.get('isPluginEnabled', function(items) {  
  
    chrome.storage.local.set({'isPluginEnabled': true}); // 默认启用插件  
  
});  
  

chrome.action.onClicked.addListener(function(tab) {  
  
  // 从本地存储中获取isPluginEnabled项的值  
  chrome.storage.local.get('isPluginEnabled', function(result) {  
    // 检查result中是否包含isPluginEnabled属性  
    let isEnabled = 'isPluginEnabled' in result ? result.isPluginEnabled : false; // 如果不存在，默认为false  
  
    // 切换状态  
    isEnabled = !isEnabled;  
  
    // 将新状态存回本地存储  
    chrome.storage.local.set({'isPluginEnabled': isEnabled}, function() {  
      // 切换图标  
      updateIcon(isEnabled); // 确保这个函数已经定义，并且能够根据isEnabled的值来更新图标  
  
      // 如果需要，可以在这里添加更多的逻辑，比如显示通知等  
    });  
  });  
});  

chrome.downloads.onDeterminingFilename.addListener(function(item, suggest) {  
  chrome.storage.local.get('isPluginEnabled', function(result) {  
    let isEnabled = 'isPluginEnabled' in result ? result.isPluginEnabled : false;  
    if (isEnabled) {  
      let downloadUrl = item.url;  
      chrome.downloads.cancel(item.id); // 注意：这可能会取消用户期望的下载  
  
      let objCookies = [];  
      chrome.cookies.getAll({ url: downloadUrl }, function(cookies) {  
        if (chrome.runtime.lastError) {  
          console.log(chrome.runtime.lastError);  
          return;  
        }  
  
        for (let cookie of cookies) {  
          objCookies.push({ name: cookie.name, value: cookie.value });  
          console.log(cookie.name + ' = ' + cookie.value);  
        }  
  
        let jsonString = JSON.stringify(objCookies, null, 2);  
        let finalString = downloadUrl + removeNewLinesFromJson(jsonString); // 注意：这里将URL和JSON字符串拼接可能不是最佳实践  
  
        console.log("final" + finalString);  
        chrome.runtime.sendNativeMessage('com.pinsoft.sder', { url: finalString }, function(response) {  
          console.log('Message sent to native app:', response);  
        });  
      });  
    }  
  });  
});
