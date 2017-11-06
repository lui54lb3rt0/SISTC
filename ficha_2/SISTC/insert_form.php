
<?php include("header.html");?>

<form action='vehicle.php' method=POST>
Plate: <input name='plate' pattern=".{6,6}"  size="6" required> <br>
Owner: <input name='owner' pattern=".{3,80}" size="80" required> <br>
Value: <input name='value' type="number" step="0.01" value="0" required> <br>
<br>
<input type=submit value='Insert'>
</form>

<?php include("footer.html");?>
