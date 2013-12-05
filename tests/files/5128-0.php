<?php

$i = 2;
while ($i<30)
{
	$is=isPrvocislo($i);
	// $is = true;
	if ($is===true)
	{
		$q=put_string($i,"\n");
	}
	else
	{}
	$i=$i+1;
}

function isPrvocislo($x)
{
	$i=2.0;
	$neniprvocislo=false;
	while ($i < ($x/2))
	{
		$pom=$x/$i;
		$pom2=intval($pom);
		$modulo= $pom - $pom2 === 0.0;
		if ($modulo)
		{
			$neniprvocislo=true;
		}
		else{}	
			$i=$i+1;
	}
	
	return $neniprvocislo === false;
}



