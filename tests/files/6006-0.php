<?php
$x = 100;
$y = 6;
while ($x - $y > 10)
{
	$x = $x - 1;
	if($x > 50)
	{
		$e = put_string($x);
		if($x > 25)
		{
			$e = put_string($x);
			if($x > 40)
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
		if($x < 20)
		{
			$e = put_string($x);
			if($x < 74)
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
}
