<?php

$x=strval(12.34e+04); //1234004333
$h=strval(4333);
$finde="043";
$source=$x.$h;
$y=find_string($source,$finde);

$q=put_string($y, "\n");
$q=put_string(12.34e04);