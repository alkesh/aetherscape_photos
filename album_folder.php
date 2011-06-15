<?php
require('common.inc');
$folder = substr(strrchr(getcwd(), "/"),1);
$parsedfoldername = parsedate($folder);
$description = $parsedfoldername["description"];
$albumpath = getcwd();
$dirs = dirlist($albumpath, false, array("res"));

//$xml = domxml_open_file('albumfolder.xml');

xhtml_header("Photo Album - ".$description);
?>
<div class="breadcrumbs">
<?php breadcrumb() ?>
</div>

<?php
	foreach ($dirs as $dir){
		$parseddirname = parsedate($dir);
?>
<div class="albumfolder">
	<span class="foldername"><a href="<?php echo $dir ?>"><?php echo $parseddirname["description"]; ?></a></span>
	<span class="folderthumbnail">
	<a href="<?php echo $dir ?>">
	<img src="<?php echo $dir."/thumbs/".getalbumfolderthumb($albumpath."/".$dir) ?>" alt="<?php echo $parseddirname["description"]; ?>" />
	</a>
	</span>
	<span class="folderdescription">
	<?php
		@include($albumpath."/".$dir."/folderdescription.html");
	?>
	</span>
</div>
<?php
	}
?>
<?php
xhtml_footer();
?>