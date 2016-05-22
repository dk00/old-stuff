<?
if (!isset($_POST['pw']) || !isset($_POST['cmd'])) {
?>
<link rel="stylesheet" type="text/css" href="../tmp.css"/>
<form id="data" onsubmit="send(this); return false;">
  <input id="pw" type="password"/>
  <br/>
  <textarea rows="8" cols="80" id="cmd"></textarea>
  <br/>
  <input type="submit" value="Send"/>
</form>
<div id="result">
</div>
<script src="http://code.jquery.com/jquery-1.4.3.min.js"></script>
<script>
function send(o) {
  data = {
    'pw': $('#pw').attr('value'),
    'cmd': $('#cmd').attr('value')
  };
  $('#result').text('Loading');
  $.post('sqlcmd', data, function(res){    
    tmp = $('#result');
    tmp.text('');
    res = res.split('\n');
    tmp.append($('<pre></pre>').text(res[0]));
    t = $('<table></table>');
    tmp.append(t);
    for (i = 1; i+1 < res.length; ++i) {
      c = res[i].split('\t');
      r = $('<tr></tr>');
      t.append(r);
      for (j = 0; j+1 < c.length; ++j)
        r.append($('<td></td>').text(c[j]));
    }
  });
}
</script>
<?
  exit;
}
$pw = $_POST['pw'];
if (md5('dk'.$pw) != 'e3333c605c8283013ba6ee149c833d3f')
  exit;
print $q = $_POST['cmd'];
print "\n";
$db = new SQLiteDatabase('db', 0600, $err) or exit($err);
$res = $db->arrayQuery($q, SQLITE_ASSOC);
if (!isset($res[0])) exit;
foreach ($res[0] as $col => $dat)
  print $col."\t";
print "\n";
foreach ($res as $r) {
  foreach ($r as $dat)
    print $dat."\t";
  print "\n";
}
?>
