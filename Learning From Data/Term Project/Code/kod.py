from __future__ import print_function, division
import csv
import sys
from sklearn.neighbors import KNeighborsClassifier
from sklearn.neural_network import MLPClassifier
from sklearn import tree
from sklearn.ensemble import RandomForestClassifier
import numpy as np
from pprint import pprint

def warn(*args, **kwargs):
    pass
import warnings
warnings.warn = warn

X = []
y = []

with open(sys.argv[1]) as f:
    for index,row in enumerate(csv.reader(f)):
        if index == 0:
            continue
        X.append(list(map(int,row[1:94])))
        y.append(int(row[-1][-1]))

#y = np.array(y).reshape((1, -1))
#neigh = KNeighborsClassifier(n_neighbors=11)
#neigh.fit(X,y)

#clf = tree.DecisionTreeClassifier()
#clf = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(5, 2), random_state=1)
#clf = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(6, 3), random_state=1)
#clf = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(8, 5), random_state=1)
#clf = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(25, 10), random_state=1)
#clf = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(1001, 201), random_state=1)
#clf = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(101, 51), random_state=1)
#clf = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(101, 51), random_state=34)
#clf = RandomForestClassifier(max_depth = 4)
clf = RandomForestClassifier(max_depth = 35)
clf = clf.fit(X, y)

print('id,Class_1,Class_2,Class_3,Class_4,Class_5,Class_6,Class_7,Class_8,Class_9')

with open(sys.argv[2]) as f:
    for index,row in enumerate(csv.reader(f)):
        if index == 0:
            continue
        res = [row[0]]
        #ar = list(map(str,neigh.predict_proba(list(map(int,row[1:94])))[0]))
        ar = list(map(str,clf.predict_proba(list(map(int,row[1:94])))[0]))
        for j in ar:
            res.append(j)
        print(','.join(res))
