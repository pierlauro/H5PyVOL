import h5py
import numpy as np
import time
import os
from dataclay import api


api.init()

current_milli_time = lambda: int(round(time.time() * 1000))

iterations = int(os.environ['ITERATIONS'])
size = int(os.environ['DATASET_SIZE'])

array = np.arange(size, dtype='int32') % 999999
array = array.astype('f4')

datasets = []

start = current_milli_time()
for i in range(0, iterations):
    f = h5py.File('file' + str(iterations) + str(i), 'w')
    g = f.create_group('group')
    d = g.create_dataset('mydataset' + str(i), (size,), dtype='f4', data=array)
    datasets.append(d)
    #print(d[()][2])

end = current_milli_time()
print("==== PUT " + str(end-start) + "ms")

time.sleep(150)
start = current_milli_time()

for i in range(0, iterations):
    from h5app_ns.classes import Dataset
    dataset = api.DataClayObject.get_by_alias('file' + str(iterations) + str(i) + '/group/mydataset' + str(i))
#    print(dataset.data[()][0])
#    st =  current_milli_time()
#    a = dataset.filterdataset(4)
#    a = dataset.minimum(999999)
#    a = dataset.column(9, 10)
#    a = dataset.column(4, 5)
    a = dataset.row(24903680)
#    en =  current_milli_time()
#    print("==== LOCAL FILTERING TIME " + str(en-st) + "ms" + " | len = " + str(len(a)) )
    print("==== len(a) = " + str(len(a)) )

end = current_milli_time()
print("==== GET " + str(end-start) + "ms")
