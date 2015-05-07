<?php

$array = json_decode('{"1":-1,"3":3}', true);

var_dump($array);

echo "<br><br>";

arsort($array, SORT_NUMERIC);

//usort($array, function($a, $b) {
//    return $b['rank'] - $a['rank'];
//});

var_dump($array);