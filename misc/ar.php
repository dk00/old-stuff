<?
$N=99,$M=99,$L=1,$n=$_REQUEST['n'],$m=$_REQUEST['m'],$t=0;
$c1=array(),$c2=array(),$c3=array(),$s=array();
void print()
{
    global $m,$t,$s;
    for($i=1;$i<=$m;$i++)
    {
        for($j=1;$j<=$t;$j++)
            if($s[$i][$j][0])
                echo ('A'+$s[$i][$j][0]-1).('A'+$s[$i][$j][1]-1).' ';
            else
                echo '-- ';
        echo '\n';
    }
}
int go($i,$j)
{
    global $n,$m,$t,$c1,$c2,$c3,$s;
    if($i>$n)return 1;
    if($j>$m)return go($i+1,1);
    if(!$c2[$i][$j])return go($i,$j+1);
    $c2[$i][$j]--;
    for($k=1;$k<=$n;$k++)
    {
        if($k==$i || !$c1[$i][$k] || !$c2[$k][$j])continue;
        for($l=1;$l<=$t;$l++)
            if($c3[$i][$l] && $c3[$k][$l] && !$s[$j][$l][0])break;
        if($l>$t)continue;
        $c1[$i][$k]--;
        $c3[$i][$l]--;
        $c1[$k][$i]--;
        $c2[$k][$j]--;
        $c3[$k][$l]--;
        $s[$j][$l][0]=$i;
        $s[$j][$l][1]=$k;
        if(go($i,$j+1))return 1;
        $s[$j][$l][0]=0;
        $s[$j][$l][1]=0;
        $c1[$i][$k]++;
        $c3[$i][$l]++;
        $c1[$k][$i]++;
        $c2[$k][$j]++;
        $c3[$k][$l]++;
    }
    $c2[$i][$j]++;
    return 0;
}
for($i=0;$i<=n;$i++)
{
    $c1[$i]=array();
    $c2[$i]=array();
    $c3[$i]=array();
    for($j=0;$j<=n+m;$j++)
        $s[$i][$j]=array();
}
for($i=1;$i<=$n;$i++)
    for($j=1;$j<=$n;$j++)
        $c1[$i][$j]=$L;
for($i=1;$i<=$n;$i++)
    for($j=1;$j<=$m;$j++)
        $c2[$i][$j]=1;
for($i=1;$i<=$n;$i++)
    for($j=1;$j<=$N+$M;$j++)
        $c3[$i][$j]=1;
for($i=1;$i<=$m;$i++)
    for($j=1;$j<=$N+$M;$j++)
        $s[$i][$j][0]=s[$i][$j][1]=0;
for($t=$m;!go(1,1);$t++);
print();
?>
