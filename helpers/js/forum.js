function make_bold (element) {
	var textarea = document.getElementById(element);

	var len = textarea.value.length;
	var start = textarea.selectionStart;
	var end = textarea.selectionEnd;
	var selection = textarea.value.substring(start, end);

	if (selection.length > 0) {
		var replace = '[b]' + selection + '[/b]';
		textarea.value = textarea.value.substring(0,start) + replace + textarea.value.substring(end,len);
	}
	else {
		textarea.value = textarea.value + '[b][/b]';
	}
}

function make_italic (element) {
	var textarea = document.getElementById(element);

	var len = textarea.value.length;
	var start = textarea.selectionStart;
	var end = textarea.selectionEnd;
	var selection = textarea.value.substring(start, end);

	if (selection.length > 0) {
		var replace = '[i]' + selection + '[/i]';
		textarea.value = textarea.value.substring(0,start) + replace + textarea.value.substring(end,len);
	}
	else {
		textarea.value = textarea.value + '[i][/i]';
	}
}

function make_underline (element) {
	var textarea = document.getElementById(element);

	var len = textarea.value.length;
	var start = textarea.selectionStart;
	var end = textarea.selectionEnd;
	var selection = textarea.value.substring(start, end);

	if (selection.length > 0) {
		var replace = '[u]' + selection + '[/u]';
		textarea.value = textarea.value.substring(0,start) + replace + textarea.value.substring(end,len);
	}
	else {
		textarea.value = textarea.value + '[u][/u]';
	}
}

function quote_post (post_id) {
	var textarea = document.getElementById("new_post_content");

	var selection = document.getSelection();

	if (textarea.value.length == 0 || textarea.value.slice(-2) == '\n\n'){
		var newlines = '';
	}
	else {
		var newlines = '\n\n';
	}

	if (selection && selection != '') {
		textarea.value = textarea.value + newlines + '[quote=' + post_id + ']' + selection + '[/quote]\n\n';
	}
	else {
		var post_content_post_id = 'post_content_' + post_id;
		var str = window[post_content_post_id].value;
		var post_content = str.replace(/\[quote[\s\S]*\/quote\]\n\n/, '');

		textarea.value = textarea.value + newlines + '[quote=' + post_id + ']' + post_content + '[/quote]\n\n';
	}

	window.setTimeout(function() { textarea.focus(); },10);
	textarea.focus();
}

function focus_on_textarea () {
	var textarea = document.getElementById("new_post_content");	
	textarea.focus();
}

function focus_on_new_topic_title () {
	var topic_title = document.getElementById("new_topic_title");	
	topic_title.focus();
}