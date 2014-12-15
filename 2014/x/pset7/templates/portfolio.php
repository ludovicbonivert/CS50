
<ul class="nav nav-pills">
	<li><a href="quote.php">Quote</a></li>
	<li><a href="buy.php">Buy</a></li>
	<li><a href="sell.php">Sell</a></li>
	<li><a href="history.php">History</a></li>
	<li><a href="logout.php">Log Out</a></li>
</ul>

<div>
	<table class="table table-striped">
		<thead>
			<tr>
				<th>Symbol</th>
				<th>Name</th>
				<th>Shares</th>
				<th>Price</th>
				<th>Total</th>
			</tr>
		</thead>
		<tbody>
		<?php

		// Retrieve users stocks with a php query
		// Lookup users stocks ? 
			// session id comes from the portfolio.php page
			$rows = query("SELECT symbol, shares FROM stocks WHERE id = ? ", $_SESSION["id"]);

			foreach ($rows as $row){
				$stock = lookup($row["symbol"]);
				$totalcash = $stock["price"] * $row["shares"];

				print("<tr>");
				print("<td> {$row["symbol"]}</td>");
				print("<td>{$stock["name"]}</td>");
				print("<td>{$row["shares"]}</td>");
				print("<td>$".$stock["price"]."</td>");
				print("<td>$".$totalcash."</td>");
				print("</tr>");
			}

			// We need to retrieve the users cash
			$usercash = query("SELECT cash FROM users WHERE	 id = ?", $_SESSION["id"]);
			
			foreach ($usercash as $user){
				print("<tr>");
				print("<td colspan='4'><b>CASH</b></td>");
				print("<td>$".$user["cash"]."</td>");
				print("</tr>");
			}
		
			
			/* actually does nothing .. maybe for later use ? Search ? 
			$positions = [];
			foreach ($rows as $row)
			{
			    $stock = lookup($row["symbol"]);
			    if ($stock !== false)
			    {
			        $positions[] = [
			            "name" => $stock["name"],
			            "price" => $stock["price"],
			            "shares" => $row["shares"],
			            "symbol" => $row["symbol"]
			        ];
			    }
			}
			*/

		?>
	</tbody>
	</table>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
