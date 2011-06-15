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
<body>
<div id="content">
<div id="title">
<h2><?php echo $pagetitle; ?></h2>
</div>
<div id="days">
<?php

$dirs = dirlist(getcwd()."/".$photodir, false, array("full_bak"));

foreach ($dirs as $dir){
$dirinfo = parsedate($dir);
?>
<p class="day">
<span class="daydate"><?php echo $dirinfo["date"] ?></span>
<span class="daylink">
<a href="album.php?photodir=<?php echo $photodir."/".$dir; ?>&parent=yes"><?php echo $dirinfo["description"]; ?></a>
</span>
</p>
<?php
}
?>
</div><!-- days -->
</div><!-- content -->
</body>
</html>