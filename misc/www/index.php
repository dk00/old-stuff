<?php
if (isset($_GET['phpinfo'])) {
  phpinfo();
} else {
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="zh-TW">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <style type="text/css">
      body { text-align:center; } h1 { background-color: #3399ff; color: #ff9966; padding:0.5em 0; } h2 { margin:0.2em 0; }
    </style>
    <title>
      歡迎使用LightyPHP - 輕量級的PHP伺服器！
    </title>
  </head>
  <body>
    <h1>歡迎使用LightyPHP</h1>
    <h2>恭喜你！如果看到這個畫面就表示網頁伺服器安裝成功</h2>
    <h2 style="color:#ff9900">
      <?php echo '看到這個字串就表示PHP可以正常運作';?></h2>
    <h2>你可以到
      <a href="http://www.nhcue.edu.tw/~u9115043/LightyPHP/">官方網站</a>
      上尋找LightyPHP的相關資訊</h2>
    <h2>有任何問題可以先查詢
      <a href="http://www.nhcue.edu.tw/~u9115043/LightyPHP/faq.html">常見問題</a>
      ，或者使用
      <a href="http://groups.google.com/group/lightyphp">論壇</a>
      尋求幫助</h2>
    <h2>感謝您使用LightyPHP！</h2>
    <hr />
    <h3>
      <a href="./index.php?phpinfo=">顯示PHP資訊</a></h3>
  </body>
</html>
<?php
}
?>