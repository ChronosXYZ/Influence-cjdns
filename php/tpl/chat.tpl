<h3>Сообщения</h3>

<iframe src="/messages/<?=$m['addr']?>" style="width: 600px; height: 400px;"></iframe>

<form method="POST" action="/messages/<?=$m['addr']?>">
	<input name="text" style="width: 300px">
	<input type="submit" value="Отправить">
</form>

<script>setInterval(function(){ document.querySelector('iframe').contentWindow.location.reload(true) }, 10000)</script>
