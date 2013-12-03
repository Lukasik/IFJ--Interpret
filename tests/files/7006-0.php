<?php

$a = 0-1000;
$z = a($a);
$z = put_string($z);

function a($x)
{
	$x = $x-1;
	$x = b($x);
	return $x;
}

function b($x)
{
	$x = $x+2;
	if($x < 100)
	{
		$x = a($x);
	}
	else
		{
		}

	return $x;
}