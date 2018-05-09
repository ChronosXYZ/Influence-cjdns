<?
	if ($m['addr'] == 'new')
		$action_name = 'Добавить';
	else
	{
		$action_name = 'Изменить';
		$a = db_search_one('dns', ['addr'=>$m['addr']]);
	}
?>
<style>
	form { white-space: pre; font-family: Courier New; }
</style>

<h2><?=$action_name?> запись</h2>
<form action="./<?=$m['addr']?>" method="POST">
	Адрес: <input name="<?=$x='addr'?>"   value="<?=@$a[$x]?>" required>
	Домен: <input name="<?=$x='domain'?>" value="<?=@$a[$x]?>" required>
	       <input type="submit" value="<?=$action_name?>"> <?if ($m['addr'!='new']){?><input type="submit" name="delete" value="Удалить"><?}?>
</form>
