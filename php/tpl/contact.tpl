<?
	if ($m['addr'] == 'new')
		$action_name = 'Добавить';
	else
	{
		$action_name = 'Изменить';
		$a = db_search_one('contacts', ['addr'=>$m['addr']]);
	}
?>
<style>
	form { white-space: pre; font-family: Courier New; }
</style>

<h2><?=$action_name?> контакт</h2>
<form action="./<?=$m['addr']?>" method="POST">
	Адрес: <input name="<?=$x='addr'?>"     value="<?=@$a[$x]?>" required>
	Ник:   <input name="<?=$x='nickname'?>" value="<?=@$a[$x]?>">
	email: <input name="<?=$x='email'?>"    value="<?=@$a[$x]?>" type="email">
	       <input type="submit" value="<?=$action_name?>"> <?if ($m['addr'!='new']){?><input type="submit" name="delete" value="Удалить"><?}?>
</form>
