<div id="dd-to-top">
	<a href="#pseudo_menubar" id="site-scroll-top" title="Gå till toppen av sidan" alt="Gå till toppen av sidan"><i class="fa fa-chevron-up" aria-hidden="true"></i></a>
</div>
<div id="footer">
	<footer>
		<div class="footer-widget">
        	<h2>Meny</h2>
			<ul>
			<li class="f-member"><a href="index.php?type=member">Användare</a>
            	<ul>
                <li class="f-member"><a href="index.php?type=member&action=admin_list">Administratörer</a></li>
                <li class="f-member"><a href="index.php?type=member&action=admin_list">Administratörer</a></li>
				<li class="f-member"><a href="index.php?type=member&action=admin_list">Administratörer</a></li>
                </ul>
            </li>
			<li class="f-message"><a href="index.php?type=message">Meddelanden</a>
            	<ul>
                <li class="f-member"><a href="index.php?type=message&amp;action=inbox">Inkorg</a></li>
                <li class="f-member"><a href="index.php?type=message&amp;action=outbox">Utkorg</a></li>
                <li class="f-member"><a href="index.php?type=message&amp;action=write">Skriv meddelande</a></li>
                </ul>
            </li>
			<li class="f-votes"><a href="index.php?type=vote">Omröstningar</a>
            	<ul>
                <li class="f-member"><a href="index.php?type=vote&amp;action=list_props">Propositioner</a></li>
                <li class="f-member"><a href="index.php?type=vote&amp;action=list_active_votes">Omröstningar</a></li>
                <li class="f-member"><a href="index.php?type=vote&amp;action=delegations">Delegater</a></li></ul>
            </li>
			<li class="f-forum"><a href="index.php?type=forum">Forum</a></li>
			<li class="f-admin"><a href="index.php?type=member&action=view&id=5#">Admin</a>
            	<ul>
				<li class="f-member"><a href="index.php?type=member_admin">Medlemsadministratör</a></li>
                <li class="f-member"><a href="index.php?type=vote_admin">Valadministratör</a></li>
                <li class="f-member"><a href="index.php?type=treasurer">Kassör</a></li>
                <li class="f-member"><a href="index.php?type=superadmin">Superadmin</a></li>
                </ul>
            </li>
			</ul>
        </div>
        <div class="footer-widget">
        	<h2>Mina sidor</h2>
			<ul>
			<li><a href="index.php?type=member&action=view">Profil</a></li>
			<li><a href="index.php?type=member&action=settings">Kontoinställningar</a></li>
			<li><a href="index.php?type=vote&action=delegations">Mina delegater</a></li>
			<li><a href="index.php?type=message&action=inbox">Inkorg</a></li>
			</ul>
            <h2>Viktiga länkar</h2>
			<ul>
			<li><a href="http://direktdemokraterna.se">Offentlig hemsida</a></li>
			<li><a href="http://direktdemokraterna.se/organisation">Organisation</a></li>
			<li><a href="http://direktdemokraterna.se/medlemsansvariga/">Medlemssupport</a></li>
			<li><a href="http://direktdemokraterna.se/medlem.pdf">Medlemsinformation (pdf)</a></li>
			</ul>
		</div>
        <div class="footer-widget">
        	<h2>Logga ut</h2>
			<ul>
			<li><a href="index.php?logout=1">Logga ut</a></li>
			</ul>
			<h2>Sociala media</h2>
			<ul>
			<li><a href="https://www.facebook.com/direktdemokraterna" target="_blank" alt="Besök vår Facebooksida" title="Besök vår Facebooksida">Facebook</a></li>
			<li><a href="https://twitter.com/DDemokraterna" target="_blank" alt="Besök vår Twitter" title="Besök vår Twitter">Twitter</a></li>
			<li><a href="https://plus.google.com/+Direktdemokraterna/posts" target="_blank" alt="Besök vår Google Plus-sida" title="Besök vår Google Plus-sida">Google Plus</a></li>
			<li><a href="http://youtube.com/Direktdemokraterna" target="_blank" alt="Besök vår Youtube-kanal" title="Besök vår Youtube-kanal">Youtube</a></li>
			</ul>
        </div>
        <div class="footer-widget">
			<ul>
			<li class="search-forums"> 
				<?php
				\View\controls::output_search_box("i forum", "forum", "search", 111);
				?>
			</li>
			<li class="sidebar-search-propositions">
		<?php 
			\View\controls::output_search_box("propositioner", "vote", "search_prop", 101);
		?>
			</li>
			<li class="sidebar-search-votes">
			<?php 
				\View\controls::output_search_box("omröstningar", "vote", "search", 103);
			?>
			</li>
			</ul>
        </div>
	</footer>
</div>
