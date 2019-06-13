#! /bin/bash
docker rm -f rados 2>/dev/null
sudo rm -r /tmp/ceph/* 2>/dev/null
mkdir -p /tmp/ceph/etc /tmp/ceph/var
docker network create rados_net --subnet=172.2.0.0/16
docker run --rm --name rados -e MON_IP=`hostname -i` -e CEPH_PUBLIC_NETWORK=172.17.0.1/16 -e CEPH_DEMO_UID=1 --network=host -v /tmp/ceph/etc:/etc/ceph -v /tmp/ceph/var:/var/lib/ceph/ --privileged ceph/daemon demo
