import h5py
import numpy as np
import time

#from dataclay import api


try:
    #api.init()
    dataclay = False
except:
    dataclay = False

current_milli_time = lambda: int(round(time.time() * 1000))

iterations = 10
size = 100

array = np.arange(size, dtype='f4')

datasets = []

start = current_milli_time()
for i in range(0, iterations):
    f = h5py.File('file' + str(i), 'w')
    g = f.create_group('group')
    d = g.create_dataset('mydataset' + str(i), (size,), dtype='f4', data=array)
    datasets.append(d)
    #print(d[()][2])

end = current_milli_time()
print("==== PUT " + str(end-start) + "ms")

start = current_milli_time()
if dataclay:
    for i in range(0, iterations):
        from h5app_ns.classes import Dataset
        dataset = api.DataClayObject.get_by_alias('file' +str(i) + '/group/mydataset' + str(i))
        print(dataset.data[()][2])
else:
    for i in range(0, iterations):
        print(i)
        dataset = datasets[i]
        print(dataset[()][2])
        
end = current_milli_time()
print("==== GET " + str(end-start) + "ms")

#api.finish()
