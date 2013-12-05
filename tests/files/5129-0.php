<?php

function f1 ($a,$b)
{
	return $a+$b;
}

function f2 ($a,$b)
{
  $x=f1($a,$b);
  return $x;
}

function f3 ($a,$b)
{
	$x=f2($a,$b);
	return $x;
}

$a=5;
$b=5;
$x=0;
while ($x<1000)
{
	$x=f3($a,$b);
	$a=$x;
	$b=$x;
	$q=put_string($x,"\n");
}




