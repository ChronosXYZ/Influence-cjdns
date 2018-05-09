<h3>Контакты</h3>

<style>
	table  { border-collapse: collapse; }
	td, th { border: 1px solid #999; padding: 5px 10px; }
	th     { background: #EEE; }
	tr:hover { background: #EEE; }
</style>

<a href="new">Добавить</a>

<table>
<tr>
	<th>Адрес</th>
	<th>Ник</th>
	<th>email</th>
	<th>online</th>
	<th></th>
</tr>
<?foreach (db_search('contacts', []) as $a){?>
<tr>
	<td><a href="<?=urlencode($a['addr'])?>"><?=$a['addr']?></a></td>
	<td><?=$a['nickname']?></td>
	<td><?=$a['email']?></td>
	<td><?=(time() - @$a['time_online'] > TIME_ONLINE)?'нет':'да'?></td>
	<td><a href="./<?=$a['addr']?>/messages">сообщения</a></td>
</tr>
<?}?>
</table>
