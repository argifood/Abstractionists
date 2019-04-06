<!DOCTYPE html>
<html>
<head>
	<title>Irigator</title>
	<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.8.1/css/all.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css">
	<style type="text/css">
		body {
 		background-image: url('https://cdn.pixabay.com/photo/2018/05/15/09/23/raindrop-3402550_960_720.jpg');
 		background-color: #cccccc;
 		background-repeat:no-repeat!important;
 		background-size: cover!important;
	}

		.container{
			margin-top:144px;
		}

		.row{

		}

		.col-sm:not(:first-child){
			margin-left: 15px;
			color:blue;
		}

	   h1{
	   	text-align: center;
	   	border: 1px solid black;
	   	border-radius: 25px;
  		background: #73AD21;
  		width:80%;
  		margin-top: 15px;
  		margin-left: 144px;
	   }

		 #footer{
			 margin-top:144px;
		 }


		 #weatherform{
			 position:relative!important;
		 }
		 .autocomplete {
  /*the container must be positioned relative:*/
  position: relative;
  display: inline-block;
}
input {
  border: 1px solid transparent;
  background-color: #f1f1f1;
  font-size: 12px;
}
input[type=text] {
  background-color: #f1f1f1;
}
input[type=button] {
  background-color: DodgerBlue;
  color: #fff;
}
.autocomplete-items {
  position: absolute;
  border: 1px solid #d4d4d4;
  border-bottom: none;
  border-top: none;
  z-index: 99;
  /*position the autocomplete items to be the same width as the container:*/
  /* top: 100%;
  left: 0;
  right: 0; */
	left:150px;
}
.autocomplete-items div {

  cursor: pointer;
  background-color: #fff; 
  border-bottom: 1px solid #d4d4d4; 
}
.autocomplete-items div:hover {
  /*when hovering an item:*/
  background-color: #e9e9e9; 
}
.autocomplete-active {
  /*when navigating through the items using the arrow keys:*/
  background-color: DodgerBlue !important; 
  color: #ffffff; 
}

	</style>
</head>
<body>
	<h1>The first IoT solution applied in irrigation systems</h1>
	<form id="weatherForm" onsubmit="return false;" action="" autocomplete="off">
	<div class="autocomplete" style="width:300px;">
	Επιλέξτε περιοχή: <input type="text" name="city" id="searchTextInput">&nbsp
		</div>
  <input id="weatherButton" type="button" value="Πάμε!">
</form>
<div id="openweathermap-widget-11"></div>
	<div class="container">
  <div class="row">
    <div class="col-sm">
      One of three columns
    </div>
    <div class="col-sm">
      One of three columns
    </div>
    <div class="col-sm">
    	One of three columns
      <!-- db.php connection with database in a variable -->
      <!-- include db.php, mysqli, pdo -->
    </div>
  </div>
</div>
<?php include 'weather.php';?>
<?php include 'footer.php';?>
</body>
<script>
	var locationsJson = <?php echo $strJsonFileContents; ?>;
	var cities = [];
	var citiesDictionary = {};
	var weatherInfo;
	for(let i = 0; i < locationsJson.length; i++){
		cities.push(locationsJson[i].name);
		citiesDictionary[locationsJson[i].name] = locationsJson[i].id;
	}
	locationsJson = "";
	document.getElementById("weatherForm").addEventListener("keypress", function () {
		let searchText = document.getElementById("searchTextInput");
			autocomplete(searchText, cities);
	});

	function autocomplete(inp, arr) {
  /*the autocomplete function takes two arguments,
  the text field element and an array of possible autocompleted values:*/
	var currentFocus;
  /*execute a function when someone writes in the text field:*/
  inp.addEventListener("input", function(e) {
		if(inp.value.length < 2){
				closeAllLists();
				return false;
			}	
		var a, b, i, val = this.value;
      /*close any already open lists of autocompleted values*/
			closeAllLists();
      if (!val) { return false;}
      currentFocus = -1;
      /*create a DIV element that will contain the items (values):*/
      a = document.createElement("DIV");
      a.setAttribute("id", this.id + "autocomplete-list");
      a.setAttribute("class", "autocomplete-items");
      /*append the DIV element as a child of the autocomplete container:*/
      this.parentNode.appendChild(a);
      /*for each item in the array...*/
      for (i = 0; i < arr.length; i++) {
        /*check if the item starts with the same letters as the text field value:*/
        if (arr[i].substr(0, val.length).toUpperCase() == val.toUpperCase()) {
          /*create a DIV element for each matching element:*/
          b = document.createElement("DIV");
          /*make the matching letters bold:*/
          b.innerHTML = "<strong>" + arr[i].substr(0, val.length) + "</strong>";
          b.innerHTML += arr[i].substr(val.length);
          /*insert a input field that will hold the current array item's value:*/
          b.innerHTML += "<input type='hidden' value='" + arr[i] + "'>";
          /*execute a function when someone clicks on the item value (DIV element):*/
              b.addEventListener("click", function(e) {
              /*insert the value for the autocomplete text field:*/
              inp.value = this.getElementsByTagName("input")[0].value;
              /*close the list of autocompleted values,
              (or any other open lists of autocompleted values:*/
              closeAllLists();
          });
          a.appendChild(b);
        }
      }
  });
  /*execute a function presses a key on the keyboard:*/
  inp.addEventListener("keydown", function(e) {
      var x = document.getElementById(this.id + "autocomplete-list");
      if (x) x = x.getElementsByTagName("div");
      if (e.keyCode == 40) {
        /*If the arrow DOWN key is pressed,
        increase the currentFocus variable:*/
        currentFocus++;
        /*and and make the current item more visible:*/
        addActive(x);
      } else if (e.keyCode == 38) { //up
        /*If the arrow UP key is pressed,
        decrease the currentFocus variable:*/
        currentFocus--;
        /*and and make the current item more visible:*/
        addActive(x);
      } else if (e.keyCode == 13) {
        /*If the ENTER key is pressed, prevent the form from being submitted,*/
        e.preventDefault();
        if (currentFocus > -1) {
          /*and simulate a click on the "active" item:*/
          if (x) x[currentFocus].click();
        }
      }
  });
  function addActive(x) {
    /*a function to classify an item as "active":*/
    if (!x) return false;
    /*start by removing the "active" class on all items:*/
    removeActive(x);
    if (currentFocus >= x.length) currentFocus = 0;
    if (currentFocus < 0) currentFocus = (x.length - 1);
    /*add class "autocomplete-active":*/
    x[currentFocus].classList.add("autocomplete-active");
  }
  function removeActive(x) {
    /*a function to remove the "active" class from all autocomplete items:*/
    for (var i = 0; i < x.length; i++) {
      x[i].classList.remove("autocomplete-active");
    }
	}
	
  function closeAllLists(elmnt) {
    /*close all autocomplete lists in the document,
    except the one passed as an argument:*/
    var x = document.getElementsByClassName("autocomplete-items");
    for (var i = 0; i < x.length; i++) {
      if (elmnt != x[i] && elmnt != inp) {
      x[i].parentNode.removeChild(x[i]);
    }
  }
}

/*execute a function when someone clicks in the document:*/
document.addEventListener("click", function (e) {
    closeAllLists(e.target);
});

document.getElementById("weatherButton").addEventListener("click", function (e) {
		let cityText = document.getElementById("searchTextInput").value;
		var xhr = new XMLHttpRequest();
  	var url = 'http://api.openweathermap.org/data/2.5/weather?id='+citiesDictionary[cityText]+'&appid=d9490b08bfb539f6146dbd58649fc797';
  	xhr.open('GET', url, true);
  	xhr.onreadystatechange = function(){
    if(xhr.readyState == 4 && xhr.status == 200){
      weatherInfo = xhr.responseText;
    }
  };
  xhr.send();
});


}
</script>
</html>