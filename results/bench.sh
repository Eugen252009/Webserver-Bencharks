#! /bin/bash

((GO = $(wrk -c 160 -t 16 http://127.0.0.1:8080 | grep "requests in 10" | awk {'print $1'})))
((express = $(wrk -c 160 -t 16 http://127.0.0.1:3000 | grep "requests in 10" | awk {'print $1'})))
((fastify = $(wrk -c 160 -t 16 http://127.0.0.1:3000 | grep "requests in 10" | awk {'print $1'})))
((c = $(wrk -c 160 -t 16 http://127.0.0.1:8081 | grep "requests in 10" | awk {'print $1'})))

echo -e "go:\t\t$GO"
echo -e "js-express:\t$express"
echo -e "js-fastify:\t$fastify"
echo -e "c:\t\t$c"

