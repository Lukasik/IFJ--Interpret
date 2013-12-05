<?php


$q=put_string("zadej obsah promenne \"\$what\"\n");
$what=get_string();

$what=strval($what); // nemelo by nic zmenit
$int=intval($what);

if ($int<2)
{
	$q=put_string("\twhat neni prvocislo\x31\x31");
}
else
{
	$result=isPrvocislo($int);
	if ($result)
	{
		$q=put_string("\twhat je prvocislo\x31\x31");
	}
	else 
	{
		$q=put_string("\twhat neni prvocislo\x31\x31");
	}
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



// function put_string($x)
// {
// 	printf($x);
// }