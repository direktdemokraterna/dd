function toggle_mobile_main_menu () {
	toggle_mobile_menu("hide_menu");
	hide_mobile_menu("logout-link");
}

function toggle_mobile_user_menu () {
	toggle_mobile_menu("logout-link");
	hide_mobile_menu("hide_menu");
}

function toggle_mobile_menu (id) {
	var menu = document.getElementById(id);
	menu.style.display = menu.style.display == "block" ? "none" : "block";
}

function hide_mobile_menu (id) {
	var menu = document.getElementById(id);
	menu.style.display = "none";
}

function checkAll(ele, class_name) {
	var checkboxes = document.getElementsByClassName(class_name);
	if (ele.checked) {
		for (var i = 0; i < checkboxes.length; i++) {
			if (checkboxes[i].type == 'checkbox') {
				checkboxes[i].checked = true;
			}
		}
	} 
	else {
		for (var i = 0; i < checkboxes.length; i++) {
			if (checkboxes[i].type == 'checkbox') {
				checkboxes[i].checked = false;
			}
		}
	}
 }