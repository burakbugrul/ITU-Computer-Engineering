#Colorless green ideas
#Mertcan Yasakçı - 150140051
#Burak Buğrul - 150140015

import csv
from sklearn.neural_network import MLPClassifier
import numpy as np

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

summer = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(1001, 201), random_state=1)
clf2 = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(101, 51), random_state=34)
clf = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(101, 51), random_state=1)

clf = clf.fit(X, y)
clf2 = clf2.fit(X, y)

dar=[]#birinci clsnin sonucu
dar2=[]#ikinci clsnin sonucu
#sonuçlarını alıp koyuyor
for i in range(len(X)):
    dar2.append(list(map(float, clf2.predict_proba(list(map(int, X[i])))[0])))
    dar.append(list(map(float, clf.predict_proba(list(map(int, X[i])))[0])))

XX=np.concatenate((np.array(dar),np.array(dar2)),axis=1)
XX=XX.tolist()

#iki clsnin sonucunu başka bir clsyi train etmek için kullanıyor
summer = summer.fit(XX, y)

out=open("out.csv", "w")
print('id,Class_1,Class_2,Class_3,Class_4,Class_5,Class_6,Class_7,Class_8,Class_9', file=out)

Xtest = []
y = []
with open("test.csv") as f:
    for index,row in enumerate(csv.reader(f)):
        if index == 0:
            continue
        Xtest.append(list(map(int,row[1:94])))

for i in range(len(Xtest)):
    res = [str(i+1)]
    ar = list(map(float,clf.predict_proba(list(map(int,Xtest[i])))[0]))
    ar2 = list(map(float,clf2.predict_proba(list(map(int,Xtest[i])))[0]))

    #sonuçları yan yana koyup summera sok
    heyyo = []
    for j in ar:
        heyyo.append(float(j))
    for j in ar2:
        heyyo.append(float(j))
    ar3 = list(map(str,summer.predict_proba(heyyo)[0]))

    for j in ar3:
        res.append(j)
    print(','.join(res), file=out)
