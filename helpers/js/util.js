function isNullOrWhitespace(str) {
	return str && !(/^\s*$/).test(str) ? false : true;
}

function replaceAll(search, replacement, str) {
	return str.split(search).join(replacement)
}

function html_to_bbcode(html_str) {
	bbcode_str = html_str;
	bbcode_str = replaceAll('<br>', '\r\n', bbcode_str);
	bbcode_str = replaceAll('<b>', '[b]', bbcode_str);
	bbcode_str = replaceAll('<i>', '[i]', bbcode_str);
	bbcode_str = replaceAll('<u>', '[u]', bbcode_str);
	bbcode_str = replaceAll('</b>', '[/b]', bbcode_str);
	bbcode_str = replaceAll('</i>', '[/i]', bbcode_str);
	bbcode_str = replaceAll('</u>', '[/u]', bbcode_str);
	return bbcode_str;
}
