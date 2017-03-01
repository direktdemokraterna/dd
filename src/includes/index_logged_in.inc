<?php 
	db_user::update_last_activity_time($_SESSION['id']);
    require("../includes/menubar.inc");
?>
<div id="header-lang">
	<?php \View\index::output_language_buttons(); ?>
</div>
<div id="wrap">
	<div class="social-media-icons-dd">
        <a href="https://www.facebook.com/direktdemokraterna" title="Direktdemokraterna på Facebook" target="_blank"><span class="fa fa-facebook"></span></a>
        <a href="https://twitter.com/DDemokraterna" title="Prata med oss på Twitter" target="_blank"><span class="fa fa-twitter"></span></a>
        <a href="https://plus.google.com/+Direktdemokraterna/posts" title="Häng med på Google Plus" target="_blank"><span class="fa fa-google-plus"></span></a>
        <!--<a href="http://instagram.com/Direktdemokraterna" title="Direktdemokraterna på Instagram" target="_blank"><span class="fa fa-instagram"></span></a>-->
        <a href="http://youtube.com/Direktdemokraterna" title="Direktdemokraterna på Youtube" target="_blank" style="margin-right: 3px;"><span class="fa fa-youtube"></span></a>
        <!--<a href="http://www.mynewsdesk.com/se/dd/latest_news" title="Direktdemokraterna på My Newsdesk" target="_blank" style="margin-right: 3px;"><span class="fa fa-comment"></span></a>-->
    </div>
	<div class="header">
		<div id="header-logo">
			<a href="index.php"><img id="dd-logo" src="images/direktdemokraterna-logotyp.png"></a>
		</div>
	</div>
	<div class="main">
		<?php 
			require("../includes/primary_content.inc");
			require("../includes/sidebar.inc");
		?>
	</div>
</div>
</div>
<?php 
	require("../includes/footer.inc");
?>