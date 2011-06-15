<!DOCTYPE html
     PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
     "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<?php
require('common.inc');
$pagetitle = stringfromslash($photodir);
?>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title><?php echo $pagetitle; ?></title>
<link href="default.css" rel="stylesheet" type="text/css" />
</head>
<?php
echo $_REQUEST['photodir'];
$photodir=$_REQUEST['photodir'];
$lastslash=strrpos($photodir, '/');
$photodirparent=substr($photodir, 0, $lastslash);
$parentdir = stringfromslash($photodirparent);
$parentdirinfo = parsedate($parentdir);
$parentdirdesc = $parentdirinfo["description"];
$currentdirinfo = parsedate(stringfromslash($photodir));
$currentdirdesc = $currentdirinfo["description"];
?>
<body>
<div id="navigation">
<a href="days.php?photodir=<?php echo $photodirparent; ?>"><?php echo $parentdirdesc; ?></a>
&nbsp;&raquo;&nbsp;<a href=""><?php echo $currentdirdesc; ?></a>
</div>
<div id="content">
<div id="title">
<h2><?php echo $currentdirdesc; ?></h2>
</div>
<div class="spacer">
  &nbsp;
</div>
<?php

function filelist($path, $fileextension){
  $d = @opendir($path) or die("Unable to open $path");
  while (($file = readdir($d)) !== false){
    if (!is_dir($file)){
      $files[] = $file;
    }
  }
  closedir($d);
  return $files;
}


$currenturl= "album.php?photodir=".$photodir;

$files = filelist($photodir."/thumbs", "jpg");
?>

<div class="wrap">

<?php
foreach ($files as $file){
?>

<div>
  <a href="slide.php?image=<?php echo ($photodir).'/slides/'.rawurlencode($file); ?>&amp;parent=<?php echo $currenturl; ?>">
  <span></span>
  <img
      src="<?php echo './'.($photodir).'/thumbs/'.rawurlencode($file); ?>"
      alt="<?php echo $file; ?>" />
  </a>
</div>


<?php
}

?>
</div><!-- wrap -->

<div class="spacer">
  &nbsp;
</div>
</div><!-- content -->
<div id="validxhtml">
<hr />
		<a href="http://validator.w3.org/check/referer">XHTML</a>
 		<a href="http://jigsaw.w3.org/css-validator/">CSS</a>
</div>
</body>
</html>
