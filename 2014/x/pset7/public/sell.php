<?php 

	/* 
	For selling we need a few things
	First we need to make a list of every stocks the id has 
	If the user submit, we need to do our delete and update queries
	*/



    // configuration
	require("../includes/config.php");
	// if form was submitted
	if($_SERVER["REQUEST_METHOD"] == "POST"){

		
		// we need to find the exact amount that has been earned and update the users cash
		$stock = lookup($_POST["symbol"]);
		$user = query("SELECT cash, shares from stocks JOIN users WHERE users.id = ? AND stocks.id = ?", $_SESSION["id"], $_SESSION["id"]);
		

		$totalcash = $user[0]["cash"] + $stock["price"] * $user[0]["shares"];
		
		query("UPDATE users SET cash = ? WHERE id = ?", $totalcash ,$_SESSION["id"]);
		query("INSERT INTO history(operation, amountofshares, priceofshare, symbol, id) VALUES(0, ?, ?, ?, ?)", $user[0]["shares"], $stock["price"], $stock["symbol"], $_SESSION["id"]);
		query("DELETE FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
		redirect("/");
		
	}else{
		render("sell_form.php", ["title" => "Selling"]);
	}



?>