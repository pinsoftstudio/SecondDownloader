document.getElementById('sendButton').addEventListener('click', function () {
    // 与本地应用程序建立连接
    var port = chrome.runtime.connectNative('com.pinsoft.sder');
   
    // 向本地应用程序发送消息
    port.postMessage({ message: 'Message from popup!' });
   
    // 监听来自本地应用程序的消息
    port.onMessage.addListener(function (response) {
      console.log('Received message from native app: ' + response.message);
    });
  });