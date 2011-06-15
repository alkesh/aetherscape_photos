<!DOCTYPE html
     PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
     "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<?php
require('common.inc');
$image = $_REQUEST['image'];
$pagetitle = myurldecode($image);

function dateCmp($a, $b){  return ($a[1] < $b[1]) ? -1 : 1;}

function prevnextfilelist($path, $fileextension, $keyfile){
  $d = @opendir($path) or die("Unable to open $path");
//  $i = 0;
  while (($file = readdir($d)) !== false){
    if (
		$file != "."
		&&
		$file != ".."
		&&
	    (!is_file($file))
		&&
		(strcasecmp(substr($file,(strrpos($file, ".")+1)),$fileextension)==0)
	){
	  $lastmodified = filemtime("$path/$file");
      $files[] = array($file, $lastmodified);

//	  if ($path."/".$file == ($keyfile)){
//	    $ki = $i;
//	  }
//	$i++;
    }
  }
  closedir($d);

  usort($files, "dateCmp");

  $i = 0;
  foreach ($files as $entry){
    if ($path."/".$entry[0] == ($keyfile)){
      $ki = $i;
    }
    $i++;
  }

  $prevnextfiles =
		array (
			'filenum'=>($ki+1),
			'totalfiles'=>($i)
		);
  if ($ki>0){
  	$prevnextfiles['prev'] = $files[$ki-1][0];
  }
  if ($ki<($i-1)){
  	$prevnextfiles['next'] = $files[$ki+1][0];
  }

  return $prevnextfiles;
}
$dir = dirname($image);
$prevnextfiles = prevnextfilelist($dir, "jpg", $image);
$currentpageurl = "slide.php?image=".$image;
if (isset($_REQUEST['parent'])){
	$currentpageurl = $currentpageurl."%26parent=".$_REQUEST['parent'];
}
?>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title><?php echo $pagetitle; ?></title>
<link href="default.css" rel="stylesheet" type="text/css" />
<script type="text/javascript">
// <![CDATA[ 
var takenAction = false;
<?php if (isset($prevnextfiles['next'])){
$nextpageurl = "slide.php?image=".$dir."/".$prevnextfiles['next'];
if (isset($_REQUEST['parent'])){
	$nextpageurl = $nextpageurl."%26parent=".$_REQUEST['parent'];
}
?>
var nextPageUrl="<?php echo ($nextpageurl); ?>";
<?php
} else {
?>
var nextPageUrl="<?php echo $currentpageurl; ?>";
<?php
}
?>
<?php if (isset($prevnextfiles['prev'])){
$prevpageurl = "slide.php?image=".$dir."/".$prevnextfiles['prev'];
if (isset($_REQUEST['parent'])){
	$prevpageurl = $prevpageurl."%26parent=".$_REQUEST['parent'];
}
?>
var prevPageUrl="<?php echo $prevpageurl; ?>";
<?php
} else {
?>
var prevPageUrl="<?php echo $currentpageurl; ?>";
<?php
}
if (isset($_REQUEST['parent'])){
?>
var parentPageUrl="<?php echo $_REQUEST['parent']; ?>";
<?php
}
?>
// ]]> 
</script>
<script type="text/javascript" src="navigation.js"></script>
</head>
<body onload="initKeyboard();">
<div id="content">
<div id="filecounter">
<?php
  echo $prevnextfiles['filenum']."/".$prevnextfiles['totalfiles'];
?>
</div>
<div id="pagenav">
<?php if(isset($_REQUEST['parent'])){
?>
<a href="<?php echo $_REQUEST['parent']; ?>">Up</a>
<?php
}
?>
</div>
<div id="imagenav">
<?php
if (isset($prevnextfiles['prev'])){
?>
<a href="<?php echo urldecode($prevpageurl); ?>">&lt;--previous</a>
<?php
}
if (isset($prevnextfiles['next'])){
?>
<a href="<?php echo urldecode($nextpageurl); ?>">next--&gt;</a>
<?php
}
?>
</div><!-- imagenav -->
<div class="image">
<img src="<?php echo rawurldecode($image); ?>" alt="<?php echo rawurldecode($image); ?>" />
</div><!-- image -->
</div><!-- content -->
<div id="validxhtml">
<hr />
		<a href="http://validator.w3.org/check/referer">XHTML</a>
 		<a href="http://jigsaw.w3.org/css-validator/">CSS</a>
</div>
</body>
</html>