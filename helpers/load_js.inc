<script src="http://code.jquery.com/jquery-1.11.3.min.js"></script>
<script src="http://code.jquery.com/ui/1.9.2/jquery-ui.js"></script>
<script src="helpers/js/libs/jquery.ui.touch-punch.min.js"></script>

<script src="helpers/js/index.js"></script>
<script src="helpers/js/forum.js"></script>
<script src="helpers/js/libs/responsive-tables.js"></script>
<script src="helpers/js/session.js"></script>
<script src="helpers/js/validateForm.js"></script>

<?php if($_GET['type'] == "vote") : ?>
<script src="helpers/js/vote.js"></script>
<script>
	var dd_public_key = "<?php echo DD_PUBLIC_KEY; ?>";
	var dd_anon_public_key = "<?php echo DD_ANON_PUBLIC_KEY; ?>";
</script>

<script src="helpers/Crypt/bin/jsencrypt.min.js"></script>
<script src="http://crypto-js.googlecode.com/svn/tags/3.1.2/build/rollups/aes.js"></script>

<script src="helpers/js/pidCrypt/pidcrypt.js"></script>
<script src="helpers/js/pidCrypt/pidcrypt_util.js"></script>
<script src="helpers/js/pidCrypt/md5.js"></script>
<script src="helpers/js/pidCrypt/aes_core.js"></script>
<script src="helpers/js/pidCrypt/aes_cbc.js"></script>

<script src="helpers/js/libs/gibberish-aes.js"></script>
<?php endif; ?>