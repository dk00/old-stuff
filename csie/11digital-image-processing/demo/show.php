<?
  $file = $_POST['file'];
  if (!isset($file))
    $file = 'testa.jpg';
  $db = new SQLiteDatabase('db', 0600, &$err);
  $q = "select res from queue where file = '$file'";
  $r = $db->singleQuery($q, SQLITE_ASSOC);
  $size = getimagesize($file);
  $width = $size[0];
?>
<style>
  .imgbox {
    display: inline-block;
    text-align: center;
    margin-left: 2px;
  }
  .outer {
    border: 0;
    margin: 0;
    padding: 0;
    width: <?=$width?>px;
  }
  .imgbox img {
    width: auto;
  }
</style>
<div class="outer" >
  <div class="imgbox">
    Original <br />
    <img id="ori" src="<?=$file?>"/>
  </div>
  <br/>
  <div class="imgbox">
<?if ($r) {?>
    Processed <br />
    <img id="result" src="<?=$r?>"/>
<?} else {?>
    <span id="msg">Loading...</span> <br />
    <img id="result" src="<?=$file?>" style="visibility: hidden"/>
<?}?>
  </div>
</div>
<script>
<?if (!$r) {?>
var count = 0;
function show(l) {
  if (l != '') {
    $('#msg').text('Processed');
    $('#result').attr('src', l);
    $('#result').css({visibility: 'visible'});
  }
  else get();
}
var wait = 0;
function get() {
  $.post('get', {'file': '<?=$file?>', 'wait': wait}, show);
  wait = 1000000;
}
get();
<?}?>
</script>

