<?php


function neni10()
{
	$q=get_string();
	$convert=doubleval($q);
	return ($convert!==10.0);
}


$res=neni10();
while ($res)
{
	$q=put_string($res,"\n");
	$res=neni10();
}
$q=put_string("konec vole");