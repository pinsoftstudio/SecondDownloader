chrome.downloads.onDeterminingFilename.addListener(function(item, suggest) {
    chrome.downloads.cancel(item.id);
    var downloadUrl = item.url;
    

    chrome.runtime.sendNativeMessage('Second Downloader Extention', { url: downloadUrl }, function(response) {
      console.log('Message sent to native app:', response);
    });
  });