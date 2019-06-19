from dataclay.DataClayObject import DataClayObject
from dataclay.DataClayObjMethods import dclayMethod

class Dataset(DataClayObject):
    '''
    @ClassField name str
    @ClassField data numpy.ndarray
    '''

    @dclayMethod(name='str')
    def __init__(self, name):
        self.name = name
        self.make_persistent(alias=name)

    @dclayMethod(_local=True, mem_type_id='int', mem_space_id='int', file_space_id='int', xfer_plist_id='int', req='int')
    def H5VL_python_dataset_read(self, mem_type_id, mem_space_id, file_space_id, xfer_plist_id, req):
        #print('Reading dataset ' + self.name + '=' + str(self.data))
        return self.data

    @dclayMethod(mem_type_id='int', mem_space_id='int', file_space_id='int', xfer_plist_id='int', buf='numpy.ndarray', req='int')
    def H5VL_python_dataset_write(self, mem_type_id, mem_space_id, file_space_id, xfer_plist_id, buf, req):
        #print('Writing dataset ' + self.name + ' = ' + str(buf))
        self.data = buf


    @dclayMethod(dxpl_id='int', req='int')
    def H5VL_python_object_close(self, dxpl_id, req):
        pass

class Group(DataClayObject):
    '''
    @ClassField name str
    @ClassField datasets dict
    '''

    @dclayMethod(name='str')
    def __init__(self, name):
        self.name = name
        self.datasets = {}
        self.make_persistent(alias=name)

    @dclayMethod(loc_params='int', name='str', dcpl_id='int', dapl_id='int', dxpl_id='int', req='int')
    def H5VL_python_dataset_create(self, loc_params, name, dcpl_id, dapl_id, dxpl_id, req):
        #if name in self.datasets:
        #    raise Exception('The dataset ' + name + 'already exists')
        unique_name = self.name + '/' + name
        dataset = Dataset(unique_name)
        self.datasets[name] = dataset
        return dataset
    
    @dclayMethod(loc_params='int', name='str', dapl_id='int', dxpl_id='int', req='int')
    def H5VL_python_dataset_open(self, loc_params, name, dapl_id, dxpl_id, req):
        print('Opening dataset ' + name)
        if name in self.datasets:
            return self.datasets[name]
        return self.H5VL_python_dataset_create(loc_params, name, 0, dapl_id, dxpl_id, req)

    @dclayMethod(dxpl_id='int', req='int')
    def H5VL_python_object_close(self, dxpl_id, req):
        pass

class File(DataClayObject):
    '''
    @ClassField name str
    @ClassField groups dict
    '''

    @dclayMethod(name='str')
    def __init__(self, name):
        self.name = name
        self.groups = {}
        self.make_persistent(alias=name)
    
    @dclayMethod(loc_params='int', name='str', gcpl_id='int', gapl_id='int', dxpl_id='int', req='int')
    def H5VL_python_group_create(self, loc_params, name, gcpl_id, gapl_id, dxpl_id, req):
        if name in self.groups:
            raise Exception('The dataset ' + name + 'already exists')
        unique_name = self.name + '/' + name
        print("Creating group " + unique_name)
        group = Group(unique_name)
        self.groups[name] = group
        return group

    @dclayMethod(loc_params='int', name='str', gapl_id='int', dxpl_id='int', req='int')
    def H5VL_python_group_open(self, loc_params, name: str, gapl_id, dxpl_id, req):
        print('Opening group ' + name)
        if name in self.groups:
            return self.groups[name]
        return self.H5VL_python_group_create(loc_params, name, 0, gapl_id, dxpl_id, req)

    @dclayMethod(dxpl_id='int', req='int')
    def H5VL_python_object_close(self, dxpl_id, req):
        pass
