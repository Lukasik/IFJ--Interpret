<?php

// test pro boolval

$x=0-100;

$inttrue=boolval($x);


$x=100*2-200;
$intfalse=boolval($x);


$x=100/29;
$doubletrue=boolval($x);


$x=100/100 - 1;
$doublefalse=boolval($x);

$x=null;
$null=boolval($x);

$x="a". 1234;
$strtrue=boolval($x);

$x="";
$strfalse=boolval($x);

$x=put_string($inttrue,"\n",$intfalse,"\n",$doubletrue,"\n",$doublefalse,"\n",$null,"\n",$strtrue,"\n",$strfalse,"\n");
$x=put_string($x);

// vraci true false true false false true false 14