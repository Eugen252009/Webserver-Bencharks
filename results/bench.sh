#! /bin/bash

((GO = $(wrk -c 3000 -t 16 http://127.0.0.1:8080 | grep "requests in 10" | awk {'print $1'})))
((express = $(wrk -c 3000 -t 16 http://127.0.0.1:3000 | grep "requests in 10" | awk {'print $1'})))
((fastify = $(wrk -c 3001 -t 16 http://127.0.0.1:3000 | grep "requests in 10" | awk {'print $1'})))

echo "Go was $(($GO/$express)) x faster then express"
echo -e "go:\t\t\t$GO"
echo -e "js express:\t\t$express"
echo -e "js fastify:\t\t$fastify"

