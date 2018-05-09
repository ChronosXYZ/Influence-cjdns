<?php

function db_insert($db, $a)
{
	$data = db_get($db);
	$data[] = $a;
	db_save($db, $data);
}

function db_update($db, $a, $filter)
{
	$data = db_get($db);
	foreach (db_search($db, $filter) as $id => $_)
		$data[$id] = $a + $data[$id];
	db_save($db, $data);
}

function db_delete($db, $filter)
{
	$data = db_get($db);
	foreach (db_search($db, $filter) as $id => $_)
		unset($data[$id]);
	db_save($db, $data);
}

function db_search($db, $filter = [])
{
	$res = [];
	foreach (db_get($db) as $id => $a)
	{
		foreach ($filter as $k => $v)
			if ($a[$k] != $v) continue 2;
		$res[$id] = $a;
	}
	return $res;
}

function db_search_one($db, $filter)
{
	$res = db_search($db, $filter);
	foreach ($res as $a) return $a;
	return [];
}

function db_get($db)
{
	$fname = "./db/$db.json";
	if (!file_exists($fname)) return [];
	$db = @json_decode(@file_get_contents($fname), true);
	return $db ?: [];
}

function db_save($db, $data)
{
	$fname = "./db/$db.json";
	if (empty($data)) unlink($fname);
	else
	{
		$st = json_encode($data, JSON_UNESCAPED_UNICODE);
		if (!file_exists($x = dirname($fname))) mkdir($x, 0777, true);
		if ($st) file_put_contents($fname, $st);
	}
}
