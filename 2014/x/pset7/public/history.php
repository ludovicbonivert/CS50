<?php 
	// configuration
    require("../includes/config.php"); 
     // render header
    require("../templates/header.php");
?>

<div>
	<table class="table table-striped">
		<thead>
			<tr>
				<th>Transaction</th>
				<th>Symbol</th>
				<th>Shares</th>
				<th>Price</th>
				<th>Date</th>
			</tr>
		</thead>
		<tbody>
<?php 

			$rows = query("SELECT operation, amountofshares, priceofshare, date, symbol FROM history WHERE id = ?", $_SESSION["id"]);
			// operation false = sold, true = bought
			foreach($rows as $row){
				
				$transaction = '';
				if($row["operation"] == 1){
					$transaction = "BUY";
				}else{
					$transaction = "SELL";
				}

				print("<tr>");
				print("<td>{$transaction}</td>");
				print("<td>{$row["symbol"]}</td>");
				print("<td>{$row["amountofshares"]}</td>");
				print("<td>$".$row["priceofshare"]."</td>");
				print("<td>{$row["date"]}</td>");
				print("</tr>");
			}

			print("</tbody>");
			print("</table>");
			print("</div>");

			// render footer
			require("../templates/footer.php");

?>			
