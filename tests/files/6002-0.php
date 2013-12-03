<?php
$x = 1;
$str = "string\n";
while($str)
{
	if($x === 11)
	{
		$str = "";
	}
	else
	{
		$e = put_string($str);
	}
	$x = $x + 1;
}
