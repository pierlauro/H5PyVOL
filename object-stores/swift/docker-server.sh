#!/bin/bash
docker network create swift_net --subnet=172.1.0.0/16
docker rm -f SWIFT_DATA swift 2>/dev/null
docker run -v /srv --name SWIFT_DATA busybox
docker run --ip 172.1.0.2 --name swift --net swift_net --restart=always --volumes-from SWIFT_DATA -t morrisjobke/docker-swift-onlyone
