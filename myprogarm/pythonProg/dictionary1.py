#!/usr/local/bin/python
#this is a dictionary example

D = {'a':1, 'b':2, 'c':3}
print(D)
Ks =list(D.keys())
print(Ks)
Ks.sort()
print(Ks)
for key in Ks:
	print(key, '=>',D[key])
