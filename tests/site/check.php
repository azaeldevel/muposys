<?php

if(isset($_POST["counter"])) 
{
	$number = $_POST["counter"];
	$number++;
	echo $number;
}
else
{
	echo "#"
}

?>