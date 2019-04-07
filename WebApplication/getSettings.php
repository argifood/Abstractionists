<?php
require('db.php');

$query = "SELECT * FROM USER_SETTINGS";

$msg = "";

if ($result = $conn->query($query)) {

    /* fetch associative array */
	$msg = [];
    while ($row = $result->fetch_assoc()) {
		$msg[$row["MY_KEY"]] = $row["VALUE"];
    }

    /* free result set */
    $result->free();
	
	echo JSON_ENCODE($msg);
}