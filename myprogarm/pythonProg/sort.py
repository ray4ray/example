import random
list_data=[]

for i in range(10):
    list_data.append(random.randint(0,20))

print list_data

list_len = len(list_data)-1

for i in range(10):
	for j in range(list_len -i):
		if(list_data[j]> list_data[j+1]):
			tmp = list_data[j]
			list_data[j]=list_data[j+1]
			list_data[j+1]= tmp
			print "swap y i=%d j= %d data: %s" %(i,j, list_data)
		else:
			print "swap n i=%d j= %d data: %s" %(i,j, list_data)
		
print list_data
