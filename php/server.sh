#!/bin/sh

source ./server.conf
php -S $IP:8000 index.php
