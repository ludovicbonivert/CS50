<?php 
	// configuration
    require("../includes/config.php"); 
    // if form was submitted
    if($_SERVER["REQUEST_METHOD"] == "POST"){
    	$stock = lookup($_POST["symbol"]);
    	if($stock === false){
    		apologize("There seems to be an error with the stock you entered ! ");
    	}else{
    		// the user has entered a correct symbol
    		// we now need to check his cashflow against the number of shares he wants to buy
    		$numberOfShares = $_POST["shares"];
    		// We need to retrieve the users cash

    		$usercash = query("SELECT cash FROM users WHERE	 id = ?", $_SESSION["id"]);
			$cash = '';
			foreach ($usercash as $user){
				$cash = $user["cash"];
			}

    		// numberOfShares * price of 1 share
    		$totalprice = $numberOfShares * $stock["price"];
    		if($cash < $totalprice){
    			apologize("You don't have sufficient cash flow ! Try selling some");
    		}else{
				query("UPDATE users SET cash = cash - ? WHERE id = ?", $totalprice,  $_SESSION["id"]);
				$newShares = query("INSERT INTO stocks(id, symbol, shares) VALUES (?,?,?)", $_SESSION["id"], $stock["symbol"], $numberOfShares);
				
				if($newShares === false){
					// That symbol already exists so we need to update it
					query("UPDATE stocks SET shares = shares + ? WHERE id = ?", $numberOfShares, $_SESSION["id"]);
				}
                query("INSERT INTO history(operation, amountofshares, priceofshare, symbol, id) VALUES(1, ?, ?, ?, ?)", $numberOfShares, $stock["price"], $stock["symbol"], $_SESSION["id"]);
				redirect("/");
    		}
    	}
    }
    
    // render portfolio
    render("buy_form.php", ["title" => "Portfolio"]);
?>