import os
from io import BytesIO
import numpy
from minio import Minio
from minio.error import BucketAlreadyOwnedByYou, BucketAlreadyExists

ENV_ADDRESS = 'MINIO_ADDRESS'
ENV_ACCESS = 'MINIO_ACCESS_KEY'
ENV_SECRET = 'MINIO_SECRET_KEY'

ADDRESS = os.environ[ENV_ADDRESS]
ACCESS_KEY = os.environ[ENV_ACCESS]
SECRET_KEY = os.environ[ENV_SECRET]

if ADDRESS is None or ACCESS_KEY is None or SECRET_KEY is None:
	raise Exception('Please, set the environment variables {}, {}, {}'.format(ENV_ADDRESS, ENV_ACCESS, ENV_SECRET))

MINIO_CLIENT = Minio(ADDRESS, access_key=ACCESS_KEY, secret_key=SECRET_KEY, secure=False)

BUCKET = 'hdf5'

try:
	MINIO_CLIENT.make_bucket(BUCKET)
except BucketAlreadyOwnedByYou as err:
	pass
except BucketAlreadyExists as err:
	pass

def object_upload(name, obj):
	buf = BytesIO()
	numpy.save(buf, obj)
	tag = MINIO_CLIENT.put_object(BUCKET, name, buf, len(buf.getbuffer()))
	return tag

def object_download(name):
	buf = BytesIO(MINIO_CLIENT.get_object(BUCKET, name))
	buf.seek(0)
	return numpy.load(buf, allow_pickle=False)
