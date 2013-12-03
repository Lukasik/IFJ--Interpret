<?php

$a="klmn";
$b="mnop";
$c="abcd";
$d="cdef";

$sour=$a.$b.$c.$d.1234;

$out=sort_string($sour);
$y=put_string($out);
