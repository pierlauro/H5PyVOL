from datetime import datetime
import numpy
import rados, sys
import io

cluster = rados.Rados(conffile='/etc/ceph/ceph.conf')
print("\nlibrados version: " + str(cluster.version()))
print("Will attempt to connect to: " + str(cluster.conf_get('mon initial members')))

cluster.connect()
print("\nCluster ID: " + str(cluster.get_fsid()))
print("\n\nCluster Statistics")
print("==================")

cluster_stats = cluster.get_cluster_stats()
for key in cluster_stats.keys():
	print(str(key) + " " + str(cluster_stats[key]))

ioctx = cluster.open_ioctx("cephfs_data")

def object_upload(name, obj):
	f = io.BytesIO()
	numpy.save(f, obj)
	ioctx.write_full(name, f.getvalue())
	return len(f.getvalue()) ## TODO calculate size outside

def object_download(name, size):
	f = io.BytesIO(ioctx.read(name, size))
	f.seek(0)
	return numpy.load(f, allow_pickle=False)

#ioctx.close()
