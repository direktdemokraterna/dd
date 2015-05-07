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