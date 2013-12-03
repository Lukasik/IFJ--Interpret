<?php

// strval

function f()
{}

$x=f(2,3);
$null=strval($x);


function soucin($x,$y)
{
	return $x*$y;
}

function cmp($x,$y)
{
	return $x===$y;
}

$x=cmp("aaa",1);
$boolnic=strval($x);

$x=soucin(7,2);
$int14=strval($x);


$q=0-11;
$q2=0-0.5;
$x=soucin($q,$q2);
$double=strval ($x);


$x="a"."b";
$str=strval($x);

$x=put_string($null,$boolnic,$int14,"\n",$double,"\n",$str);


// null ""   boolnic ""   int14  "14"  double 5.5  str "ab"



