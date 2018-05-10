<?php

function send($data)
{
	$data_url = http_build_query ($data);
	$data_len = strlen ($data_url);

	$context = stream_context_create([
		'http' => ['method'=>'POST','header'=>"Connection: close\r\nContent-Length: $data_len\r\n", 'content'=>$data_url]
	]);

	$res = json_decode(@file_get_contents('http://'.$data['to'].'/messages/', false, $context), true);
	return !empty($res);
}
