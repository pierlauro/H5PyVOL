from dataclay.api import init
init()

from h5app_ns.classes import File

class DataClayVOL():
    def __init__(self):
        self.files = {}

    def H5VL_python_file_create(self, name, flags, fcpl_id, fapl_id, dxpl_id, req):
        print('Creating file ' + name)
        new_file = File(name)
        self.files[name] = new_file
        return new_file
