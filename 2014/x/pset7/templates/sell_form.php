
<?php
	// quote.php is sending the stock variable  
	if(isset($stock)){
		print("<div>");

		print("A share of " . $stock["name"] . "(" . $stock["symbol"] 
			. " ) costs <b> $" . $stock["price"] 
		. "</b>");

		print("</div>");

	}
?>
<form action="sell.php" method="post">
	<fieldset>
		<div class="form-group">
			<select class="form-control" name="symbol">
			<option value=""> </option>
			<?php 
			$rows = query("SELECT symbol FROM stocks WHERE id = ?", $_SESSION["id"]);
				foreach($rows as $row){
					print("<option value='{$row["symbol"]}'>{$row["symbol"]}</option>");
				}
			?>
			</select>
		</div>
		<div class="form-group">
			<button type="submit" class="btn btn-default">Sell all your shares</button>
		</div>
	</fieldset>
</form>