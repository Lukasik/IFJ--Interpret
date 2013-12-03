<?php

// doubleval

function f()
{}

$x=f(2,3,4,5);

$null=doubleval($x);

function getbool($x,$y)
{
	$z=cmp($x,$y,3);
	return $z;
}

// false
$x=getbool("ahoj","martine");
$bool0=doubleval($x);
$x=getbool("jsempica","alecouz");
$bool1=doubleval($x);

function cmp($x,$y)
{
	return $x > $y;
}


$pom=getbool("aaa","bbb");
$x=intval($pom);
$int0=doubleval($x);

$pom=getbool("baba","bab");
$x=intval($pom);
$int1=intval($x);

$x=0-0.125;
$double=doubleval($x);

$x="12".".2";
$str0=doubleval($x);

$x="1.5e+". 2;
$str1=doubleval($x);

$x="1". 2 . "." . "5";
$str2=doubleval($x);

// 1.2E-3
$x="\x31\x2E\x32\x45\x2B\x33";
$str3=doubleval($x);

$x=put_string($null," ",$bool0," ",$bool1," ",$int0," ",$int1," ",$double," ",$str0," ",$str1," ",$str2," ",$str3);


// null 0.0    bool0 0.0     bool1 1.0    int0 0.0    int1 1.0  double -0.125
// str0 12.2    str1 1.5e+2    str2 12.5 str3 1.2E-3


// function put_string()
// {
// 	$x = func_get_args();

// 	foreach($x as $imte)
// 	printf($imte);
// }