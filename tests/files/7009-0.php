<?php

function a($x)
{
	$x = b($x);
	return $x;
}

function b($x)
{
	$x = c($x);
	return $x;
}

function c($x)
{
	while($x)
	{
		$x = $x - 1;
		$z = put_string($x);
	}

	return 42;
}

$x = a(9);
$z = put_string($x);

$x = c(9);
