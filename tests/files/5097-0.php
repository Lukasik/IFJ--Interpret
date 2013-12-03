<?php

$a="klmn";
$b="mnop";
$c="abcd";
$d="cdef";
$e=1234;

$sour=$a.$c.$b.$e.$d;

$out=sort_string($sour);
$y=put_string($out);
