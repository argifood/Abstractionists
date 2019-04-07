<?php
require('db.php');

$pinNumber = $_GET["pinNumber"];
$soilHumidity = $_GET["soilHumidity"];
$soilPH = $_GET["soilPH"];
$soilTemperature = $_GET["soilTemperature"];

if(!isset($pinNumber) || trim($pinNumber) == ""){
	return;
}
if(!isset($soilHumidity) || trim($soilHumidity) == ""){
	return;
}
if(!isset($soilPH) || trim($soilPH) == ""){
	return;
}
if(!isset($soilTemperature) || trim($soilTemperature) == ""){
	return;
}

$sql = $conn->prepare("REPLACE INTO SENSORS (PIN_NUMBER, SOIL_HUMIDITY, SOIL_PH, SOIL_TEMPERATURE) VALUES (?,?,?,?)");
$sql->bind_param("isss", $pinNumber, $soilHumidity, $soilPH, $soilTemperature);
$sql->execute();

$sql->close();
$conn->close();