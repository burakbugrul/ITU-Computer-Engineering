from __future__ import print_function, division
import csv
import sys
from sklearn.neighbors import KNeighborsClassifier
from sklearn.neural_network import MLPClassifier
from sklearn import tree
from sklearn.ensemble import RandomForestClassifier
import numpy as np
from pprint import pprint

import warnings
from sklearn.exceptions import NonBLASDotWarning
warnings.simplefilter('always', NonBLASDotWarning)

def warn(*args, **kwargs):
    pass
import warnings
warnings.warn = warn

X = []
y = []

with open("train.csv") as f:
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
summer = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(1001, 201), random_state=1)
clf2 = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(101, 51), random_state=1)
clf = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(101, 51), random_state=34)
#clf = RandomForestClassifier(max_depth = 4)
#clf = RandomForestClassifier(max_depth = 35)

clf = clf.fit(X, y)
clf2 = clf2.fit(X, y)

dar=[]#birinci clsnin sonucu
dar2=[]#ikinci clsnin sonucu
#sonuçlarını alıp koyuyor
with open("train.csv") as f:
    for index,row in enumerate(csv.reader(f)):
        if index == 0:
            continue
        dar.append(list(map(float,clf.predict_proba(list(map(int,row[1:94])))[0])))
        dar2.append(list(map(float,clf2.predict_proba(list(map(int,row[1:94])))[0])))

#birinci clsnin çıktısının yanına ikincinin sonuçlarını ekliyor
#9 sütunluk iki matrisi yan yana koyuyor 18 sütunlu oluyor
XX=dar
for i in range(0,len(XX)):
    for j in dar2[i]:
        XX[i].append(float(j))
#matrisleri yan yana eklemek yerine ortalamaları alınabilir - denenmeli
#matrisler yan yana koyulup dimension reduction uygulanabilir(pca) - denenmeli

#iki clsnin sonucunu başka bir clsyi train etmek için kullanıyor
summer = summer.fit(XX, y)

out=open("out.csv", "w")
print('id,Class_1,Class_2,Class_3,Class_4,Class_5,Class_6,Class_7,Class_8,Class_9', file=out)
with open("test.csv") as f:
    for index,row in enumerate(csv.reader(f)):
        if index == 0:
            continue
        res = [row[0]]
        #ar = list(map(str,neigh.predict_proba(list(map(int,row[1:94])))[0]))
        ar = list(map(float,clf.predict_proba(list(map(int,row[1:94])))[0]))
        ar2 = list(map(float,clf2.predict_proba(list(map(int,row[1:94])))[0]))

        #sonuçları yan yana koyup summera sok
        heyyo = ar
        for j in ar2:
            heyyo.append(float(j))
        ar3 = list(map(str,summer.predict_proba(heyyo)[0]))

        for j in ar3:
            res.append(j)
        print(','.join(res), file=out)
