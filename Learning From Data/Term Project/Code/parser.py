from __future__ import print_function, division
import csv
import sys
from pprint import pprint

feature_intervals = {}

for i in xrange(1,10):
    feature_intervals['Class_'+str(i)] = [ [float("inf"),float("-inf")] for j in range(94) ]

with open(sys.argv[1]) as f:
    for index,row in enumerate(csv.reader(f)):
        if index == 0:
            continue
        for i in range(1,94):
            feature_intervals[row[-1]][i][0] = min(feature_intervals[row[-1]][i][0],int(row[i]))
            feature_intervals[row[-1]][i][1] = max(feature_intervals[row[-1]][i][1],int(row[i]))

print('id,Class_1,Class_2,Class_3,Class_4,Class_5,Class_6,Class_7,Class_8,Class_9')

with open(sys.argv[2]) as f:
    for index,row in enumerate(csv.reader(f)):
        if index == 0:
            continue
        cnt = [0]*10
        for i in xrange(1,94):
            for key,value in feature_intervals.items():
                if value[i][0] <= int(row[i]) <= value[i][1]:
                    cnt[int(key[-1])] += 1

        s = sum(cnt)
        cnt[0] = index
        for cl in xrange(1,10):
            cnt[cl] /= s
        print(','.join(map(str,cnt)))
