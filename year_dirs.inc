<?php
	breadcrumb();
?>
<h1>Photo Archives</h1>

<?php
	$dirs = dirlist(getcwd());
	
	foreach($dirs as $dir){
?>
<a href="<?php echo $dir ?>"><?php echo $dir ?></a>
<br/>
<?php	
	}
?>
<div class="returnlink"><a href="../">Return to Main Page</a></div>
