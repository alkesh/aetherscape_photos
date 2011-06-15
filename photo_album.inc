<?php
require_once "common.inc";

function dirs($dir, $revsort=false){
  $d = @opendir(getcwd()) or die("unable to open directory ".$dir);
  while (($file = readdir($d)) !== false){
    if ($file != "." && $file != ".." && is_dir($file)){
      $dirs[] = $file;
    }
  }
  closedir($d);
  if ($revsort){
    arsort($dirs);
  }
  return $dirs;
}

function files($dir, $fileextension, $filefilter='.*'){
$dir = str_replace("\\","",$dir);
  $d = @opendir($dir) or die("Unable to open ".$dir);
  while (($file = readdir($d)) !== false){
    if (!is_dir($file) && ereg($filefilter, $file)){
      $files[] = str_replace("\\","",$file);
    }
  }
  closedir($d);
  natcasesort($files);
  return $files;
}

function prevnextfilelist($path, $fileextension, $keyfile){
  $files = files($path, $fileextension);
  $i=0;
  foreach($files as $entry){
    if($entry == $keyfile){
      $ki = $i;
    }
    $i++;
  }
  $prevnextfiles = array('filenum'=>($ki+1), 'totalfiles'=>($i));
  if ($ki>0){
    $prevnextfiles['prev'] = $files[$ki-1];
  }
  if ($ki<($i-1)){
    $prevnextfiles['next'] = $files[$ki+1];
  }
  return $prevnextfiles;
}

function parse_date($filename){
/* assume date format is: yyyy_mm_dd - some description */
        $year = substr($filename,2,2);
	$month = substr($filename,5,2);
	$day = substr($filename,8,2);
	$description = substr($filename,13);
	$date = "$day/$month/$year";

        $arr = array(   "year" => $year,
                        "month" => $month,
                        "day" => $day,
                        "description" => $description,
                        "date" => $date
                        );
	return $arr;
}

function list_album_days($dir){
  chdir($dir);
  $day_folders = dirs($dir);
  ?>
  <ul class="days">
  <?php
  foreach($day_folders as $day_folder){
    $fileinfo = parsedate($day_folder);
    ?>

    <li id="<?php echo "day_".stripunwanted($day_folder) ?>" class="dayrow">
      <div class="daydate">
        <a href="?show_album=<?php echo $dir."/".$day_folder ?>"><?php echo $fileinfo["date"] ?></a>
      </div>
      <div class="daydescription">
      <?php
      $desc_file = $day_folder."/description.html";
      if (file_exists($desc_file)){
        include $desc_file;
      } else {
        echo "Click to view this days photos";
      }
      ?>
      </div>
    </li>
    <?php
  }
  ?>
  </ul>
  <div class="navlink">
    <a href="./">Return to Main Page</a>
  </div>
  <?php
}

function list_albums($basedir){
  $dirs = dirs($basedir,true);
  foreach($dirs as $dir){
   $html_safe_dir = $dir;
   $fileinfo = parse_date($dir)
   ?>
     <div class="album_entry">
     <?php
       if (!file_exists($dir."/thumbs")){
         $action = "dir";
       } else {
	 $action = "show_album";
       }
     ?>
      <span class="albumdate"><?php echo $fileinfo["date"] ?></span>
       <span class="albumlink"><a href="?<?php echo $action ?>=<?php echo $html_safe_dir; ?>"><?php echo $fileinfo["description"]; ?></a></span>
     </div>
   <?php
  }
  ?>
  <h3>Older Photos</h3>
  <a href="/older_photos">Available Here</a>
  <?php
}

function show_album($dir){
  $dir = str_replace("\\","",$dir);
  $last_slash_pos = strrpos($dir, "/");
  $parentdir=substr($dir, 0, $last_slash_pos);
  $files = files($dir."/thumbs", "jpg", "^IMG.*");
  ?>
  <div class="wrap">
  <?php
  foreach ($files as $file){
  ?>
  <div class="thumbnail">
  <a href="?show_image=<?php echo ($dir).'/800x600/'.rawurlencode($file); ?>&amp;parent=<?php
   echo $currenturl; ?>">
  <span></span>
  <img src="<?php echo './'.($dir).'/thumbs/'.rawurlencode($file); ?>"
	           alt="<?php echo $file; ?>" />
  </a>
  </div>
  <?php
  }
  ?>
  </div><!-- wrap -->
  <div class="navlink">
  <?php
    $d = getcwd()."/".$parentdir;
    if (strlen($parentdir) == 0){
  ?>
   <a href=".">Return to Index</a>
  <?php
  } else {
  ?>
    <a href="?dir=<?php echo $parentdir  ?>">Return to Index</a>
  <?php
    }
  ?>
  </div>
  <?php
}

function show_image($image){
  $image = str_replace("\\","",$image);
  $last_slash_pos = strrpos($image, "/");
  $second_to_last_slash_pos = strrpos(substr($image, 0, $last_slash_pos), "/");
  $image_name = substr($image, $last_slash_pos+1, strlen($image)-$last_slash_pos);
  $path = substr($image, 0, $last_slash_pos);
  $prevnext = prevnextfilelist($path, 'jpg', $image_name); 
  $first_slash_pos = strpos($image, "/"); 
  $second_slash_pos = strpos($image, "/", $first_slash_pos+1); 
  $album_path = substr($image, 0, $second_to_last_slash_pos);
  ?>
  <div class="imagecount">
    <?php echo $prevnext['filenum'] ?>/<?php echo $prevnext['totalfiles'] ?> 
  </div>
  <div class="imagenav">
  <?php 
    if(isset($prevnext['prev'])){
  ?>
    <a href="?show_image=<?php echo $path."/".$prevnext['prev'] ?>">prev</a>
  <?php 
    }
    if(isset($prevnext['next'])){
  ?>
    <a href="?show_image=<?php echo $path."/".$prevnext['next'] ?>">next</a>
  <?php
    }
  ?>
   <a href="?show_album=<?php echo $album_path ?>">up</a> 
  </div>
  <div class="image">
  <img src="<?php echo $image ?>" alt="<?php echo $image_name ?>"/>
  </div>
  <div class="exifdata">
    <?php
      #$exif_data_path = substr_replace($image, "exifdata", $second_slash_pos+1, 7).".exif";
      #show_exif_data($exif_data_path);
    ?>
  </div>
  <?php
  $original_photo = substr_replace($image, "originals", $second_to_last_slash_pos+1, 7);
  if (file_exists($original_photo)){
    $url_base = "http://mediabox.moon127.net/~alkesh/photos/";
    $thumb = substr_replace($image, "thumbs", $second_slash_pos+1, 7);
    $image_thumb_url = $url_base.$thumb;
    $image_full_url = $url_base.$original_photo;
    $img = imagecreatefromjpeg($original_photo);
    if ($img){
      $img_w = imagesx($img);
      $img_h = imagesy($img);
    } 
  ?>
    <div class="linkstoimages">
      <a href="?show_image=<?php echo $original_photo  ?>">Original full-size photo</a>
    </div>
  <?php
  }
  ?>
  <?php
}

function photobox_printbutton_form($image_name, $image_thumb, $image_full, $image_width, $image_height){
?>
<form name="orderform" action="http://printbutton.photobox.co.uk/printbutton.html" method="post" target="printbutton" onsubmit="javascript:window.open('','printbutton','width=200,height=350')">
  <input type="hidden" name="v_id" value="1010432"/>
  <input type="hidden" name="buy" value="<?php echo $image_name ?>"/>
  <input type="hidden" name="notfromcache" value="true"/>
  <input type="hidden" name="photo_url_<?php echo $image_name ?>" value="<?php echo $image_full ?>"/>
  <input type="hidden" name="thumbnail_url_<?php echo $image_name ?>" value="<?php echo $image_thumb ?>"/>
  <input type="hidden" name="photo_width_<?php echo $image_name ?>" value="<?php echo $image_width ?>"/>
  <input type="hidden" name="photo_height_<?php echo $image_name ?>" value="<?php echo $image_height ?>"/>
<?php
 # <input type="hidden" name="photo_width_IMG_4093.JPG" value="720">
 # <input type="hidden" name="photo_height_IMG_4093.JPG" value="540">
 # <input type="hidden" name="toImage" value="slides/IMG_4093.JPG">
 # <input type="hidden" name="toThumb" value="thumbs/IMG_4093.JPG">
?>
<a href="javascript:document.forms['orderform'].submit()">Order this Photo</a>
</form>
<?php
}

function show_exif_data($exif_path){
  #echo $exif_path;
  #$xmlparser = xml_parser_create();
  #xml_set_character_data_handler($xmlparser, "xml_character_handler");
  #xml_parser_set_option($xmlparser,XML_OPTION_SKIP_WHITE,1);
  #xml_parse($xml_parser, file_get_contents($exif_path));
  
  #$fp=fopen($exif_path,"r");
  #while ($data=fread($fp,4096)){
  #  xml_parse($xmlparser, $data,feof($fp));
  #}
  #xml_parser_free($xml_parser);
}

function xml_character_handler($parser, $data){
  echo $data;
}

function breadcrumbgen(){
  $rooturl = "/photos";
  $rootdir = "/home/alkesh/photos";
  $show = false;
  $breadcrumbarray[] = array ("name" => "Home", "link" => $rooturl );

  if (isset($_REQUEST["show_album"])){
    $current_action="show_album";
  } else if (isset($_REQUEST["dir"])){
    $current_action="dir";
  } else if (isset($_REQUEST["show_image"])){
    $current_action="show_image"; 
  }
  if (isset($_REQUEST["show_album"]) 
  	|| isset($_REQUEST["dir"])
	|| isset($_REQUEST["show_image"])){
    $show = true;
    $album = str_replace("\\","",$_REQUEST[$current_action]);
    $slashes = substr_count($album, "/");
    
    if (!strpos($album, "/")){
      /* For top level album pages */
      $current_album = $album; 
      $action = $current_action;
    } else {
      /* for sub-albums or images */
      if ($slashes == 3){
        /* for images in sub-albums*/
        $action="dir";
      } else {
        if ($current_action == "show_album"){
          /* for sub-album */
          $action="dir";
	} else {
          /* for image in top-level album */
	  $action="show_album";
	}
      }
      $slashpos = strpos($album, "/");
      $current_album = substr($album,0,$slashpos);
    }
    $albuminfo = parse_date($current_album);
    $albumdate = strftime("%B %Y", strtotime($albuminfo["year"]."-".$albuminfo["month"]."-".$albuminfo["day"]));
    $albumname = $albuminfo["description"]." (".$albumdate.")";
    $url = "?".$action."=".$current_album;
    $breadcrumbarray[] = array ("name" => $albumname, "link" => $url );
    if (isset($slashpos)){
      if ($current_action != "show_image"){
        $action = $current_action;
        $url = "?".$action."=".$album;
        $sub_album = str_replace("\\","",substr($album,$slashpos+1));
        $breadcrumbarray[] = array ("name" => $sub_album, "link" => $url );
      } else {
	if ($slashes == 3){
          $action = "show_album";
	  $first_slash_pos = strpos ($album, "/");
	  $second_slash_pos = strpos ($album, "/", $first_slash_pos+1);
	  $sub_album = substr($album,$first_slash_pos+1,$second_slash_pos-$first_slash_pos-1);
	  $url = "?".$action."=".substr($album,0,$second_slash_pos);
          $breadcrumbarray[] = array ("name" => $sub_album, "link" => $url );
	}
	$last_slash_pos = strrpos ($album, "/");
	$image_name = substr($album, $last_slash_pos+1);
        $url = "?".$current_action."=".$album;
	$breadcrumbarray[] = array ("name" => $image_name, "link" => $url);
      }
    }
  } 

  if ($show){
    $firstloop = true;
    foreach ($breadcrumbarray as $bc){
      if (!$firstloop) echo "&raquo;";
      ?>
        <a href="<?php echo $bc["link"] ?>"><?php echo $bc["name"] ?></a>
      <?php
      $firstloop = false;
    }
  }
}
?>
