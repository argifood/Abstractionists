<?php
require('db.php');

$key = $_GET["key"];
$value = $_GET["value"];

if(!isset($key) || trim($key) == ""){
	return;
}
if(!isset($value) || trim($value) == ""){
	return;
}

$sql = $conn->prepare("REPLACE INTO USER_SETTINGS (MY_KEY, VALUE) VALUES (?,?)");
$sql->bind_param("ss", $key, $value);
$sql->execute();

$sql->close();
$conn->close();