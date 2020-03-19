import h5py
import numpy as np
import time
import os
current_milli_time = lambda: int(round(time.time() * 1000))

iterations = int(os.environ["ITERATIONS"])
size = int(os.environ["DATASET_SIZE"])

array = np.arange(size, dtype='int32') % 999999
array = array.astype('f4')

datasets = []

start = current_milli_time()
for i in range(0, iterations):
    f = h5py.File('file' + str(i), 'w')
    g = f.create_group('group')
    d = g.create_dataset('mydataset' + str(i), (size,), dtype='f4', data=array)
    datasets.append(d)

end = current_milli_time()
print("==== PUT " + str(end-start) + "ms")
time.sleep(30)
start = current_milli_time()
for i in range(0, iterations):
    dataset = datasets[i]
#    lgs = current_milli_time()
    array = dataset[()]
#    print(dataset[()][0])
#    variable = array[9::10]
#    lge = current_milli_time()
#    print("==== LOCAL SINGLE GET " + str(lge-lgs) + "ms")
#    fts = current_milli_time()
#    variable = array[array < 999999]
#    variable = array[array < 1]
#    fte = current_milli_time()
#    print("==== FILTER " + str(fte-fts) + "ms")

end = current_milli_time()
print("==== GET " + str(end-start) + "ms")
