import os
from io import BytesIO
import numpy as np
from swiftclient.client import Connection

ENV_SWIFT='SWIFT_IP'
SWIFT_IP = os.environ[ENV_SWIFT]
if SWIFT_IP is None:
	raise Exception('Please set the environment variable ' + SWIFT_IP)

## Reading swift configuration from properties file
CONF_FILE="/".join(__file__.split("/")[:-1]) + '/swift.properties'
with open(CONF_FILE, 'r') as conf_file:
	config = {prop: value for prop, value in [prop.split("=") for prop in list(filter(lambda x: '=' in x, conf_file.read().split("\n")))]}

default_authurl = config['auth_url'].replace('$$SWIFT_IP$$', SWIFT_IP)
default_key = config['key'] 
default_user = config['user']
default_auth_version = config['auth_version']

def swift_connect():
	conn = Connection(
		authurl = default_authurl,
		user = default_user,
		key = default_key,
		auth_version = default_auth_version,
		os_options=None
	)
	return conn

conn = swift_connect()

def swift_object_upload(container, obj_name, obj):
	container.replace('/','\\')
	conn.put_container(container) ## TODO move out (in group declaration?)
	buf = BytesIO()
	np.save(buf, obj)
	buf.seek(0)
	conn.put_object(
		container,
		obj_name,
		contents=buf.read()
	)

def swift_object_download(container, sciobj_name):
	container.replace('/','\\')
	res, obj=conn.get_object(container,sciobj_name)
	buf = BytesIO(obj)
	return np.load(buf, allow_pickle=False)

