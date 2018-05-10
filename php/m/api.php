<?php

function api_get($uri, $handler)
{
	if ($_SERVER['REQUEST_METHOD'] == 'GET')
		api_call($uri, $handler);
}

function api_post($uri, $handler)
{
	if ($_SERVER['REQUEST_METHOD'] == 'POST')
		api_call($uri, $handler);
}

function api_call($uri, $handler)
{
	if (preg_match("#^$uri$#", $_SERVER['REQUEST_URI'], $m))
	{
		foreach ($m as $k => $v) if (is_string($v)) $m[$k] = urldecode($v);
		if (is_callable($handler)) $handler($m);
		else require_once "tpl/$handler";
	}
}
