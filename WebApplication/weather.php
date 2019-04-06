<?php

// Get the contents of the JSON file 
$strJsonFileContents = file_get_contents("locations.json");

$array = json_decode($strJsonFileContents, true);

?>