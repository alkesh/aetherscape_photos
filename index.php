<?php
include "common.inc";
include "photo_album.inc";

xhtml_header("Alkesh's Photos", "photoalbum.css");
?>
<!-- compliance patch for microsoft browsers -->
<!--[if lt IE 7]>
<script src="/ie7/ie7-standard-p.js" type="text/javascript">
</script>
<![endif]-->
<div id="header">
<h1>Alkesh's Photos</h1>
<span class="breadcrumb"><?php breadcrumbgen(); ?></span>
</div>
<div id="content">
<?php
if (is_null($_REQUEST['dir']) && is_null($_REQUEST['show_album']) && is_null($_REQUEST['show_image'])){

  list_albums($_REQUEST['dir']);

} elseif (!is_null($_REQUEST['show_album'])){

  $albumdir = $_REQUEST['show_album'];
  show_album($albumdir);

} elseif (!is_null($_REQUEST['show_image'])){

  show_image($_REQUEST['show_image']);

} else {

  list_album_days($_REQUEST['dir']);

}
?>
</div><!-- content -->
<?php
xhtml_footer(true);
?>
