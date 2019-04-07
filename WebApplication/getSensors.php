<?php
require('db.php');

$query = "SELECT * FROM SENSORS";

$msg = "";

if ($result = $conn->query($query)) {

    /* fetch associative array */
	$msg = [];
	$counter = 0;
    while ($row = $result->fetch_assoc()) {
		$msg[$counter] = [];
		$msg[$counter]["PIN_NUMBER"] = $row["PIN_NUMBER"];
		$msg[$counter]["SOIL_HUMIDITY"] = $row["SOIL_HUMIDITY"];
		$msg[$counter]["SOIL_PH"] = $row["SOIL_PH"];
		$msg[$counter]["SOIL_TEMPERATURE"] = $row["SOIL_TEMPERATURE"];
		$counter++;
    }

    /* free result set */
    $result->free();
	
	echo JSON_ENCODE($msg);
}