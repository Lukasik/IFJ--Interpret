<?php
$x = 1;
$y = 6;
while ($x - $y)
{
	$x = $x + 1;
	if($x > 0)
	{
		$e = put_string($x);
		if($x > 2)
		{
			$e = put_string($x);
			if($x > 4)
			{
				$e = put_string($x);
			}
			else
			{
				$e = put_string($x);
			}
		}
		else
		{
			$e = put_string($x);
		}
	}
	else
	{
		$e = put_string($x);
	}
}
