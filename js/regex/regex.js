<script type="text/javascript">
function r_test(regex, s) {
    var p = document.getElementById('r_test');
    var result = document.createTextNode(
        regex.test(s)
            ? 'Match!'
            : 'Not match!'
    );
    p.replaceChild(result, p.lastChild);
}
 
function r_exec(regex, s) {
    var p = document.getElementById('r_exec');
    var matches = regex.exec(s);
    var result = document.createTextNode(
        matches
            ? matches.toString()
            : 'Not match!'
    );
    p.replaceChild(result, p.lastChild);
}
 
function s_split(regex, s) {
    var p = document.getElementById('s_split');
    var splits = s.split(regex);
    var result = document.createTextNode(
        splits
            ? splits.toString()
            : 'Not match!'
    );
    p.replaceChild(result, p.lastChild);
}
 
function regexp_match() {
    var p = document.getElementById('regex');
 
    var inputString = document.getElementById('inputString').value;
    var patternString = document.getElementById('patternString').value;
    var regexFlags = document.getElementsByName('regexFlags');
    var flags = '';
    for (i = regexFlags.length - 1; i >= 0; --i) {
        if (regexFlags[i].checked) {
            flags += regexFlags[i].value;
        }
    }
 
    var regex = new RegExp(patternString, flags);
    p.replaceChild(document.createTextNode(regex.toString()), p.lastChild);
 
    r_test(regex, inputString);
    r_exec(regex, inputString);
    s_split(regex, inputString);
}
</script>
