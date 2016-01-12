<?php
	__h1(_t("Create a new workgroup"));
	__open_form();
	__textfield("title", _t("Name"), 1);
	__textfield("number_of_members", _t("Number of members"), 2);
	__textarea("description", _t("Description"), 3);
	__submit_and_close(_t("Create"), null, null, 4);
	__p(_t("Here you create restricted workgroups, workgroups whose membership is not free and with a restricted number of members. In association with the creation of this workgroup a continous vote will also be created where the members of this workgroup are appointed."));
?>
