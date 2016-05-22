<link href="http://s000015.googlepages.com/vcprob.css" rel="stylesheet">

<title><?php echo htmlspecialchars($_POST['title'])?></title>

<div class="Title"><?php echo htmlspecialchars($_POST['title'])?></div>

<div class="Info"><?php echo $_POST['info']?></div>

<?php echo $_POST['dsc']?>

<div class="Title1">Input</div>

<?php echo $_POST['input']?>

<div class="Title1">Output</div>

<?php echo $_POST['output']?>

<table border="0" width="100%">
<tbody><tr>
  <td class="Title2" width="50%">Sample Input</td>
  <td class="Title2" width="50%">Sample Output</td></tr>
  <tr valign="top"><td>
    <pre class=SampleIO><?php echo htmlspecialchars($_POST['in'])?></pre>
  </td><td>
    <pre class=SampleIO><?php echo htmlspecialchars($_POST['out'])?></pre>
  </td></tr>
</tbody></table>
