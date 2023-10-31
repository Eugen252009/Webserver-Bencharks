#! /bin/bash

((GO = $(wrk -c 3000 -t 16 http://127.0.0.1:8080 | grep "requests in 10" | awk {'print $1'})))
((JS = $(wrk -c 3000 -t 16 http://127.0.0.1:3000 | grep "requests in 10" | awk {'print $1'})))

if (($GO > $JS ))
then 
	echo -e "Go was $(($GO/$JS)) x faster\n go: $GO\n js: $JS"
else
	echo -e "JS was $(($JS/$GO)) x faster\n go: $GO\n js: $GO"
fi
