<?php
/******************************************************************************/
function xhtml_header($title, $stylesheet = NULL){
	error_reporting(1);
	?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
 		"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title><?php echo $title ?></title>
<meta http-equiv="Content-type" content="text/html; charset=iso-8859-1" />
	<?php
	if (!is_null($stylesheet)){
	?>
<link rel="stylesheet" href="<?php echo $stylesheet ?>" type="text/css" />
	<?php
	}
	?>
</head>
<body>
	<?php
}
/******************************************************************************/
function xhtml_footer($validationlinks = NULL){
	if ($validationlinks){
	?>
	<div id="validxhtml">
		<a href="http://validator.w3.org/check?uri=referer">xhtml</a>
	</div>
	<?php
	}
	?>
  	</body></html>
	<?php
}
/******************************************************************************/
function dirlist($path, $reversesort = true, $excludelist = NULL){
	
	if (chdir($path)){
	$d = @opendir($path) or die("No photos available for this year yet");
	
	while (($file = readdir($d)) !== false){
		if ($file != "." && $file != ".." && is_dir($file)){
			if (!is_null($excludelist)){
				$fileexcluded = false;
				foreach ($excludelist as $excluded){
					if ($file == $excluded){
						$fileexcluded = true;
					}
					if (!$fileexcluded){
						$dirs[] = $file;
					}
				}
			} else {
				$dirs[] = $file;
			}
		}
	}
	closedir($d);
	if ($reversesort){
		arsort($dirs);
	} else {
		asort($dirs);
	}
	return  $dirs;
	} else {
		echo "no photos available for this year";
		return;
	}
}
/******************************************************************************/
function parsedate($filename){
/* assume date format is: yyyy_mm_dd - some description */
	$year = substr($filename,2,2);
	$month = substr($filename,5,2);
	$day = substr($filename,8,2);
	$description = substr($filename,13);
	$date = "$day/$month/$year";
	
	$arr = array(	"year" => $year,
					"month" => $month,
					"day" => $day,
					"description" => $description,
					"date" => $date
					);
	return $arr;
}
/******************************************************************************/
/* function to strip out characters not allowed in xhtml attributes */
function stripunwanted($string){
 $clean = ereg_replace("[[:punct:][:space:]]","", $string);
 return $clean;
}
/******************************************************************************/
/* Breadcrumb generator */
function breadcrumb(){
	require 'breadcrumbconfig.inc'; 	// contains $breadcrumbrootdir 
									// and $breadcrumbrooturl
	$cwd = getcwd();
	//$relevantpath = str_replace($breadcrumbrootdir, "", $cwd);
	

	/* populate array with directories leading up to root directory */
	for (	$currentpath = $cwd;
			strcmp($currentpath,$breadcrumbrootdir) != 0;
			$currentpath = substr($currentpath,0,strrpos($currentpath,"/"))
		){
		$currentname = substr(strrchr($currentpath,"/"),1);
		$currentlink = str_replace($breadcrumbrootdir, $breadcrumbrooturl, $currentpath);
		
		$breadcrumbarray[] = array (	"path" => $currentpath,
									"name" => $currentname,
									"link" => $currentlink);
	}
	
	/* add root to array */
	$breadcrumbarray[] =  array ( 	"path" => $breadcrumbrootdir,
										"name" => "Home",
										"link" => $breadcrumbrooturl
								);	
	
	krsort($breadcrumbarray);
	
	$firstloop = true;
	foreach ($breadcrumbarray as $breadcrumb){
		if (!$firstloop) echo "&raquo;";	
		?>
			<a href="<?php echo $breadcrumb["link"] ?>"><?php echo $breadcrumb["name"] ?></a>
		<?php
		$firstloop = false;
	}
}
/******************************************************************************/
function getalbumfolderthumb($albumfolderpath){
	$path = $albumfolderpath."/thumbs";
	chdir($path);
	$d = @opendir($path) or die("Unable to open $path");
	$foundthumb = false;
	while ((($file = readdir($d)) !== false) && !$foundthumb){
		if ($file != "." && $file != ".." && $file !="res"){
			$foundthumb = true;
		}
	}
	
	closedir($d);

	if (is_null($file)){
		die("No thumbnails in directory ".$albumfolderpath."/thumbs");
	}
	return $file;
}
/******************************************************************************/
function stringfromslash($string){
	return substr($string, strrpos($string, '/')+1);
}
/******************************************************************************/
function myurlencode($val)
{
 	return str_replace("%2f","/",rawurlencode($val));
// return rawurlencode (str_replace("/","%2f",$val));
} 
/******************************************************************************/
function myurldecode($val)
{
 return str_replace("%2f","/",urldecode ($val));
} 
/******************************************************************************/
?> 
