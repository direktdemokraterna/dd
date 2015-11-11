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

function get_text_to_quote (post_id) {
	var post_content_post_id = 'post_content_' + post_id;
	var str = document.getElementById(post_content_post_id).value;
	return str;
}

function quote_post (post_id) {
	var textarea = document.getElementById("new_post_content");
	var text_to_quote = get_text_to_quote(post_id);
	var newlines = textarea.value.length ? '\n\n' : '';
	textarea.value += newlines + '[quote=' + post_id + ']' + text_to_quote + '[/quote]\n\n';
	window.setTimeout(function() { textarea.focus(); },10);
}