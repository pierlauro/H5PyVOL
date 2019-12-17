import h5py
import numpy as np
import time

current_milli_time = lambda: int(round(time.time() * 1000))

iterations = 1
size = 26214400

array = np.arange(size, dtype='f4')

datasets = []

start = current_milli_time()
for i in range(0, iterations):
    f = h5py.File('file' + str(i), 'w')
    g = f.create_group('group')
    d = g.create_dataset('mydataset' + str(i), (size,), dtype='f4', data=array)
    datasets.append(d)

end = current_milli_time()
print("==== PUT " + str(end-start) + "ms")

start = current_milli_time()
for i in range(0, iterations):
    dataset = datasets[i]
    print(dataset[()][2])
        
end = current_milli_time()
print("==== GET " + str(end-start) + "ms")

