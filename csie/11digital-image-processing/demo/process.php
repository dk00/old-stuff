<?
  $db = new SQLiteDatabase('db', 0600, &$err);
  $q = "insert into queue values('{$file['name']}', NULL, datetime('now'))";
  $db->queryExec($q);
?>
<form id="upload" enctype="multipart/form-data" action="." method="POST" onsubmit="return upload()">
	<input name="pass" type="password" />
 	<input name="upload" type="file"/>
  <input type="submit" value="Upload"/><br/>
 </form>
 Upload complete
