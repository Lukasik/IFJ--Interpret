<?php

$z = a(2);
$z = put_string("\n", $z);

function a($x)
{
	if($x === 512)
	{
		return 1;
	}
	else
	{
		$z = put_string("\n", $x);
		$x = $x *2;
	}
	$x = a($x);

	return $x;
}