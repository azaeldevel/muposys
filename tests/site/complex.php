<?php

if(isset($_POST["counter"])) 
{
	$number = $_POST["counter"];
	$a = $number * $number;
	$b = sqrt($number);
	$c = ($a + $b)/2;
	
	echo $c;
}
else
{
	echo "#"
}

?>
