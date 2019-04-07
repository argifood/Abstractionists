<?php
require('db.php');

$query = "SELECT * FROM PUMPS";

$msg = "";

if ($result = $conn->query($query)) {

    /* fetch associative array */
    while ($row = $result->fetch_assoc()) {
		$msg = $msg.$row["PIN_NUMBER"]."-".$row["IN_OPERATION"].",";
    }

    /* free result set */
    $result->free();
	$msg = rtrim($msg,',');
	echo $msg;
}
