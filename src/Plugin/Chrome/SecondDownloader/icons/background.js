chrome.downloads.onDeterminingFilename.addListener((item, suggest) => {  
    // 注意：这个事件可能不是所有下载都会触发，且可能因浏览器而异  
    console.log('Download URL:', item.url);  
    console.log('Suggested filename:', suggest.filename);  
    
    // 这里不能直接启动程序，但可以通知用户或记录信息  
    chrome.notifications.create({  
      type: 'basic',  
      iconUrl: 'icons/icon48.png',  
      title: 'Download Started',  
      message: `Download from ${item.url} has started.`,  
      priority: 2  
    });  
    
    // 如果需要，可以修改建议的文件名  
    // suggest({filename: 'new-filename.ext'});  
  });  
    
  // 注意：chrome.downloads.onDeterminingFilename 在某些情况下可能不会触发，  
  // 你可能需要结合其他事件或逻辑来判断下载是否开始。  
    
  // 如果上述事件不可用，你可以尝试监听其他事件，如 onChanged，但请注意其触发条件和限制。