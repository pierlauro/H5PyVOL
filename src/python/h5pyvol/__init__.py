from abc import ABC, abstractmethod

class H5Object(ABC):
	@abstractmethod
	def __init__(self, name: str):
		pass
	
	@abstractmethod
	def H5VL_python_object_close(self, dxpl_id, req):
		pass

class H5Dataset(H5Object, ABC):
	@abstractmethod
	def __init__(self, name: str, array: list):
		pass

	@abstractmethod
	def H5VL_python_dataset_read(self, mem_type_id, mem_space_id, file_space_id, xfer_plist_id, req):
		pass

	@abstractmethod
	def H5VL_python_dataset_write(self, mem_type_id, mem_space_id, file_space_id, xfer_plist_id, buf, req):
		pass

class H5Group(H5Object, ABC):
	@abstractmethod
	def __init__(self, name: str):
		pass
	
	@abstractmethod
	def H5VL_python_dataset_create(self, loc_params, name: str, dcpl_id, dapl_id, dxpl_id, req) -> H5Dataset:
		pass

	@abstractmethod
	def H5VL_python_dataset_open(self, loc_params, name: str, dapl_id, dxpl_id, req) -> H5Dataset:
		pass

	#@abstractmethod
	def H5VL_python_dataset_get(self, get_type, dxpl_id, req, arguments):
		pass

	#@abstractmethod
	def H5VL_python_dataset_specific(self, specific_type, dxpl_id, req, arguments):
		pass

        #@abstractmethod
	def H5VL_python_dataset_optional(self, dxpl_id, req, arguments):
		pass

class H5File(H5Object, ABC):
	@abstractmethod
	def __init__(self, name: str):
		pass
	
	@abstractmethod
	def H5VL_python_group_create(self, loc_params, name: str, gcpl_id, gapl_id, dxpl_id, req) -> H5Group:
		pass

	@abstractmethod
	def H5VL_python_group_open(self, loc_params, name: str, gapl_id, dxpl_id, req) -> H5Group:
		pass

	#@abstractmethod
	def H5VL_python_group_get(self, get_type, dxpl_id, req, arguments):
		pass

	#@abstractmethod
	def H5VL_python_group_specific(self, specific_type, dxpl_id, req, arguments):
		pass

        #@abstractmethod
	def H5VL_python_group_optional(self, dxpl_id, req, arguments):
		pass

class H5VOL(ABC):
	@abstractmethod
	def __init__(self):
		pass

	@abstractmethod
	def H5VL_python_file_create(self, name: str, flags, fcpl_id, fapl_id, dxpl_id, req) -> H5File:
		pass

	@abstractmethod
	def H5VL_python_file_open(self, name: str, flags, fapl_id, dxpl_id, req) -> H5File:
		pass

	#@abstractmethod
	def H5VL_python_file_get(self, get_type, dxpl_id, req, arguments):
		pass

	#@abstractmethod
	def H5VL_python_file_specific(self, specific_type, dxpl_id, req, arguments):
		pass

        #@abstractmethod
	def H5VL_python_file_optional(self, dxpl_id, req, arguments):
		pass
