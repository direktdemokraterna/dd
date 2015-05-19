function expand_mobile_menu () {

	var menu = document.getElementById("hide_menu");
	var menu2 = document.getElementById("logout-link");

	if(menu.style.display != "block"){
		menu.style.display = "block";
		menu2.style.display = "block";
	}
	else{
		menu.style.display = "none";
		menu2.style.display = "none";
	}

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