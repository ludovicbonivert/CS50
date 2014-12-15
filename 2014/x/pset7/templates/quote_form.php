
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
<form action="quote.php" method="post">
	<fieldset>
		<div class="form-group">
			<input autofocus class="form-control" name="symbol" placeholder="Symbol" type="text"/>
		</div>
		<div class="form-group">
			<button type="submit" class="btn btn-default">Get Quote</button>
		</div>
	</fieldset>
</form>