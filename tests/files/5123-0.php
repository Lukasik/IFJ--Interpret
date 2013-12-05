<?php
$str="ahojMartine";

// fibonachi

function secti($x,$y)
{
  return $x + $y;
}

$pocet=2;
$q=put_string(1," ",1);
$a=1;
$b=1;
$c=1;


while ($pocet < 10)
{
  $c=secti($a,$b,10); // 10 jen navic schvalne
  $q=put_string(" ",$c);
  $a=$b;
  $b=$c;

  $pocet=$pocet+1;
}

