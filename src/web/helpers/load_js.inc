<script src="//code.jquery.com/jquery-1.11.3.min.js"></script>
<script src="//code.jquery.com/ui/1.9.2/jquery-ui.js"></script>
<script src="js/libs/jquery.ui.touch-punch.min.js"></script>

<script src="js/index.js"></script>
<script src="js/forum.js"></script>
<script src="js/libs/responsive-tables.js"></script>
<script src="js/session.js"></script>
<script src="js/validateForm.js"></script>
<script src="js/constituency.js"></script>
<script src="js/util.js"></script>

<?php if($_GET['type'] == "vote") : ?>
<script src="js/vote.js"></script>
<script>
	var dd_public_key = "<?php echo DD_PUBLIC_KEY; ?>";
	var dd_anon_public_key = "<?php echo DD_ANON_PUBLIC_KEY; ?>";
</script>

<script src="helpers/Crypt/bin/jsencrypt.min.js"></script>
<script src="//cdnjs.cloudflare.com/ajax/libs/crypto-js/3.1.2/components/aes-min.js"></script>

<script src="js/pidCrypt/pidcrypt.js"></script>
<script src="js/pidCrypt/pidcrypt_util.js"></script>
<script src="js/pidCrypt/md5.js"></script>
<script src="js/pidCrypt/aes_core.js"></script>
<script src="js/pidCrypt/aes_cbc.js"></script>

<script src="js/libs/gibberish-aes.js"></script>
<?php endif; ?>

