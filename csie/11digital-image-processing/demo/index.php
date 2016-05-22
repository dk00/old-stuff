<?
  $arg = explode('/', key($_GET));
  // TODO: fix the dirty code
  if ($arg[0] == 'show') {
    require_once 'show.php';
  }
  else if($arg[0] == 'all') {
    $db = new SQLiteDatabase('db', 0600, &$err);
    $q = "select * from queue order by next desc";
    $g = $db->arrayQuery($q, SQLITE_ASSOC);
    foreach ($g as $img) {?>
	  <img src="<?=$img['file']?>"/>
	  <img src="r_<?=$img['file']?>"/>
  <?} 
  }
  else if ($arg[0] == 'get') {
    $wait = intval($_POST['wait']);    
    usleep($wait);
    $file = $_POST['file'];
    $db = new SQLiteDatabase('db', 0600, &$err);
    $q = "select res from queue where file = '$file'";
    print $db->singleQuery($q, SQLITE_ASSOC);
  }
  else if ($arg[0] == 'done') {
    $db = new SQLiteDatabase('db', 0600, &$err);
    $file = $_POST['file'];
    $res = $_POST['res'];
    $q = "update queue set res = '$res' where file = '$file'";
    print $q;
    $db->queryExec($q);
  }
  else if ($arg[0] == 'fetch') {
    $db = new SQLiteDatabase('db', 0600, &$err);
    //$db->queryExec('begin transaction');
    $q = "select * from queue where res ISNULL and next < datetime('now')";
    $name = $db->singleQuery($q);
    if (is_array($name)) $name = $name[0];
    $q = "update queue set next = datetime('now', '+5 seconds') where file = '$name'";
    $db->queryExec($q);
    print $name;
    //$db->queryExec('commit transaction');
  }
  else if ($arg[0] == 'sql') require_once 'sqlcmd.php';
  else if ($arg[0] == 'upload') {
    require_once 'upload.php';
  }
  if ($arg[0]) exit;
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
	<meta http-equiv="imagetoolbar" content="no" />
	<title>DIP | Demonstration</title>
	<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4/jquery.min.js"></script>
<!--	<script type="text/javascript" src="./fancybox/jquery.mousewheel-3.0.4.pack.js"></script>-->
	<script type="text/javascript" src="./fancybox/jquery.fancybox-1.3.4.pack.js"></script>
	<link rel="stylesheet" type="text/css" href="./fancybox/jquery.fancybox-1.3.4.css" media="screen" />
 	<link rel="stylesheet" href="style.css" />
	<script type="text/javascript">
    var pdata = {};
		$(document).ready(function() {
      $("a[rel=main]").each(setup);
		});
    function setup() {
      $(this).fancybox({
        ajax: {type: 'POST', data: {file: $(this).attr('data')}},
        onComplete      : resize,
        scrolling       : 'no',
				'titleFormat'   : function(title, currentArray, currentIndex, currentOpts) {
					return '<span id="fancybox-title-over">Image ' + (currentIndex + 1) + ' / ' + currentArray.length + (title.length ? ' &nbsp; ' + title : '') + '</span>';
				}
      });
    }
    window.newImage = 
    function(src) {
      $('#info').text('' + src + ' uploaded');
      ni = $('<a href="show" data="'+src+'" rel="main"><img src="'+src+'"/></a>');
      ni.prependTo($('#gallery')).hide().slideDown('slow');
      setup.apply(ni);
    };
    function resize() {
      $('#fancybox-content img').each(zoomimg);
    }
    function zoomimg() {
      w = $(this).width();
      nw = $('#fancybox-content').width() - 2;
      $('#debug').text(''+nw+' '+w);
      h = $(this).height();
      $(this).width(nw);
      $(this).height(h*nw/w);
    }
	</script>
</head>
<body>
<div id="content">
	<h1>DIP Final Project <span> team 20</span></h1>
	<p>
	</p>
  <iframe src="upload"></iframe>
	<hr />
	<p>
	Image Gallery <br />
  <div id="gallery">
<?
  $db = new SQLiteDatabase('db', 0600, &$err);
  $q = "select * from queue order by next desc";
  $g = $db->arrayQuery($q, SQLITE_ASSOC);
  foreach ($g as $img) {?>
  <a href="show" data="<?=$img['file']?>" rel="main"><img src="t_<?=$img['file']?>"/></a>
<?} ?>
	</p>
  </div>
</div>
</body>
</html>

