from CPyVOL import H5Object, H5Dataset, H5Group, H5File, H5VOL
from . import rados_functions

class Object(H5Object):
	def __init__(self, name: str):
		self.name: str = name
		self.open: bool = True

	def H5VL_python_object_close(self, dxpl_id, req):
		self.open = False

class Dataset(H5Dataset, Object):
	def __init__(self, name: str, array: list):
		Object.__init__(self, name)

	def H5VL_python_dataset_read(self, mem_type_id, mem_space_id, file_space_id, xfer_plist_id, req):
		arr = rados_functions.object_download(self.name, self.size)
		print('Reading dataset ' + self.name + '=' + str(arr))
		return arr

	def H5VL_python_dataset_write(self, mem_type_id, mem_space_id, file_space_id, xfer_plist_id, buf, req):
		print('Writing dataset ' + self.name + ' = ' + str(buf))
		self.size = rados_functions.object_upload(self.name, buf)

class Group(H5Group, Object):
	def __init__(self, name: str):
		Object.__init__(self, name)
		self.datasets: dict = {}

	def H5VL_python_dataset_create(self, loc_params, name: str, dcpl_id, dapl_id, dxpl_id, req) -> Dataset:
		print('Creating dataset ' + name)
		dataset = Dataset(name, None)
		self.datasets[name] = dataset
		return dataset

	def H5VL_python_dataset_open(self, loc_params, name: str, dapl_id, dxpl_id, req) -> Dataset:
		print('Opening dataset ' + name)
		if name in self.datasets:
			return self.datasets[name]
		return self.H5VL_python_dataset_create(loc_params, name, 0, dapl_id, dxpl_id, req)

class File(H5File, Object):
	def __init__(self, name: str):
		Object.__init__(self, name)
		self.groups: dict = {'/': Group('/')}

	def H5VL_python_group_create(self, loc_params, name: str, gcpl_id, gapl_id, dxpl_id, req) -> Group:
		print('Creating group ' + name)
		group = Group(name)
		self.groups[name] = group
		return group

	def H5VL_python_group_open(self, loc_params, name: str, gapl_id, dxpl_id, req) -> Group:
		print('Opening group ' + name)
		if name in self.groups:
			return self.groups[name]
		return self.H5VL_python_group_create(loc_params, name, 0, gapl_id, dxpl_id, req)

class RadosVOL(H5VOL):
	def __init__(self):
		self.files: dict = {}

	def H5VL_python_file_create(self, name: str, flags, fcpl_id, fapl_id, dxpl_id, req) -> File:
		print('Creating file ' + name)
		new_file = File(name)
		self.files[name] = new_file
		return new_file


	def H5VL_python_file_open(self, name: str, flags, fapl_id, dxpl_id, req) -> Group:
		print('Opening file ' + name)
		return self.files[name]
