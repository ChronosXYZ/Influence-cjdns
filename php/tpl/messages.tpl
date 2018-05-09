<?php
$contacts = [];
foreach (db_search('contacts') as $a) $contacts[$a['addr']] = $a['nickname'];
$contacts[$_SERVER['HTTP_HOST']] = 'Я';
?>

<?$a = array_merge(db_search('messages/'.$m['addr']), db_search('undelivered/'.$m['addr']));?>
<?if (empty($a)) {?>
<p>Список сообщений пуст</p>
<?} else

foreach ($a as $a){?>
<?=date('H:i:s', $a['timestamp'])?> <b><?=$contacts[$a['from']]?></b>: <?=$a['text']?>
<?if (empty($a['received'])) echo ' <small><i>(не доставлено)</i></small>';?>
<br>
<?}?>

<?exit;?>
