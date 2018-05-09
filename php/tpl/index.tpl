<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
</head>
<body>
	<p>Ваш IP: <?=$_SERVER['HTTP_HOST']?></p>

	<nav>
		<a href="/contacts/">Контакты</a>
	</nav>
<?
	api_get('/contacts/',               'contacts.tpl');
	api_get('/contacts/(?<addr>[^/]+)', 'contact.tpl');
	api_get('/contacts/(?<addr>[^/]+)/messages', 'chat.tpl');
?>

	<iframe id="ping" style="display: none"></iframe>
	<script>setInterval(function(){ document.querySelector('#ping').src = '/contacts/ping'; }, 5000)</script>
</body>
</html>
