<h3>DNS записи</h3>

<a href="new">Добавить</a>

<table>
<tr>
	<th>Адрес</th>
	<th>Домен</th>
</tr>
<?foreach (db_search('dns', []) as $a){?>
<tr>
	<td><a href="<?=urlencode($a['addr'])?>"><?=$a['addr']?></a></td>
	<td><?=$a['domain']?></td>
</tr>
<?}?>
</table>
