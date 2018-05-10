<?php

api_get('/ping', function(){
	$a = ['timestamp'=>time(), 'addr'=>$_SERVER['HTTP_HOST']];
	echo json_encode($a);
	exit;
});

api_get('/contacts/ping', function(){
	foreach (db_search('contacts') as $a)
	if ($a['addr'] != $_SERVER['HTTP_HOST']) // COMMENT: сами себе не отправляем
	{
		if (time() - @$a['time_ping'] > TIME_PING)
		{
			$st = @file_get_contents('http://'.$a['addr'].'/ping');
			$json = json_decode($st, true);
			$x = $json ? ['time_online' => time()] : [];
			db_update('contacts', ['time_ping' => time()] + $x, ['addr'=>$a['addr']]);
		}
		// если на связи - пытаемся дотправить сообщения
		if (time() - $a['time_online'] < TIME_ONLINE)
		{
			$addr = $a['addr'];
			foreach (db_search("undelivered/$addr") as $a)
			if (send($a))
			{
				db_insert("messages/$addr", $a + ['received'=>time()]);
				db_delete("undelivered/$addr", ['timestamp'=>$a['timestamp']]);
			} else break;
		}
		if (!empty($data)) $a['messages'] = $data;
	}
	exit;
});

api_get('/messages/(?<addr>[^/]+)',          'messages.tpl');

if ($_SERVER['REQUEST_METHOD'] != 'POST') return;

api_post('/contacts/(?<addr>[^/]+)', function($m){
	if (empty($_REQUEST['addr'])) die('Не указан адрес!');
	$addr = $m['addr'];
	$x = db_search('contacts', $addr == 'new' ? request('addr') : ['addr'=>$addr]);
	if ($addr == 'new')
	{
		if (!empty($x)) die('Такой адрес уже есть в базе!');
		db_insert('contacts', request('addr,nickname,email'));
		redirect('/contacts/');
	} else {
		if (request('delete'))
		{
			db_delete('contacts', ['addr'=>$addr]);
			redirect('/contacts/');
		}
		else
			db_update('contacts', request('addr,nickname,email'), ['addr'=>$addr]);
	}
});

api_post('/messages/(?<addr>[^/]+)', function($m){
	$a = request('text') + ['from'=>$_SERVER['HTTP_HOST'], 'to'=>$m['addr'], 'timestamp'=>time()];
	if (send($a))
		db_insert('messages/'.$m['addr'], $a + ['received'=>time()]);
	else
		db_insert('undelivered/'.$m['addr'], $a);
	redirect($_SERVER['HTTP_REFERER']);
});

api_post('/messages/', function($m){
	$a = request('from,to,text,timestamp');
	if ($a['to'] == $_SERVER['HTTP_HOST'])
	{
		db_insert('messages/'.$a['from'], $a + ['received'=>time()]);
		$res = ['received'=>time()];
		echo json_encode($res);
	}
	exit;
});

redirect();
