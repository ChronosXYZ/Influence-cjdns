<?php

function request($x)
{
	return array_intersect_key($_REQUEST, array_fill_keys(explode(',', $x), 1));
}

function redirect($x = NULL)
{
	if (is_null($x)) $x = $_SERVER['REQUEST_URI'];
	header('Location: '.$x);
	exit;
}
