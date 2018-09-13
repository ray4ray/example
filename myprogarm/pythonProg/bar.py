def count(sales):
	if(sales > 20):
		return sales * 10000 * 0.03
	elif(sales > 10):
		return sales * 10000 * 0.02
	else:
		return sales * 10000 * 0.01

while(True):
	sales = int(raw_input("enter Sales:"))
	print "salary = %d RMB" % count(sales);

