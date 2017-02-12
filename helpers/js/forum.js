function make_bold (element) {
	make_tag(element, 'b', 1);
}

function make_italic (element) {
	make_tag(element, 'i', 1);
}

function make_underline (element) {
	make_tag(element, 'u', 1);
}

function make_quote (element) {
	make_tag(element, 'quote', 5);
}

function make_li (element) {
	make_tag(element, 'li', 2);
}

function make_list (element, type) {
	var textarea = document.getElementById(element);

	var len = textarea.value.length;
	var start = textarea.selectionStart;
	var end = textarea.selectionEnd;
	var selection = textarea.value.substring(start, end);

	var replace = '[' + type + ']\n\t[li]' + selection + '[/li]\n[/' + type + ']\n';
	textarea.value = textarea.value.substring(0,start) + replace + textarea.value.substring(end,len);
	textarea.focus();
	textarea.setSelectionRange(start+10, start+10+selection.length);
}

function make_tag (element, tag_content, tag_content_length){
	var textarea = document.getElementById(element);
	var starttag = '[' + tag_content + ']';
	var endtag = '[/' + tag_content + ']';

	var len = textarea.value.length;
	var start = textarea.selectionStart;
	var end = textarea.selectionEnd;
	var selection = textarea.value.substring(start, end);

	var replace = starttag + selection + endtag;
	textarea.value = textarea.value.substring(0,start) + replace + textarea.value.substring(end,len);
	textarea.focus();
	textarea.setSelectionRange(start+tag_content_length+2, start+tag_content_length+2+selection.length);
}

function quote_post (post_id) {
	var textarea = document.getElementById("new_post_content");
	var selection = document.getSelection();
	var newlines = textarea.value && textarea.value.slice(-2) != '\n\n'
		? '\n\n'
		: '';
	if (selection && selection != '') {
		textarea.value = textarea.value + newlines + '[quote=' + post_id + ']' + selection + '[/quote]\n\n';
	}
	else {
		var post_content_post_id = 'post_content_' + post_id;
		var str = window[post_content_post_id].value;
		var post_content = str.replace(/\[quote[\s\S]*\/quote\]\n\n/, '');
		textarea.value += newlines + '[quote=' + post_id + ']' + post_content + '[/quote]\n\n';
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