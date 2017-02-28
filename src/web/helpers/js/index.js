function isOutside(event, id) {
	return !$(event.target).closest('#' + id).length;
}

function closeWhenClickOutside(id) {
	$(document).click(function(event) {
		var local_id = id;
	    if(isOutside(event, local_id) && isOutside(event, 'alt-menu-row'))
            hide_mobile_menu(local_id);
	});
}

var mobile_main_menuOpened = false;
var mobile_user_menuOpened = false;

function toggle_mobile_main_menu () {
	toggle_mobile_menu("hide_menu");
	hide_mobile_menu("logout-link");
	if (!mobile_main_menuOpened)
		closeWhenClickOutside("hide_menu");
	mobile_main_menuOpened = true;
}

function toggle_mobile_user_menu () {
	toggle_mobile_menu("logout-link");
	hide_mobile_menu("hide_menu");
	if (!mobile_user_menuOpened)
		closeWhenClickOutside("logout-link");
	mobile_user_menuOpened = true;
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
	setAllCheckedState(checkboxes, ele.checked);
 }

function setAllCheckedState(checkboxes, checked) {
	for (var i = 0; i < checkboxes.length; i++) 
		if (checkboxes[i].type == 'checkbox')
			checkboxes[i].checked = checked;
 }
 
/* Scroll to anchor */ 
 
$(function() {
  $('a[href*="#"]:not([href="#"])').click(function() {
    if (location.pathname.replace(/^\//,'') == this.pathname.replace(/^\//,'') && location.hostname == this.hostname) {
      var target = $(this.hash);
      target = target.length ? target : $('[name=' + this.hash.slice(1) +']');
      if (target.length) {
        $('html, body').animate({
          scrollTop: target.offset().top
        }, 1000);
        return false;
      }
    }
  });
});

