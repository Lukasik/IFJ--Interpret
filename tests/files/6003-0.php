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
		$str = $str . $x;
		$e = put_string($str);
	}
	$x = $x + 1;
}
