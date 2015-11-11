function isNullOrWhitespace(str) {
	return str && !(/^\s*$/).test(str) ? false : true;
}

function replaceAll(search, replacement, str) {
	return str.split(search).join(replacement)
}
