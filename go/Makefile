tag =	$(shell git log -1 --pretty=%h)
repository=192.168.178.2:9006/service-checker:
buildTAG=$(repository)$(tag)
latestTAG=$(repository)latest
BUILD_TIMESTAMP=$( date '+%F_%H:%M:%S' )
build:
	go build -o output ./cmd/main/*
docker:
	git add -A
	git commit -m "pushing to REPO"
	docker build -t $(buildTAG) .
	docker build -t $(latestTAG) .
	docker push $(buildTAG)   
	docker push $(latestTAG) 
run:
	go run ./cmd/main/*

