import random
list_data=[]

for i in range(10):
    list_data.append(random.randint(0,40))

print list_data

list_len = len(list_data)

for i in range(1,len):
	tmpj = list_len
	for j in range(i-1:0: -1):
		if(list_data[j]> list_data[i]):
			tmpj = j
			print "move j in i " %(i,j)
		else:
			print "no move j in i, break, data %s" %(i,j, list_data)
			break
	
	
    if(tmpj < i):
	    tmp = list_data[tmpj]
		for j in range(i:tmpj+1: -1)
			list_data[j] = list_data[j-1]
		list_data[j] = tmp
print list_data
