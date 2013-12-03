<?php
$w = intval("\x31\x32\x33");
$x = boolval("\x31\x32\x33");
$y = doubleval("\x31\x32\x33");
$z = strval("\x31\x32\x33");

if($w > 100) {
	$e = put_string("ano\n");
}
else {
	$e = put_string("ne\n");
}

if($x) {
	$e = put_string("ano\n");
}
else {
	$e = put_string("ne\n");
}

if($y < 100.0) {
	$e = put_string("ne\n");
}
else {
	$e = put_string("ano\n");
}

if($z) {
	$e = put_string("ano\n");
}
else {
	$e = put_string("ne\n");
}
