<html>
	<body>
		<form action="" method="post">
			<input type="text" name="cm" placeholder="" />
			<input type="submit" name="sub" />
			
		</form>
	</body>
</html>

<?php 
	$p = '/home/revenant/Desktop/z_windowsa/php/commands.txt';
	if(isset($_POST['sub'])){
		$cm = $_POST['cm'];
		$f = fopen($p, 'w');
		fwrite($f, "$cm");
		fclose($f);
		
	}

?>


