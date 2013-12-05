<?php
$str="ahojMartine";

//a
$a=get_substring($str,0,1);
$y=put_string($a,"\n");

//hoj
$b=get_substring($str,1,4);
$y=put_string($b,"\n");

$strlenstr=strlen($str);
$c=get_substring($str,0,$strlenstr);
$y=put_string($c,"\n");


$str2="12345". 6789;
$d=get_substring($str2,1,9);
$y=put_string($d,"\n");

// enter $ enter \\ tab $ tab
$str3="\n\$\n\\\\\t\$\t";
$e=get_substring($str3,0,3);
$y=put_string($e);

$f=get_substring($str3,0,4);
$y=put_string($f);


$delka=strlen($str3);
$y=put_string($delka);


