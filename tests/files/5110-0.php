<?php

// test pro intval

$y=11;
$z="ab";
$x=null;
$null0=intval($x,$y,$z);

$x=cmp(4,5);
$bool0=intval($x,$y,$z);


function cmp($a,$b)
{
	return $a>$b;
}

$q=1-10;
$x=cmp(5,$q);
$bool1=intval($x,$y,$z);


$q=0-10;
$x=10+$q;
$int0=intval($x,$y,$z);

$x=$q+100;
$int90=intval($x,$y,$z);

$x=$q/20;
$double0=intval($x,$y,$z);

$x=$q/4;
$doubleminusdva=intval($x,$y,$z);

$x="12"."00b";
$str1200=intval($x,$y,$z);

$x="1". 234;
$str1234=intval($x,$y,$z);

$x="abeceda". 234;
$str0=intval($x,$y,$z);

$x=put_string($null0,$bool0,$bool1,$int0,$int90,$double0,$doubleminusdva,$str1200,$str1234,$str0);

// vraci null0,bool0,bool1,int0,int90,double0,doubleminusdva,str1200,str1234,str0,



