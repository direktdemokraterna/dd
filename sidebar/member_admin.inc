<ul>
	<li>
		<h2>Alternativ</h2>
		<ul>
			<li><a href="index.php?type=member_admin">Medlemslista</li>
			<li><a href="index.php?type=member_admin&action=create_new">Skapa ny medlem</li>
			<?php if(db_user::get_all_user_applications()) : ?>
				<li><a href="index.php?type=member_admin&action=list_applications">Hantera ansökningar</li>
			<?php endif; ?>
			<li><a href="index.php?type=member_admin&action=create_workgroup">Skapa arbetsgrupp</li>
		</ul>
	</li>
</ul>