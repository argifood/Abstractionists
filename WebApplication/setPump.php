<?php
require('db.php');

$pinNumber = $_GET["pinNumber"];
$inOperation = $_GET["inOperation"];

if(!isset($pinNumber) || trim($pinNumber) == ""){
	return;
}
if(!isset($inOperation) || trim($inOperation) == ""){
	return;
}

$sql = $conn->prepare("REPLACE INTO PUMPS (PIN_NUMBER, IN_OPERATION) VALUES (?,?)");
$sql->bind_param("is", $pinNumber, $inOperation);
$sql->execute();

$sql->close();
$conn->close();
