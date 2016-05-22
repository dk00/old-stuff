<?
header('Content-type: image/bmp');
$n0 = 640;
$n1 = 128;
$h = pack('a2Lx4LIIISSIIIIII', 
    'BM', $n0*$n1*3+54, 0, 0x28, $n0, -$n1, 1, 24, 0, $n0*$n1*3, 8192, 8192, 0, 0);
print $h;
$f = fopen('candy.raw', 'rb');
while ($tmp = fread($f, 8192)) {
  for ($i = 0; $i < 8192; ++$i) {
    $px = ord($tmp[$i]);
    print pack('C3', $px, $px, $px);
  }
}


?>
