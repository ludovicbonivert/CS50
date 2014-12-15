<?php
	// configuration
	require("../includes/config.php");
	// if form was submitted
	if($_SERVER["REQUEST_METHOD"] == "POST"){
		$stock = lookup($_POST["symbol"]);
		// likewhise $stock wil not be false, but empty or another error
		if($stock === false){
			apologize("There seems to be an error with the stock you entered ! ");
		}else{
			// lookup returned an associative array of symbol, name and price
			// problem is at the moment that it is printed on another page :/
			//redirect("/");
			// that isnt showed at the moment
			render("quote_form.php", ["title" => "Looking up a quote", "stock" => $stock]);
		}
	}else{
		render("quote_form.php", ["title" => "Looking up a quote"]);
	}
?>
