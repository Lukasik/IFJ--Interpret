<?php

// test pro boolval

$x=1>0;
$t=boolval($x);

$x=1>=2;
$f=boolval($x);

$x=put_string($t,"\n",$f,"\n");
$x=put_string($x);

// true false 2