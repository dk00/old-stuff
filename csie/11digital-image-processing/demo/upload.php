<?
  $valid = (md5('dip'.$_POST['pass']) == '22cce7d8d94afb075c0f3cef56acc227');
  $mes='';
  if($valid && $file=&$_FILES['upload']) {
    $mes = 'Upload Complete';
    move_uploaded_file($file['tmp_name'],$file['name']);
    $name = $file['name'];
    shell_exec('chmod o+r '.$file['name']);
    $db = new SQLiteDatabase('db', 0600, &$err);
    $q = "insert into queue values('{$file['name']}', NULL, datetime('now'))";
    $db->queryExec($q);
?>
<script>
  window.parent.window.newImage('<?=$name?>');
</script>  
<?
  }
?>
<form id="upload" enctype="multipart/form-data" action="upload" method="POST">
	<input name="pass" type="password" value="<?=$_POST['pass']?>"/>
	<input name="upload" type="file"/>
  <input type="submit" value="Upload"/><br/>
</form>

