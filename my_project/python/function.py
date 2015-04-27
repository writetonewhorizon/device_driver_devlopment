#! /usr/bin/python
x=5
y=7
list=["dharmender","sharma","ece","431"]
def my_func2(message,times=1):
	print message*times
	print list[0]
	print list[:]
	list[0]="hemant"
	print list[0]
	global x	#global word is used to make a variable global
	x=14
def my_func1(a,b):	#defination of function
	if a>b:
		print a, 'is maximum'
		x=10	#local variable
		my_func2("hello world", 5)
	else:
		print b, 'is maximum'
		y=20

my_func1(x,y)	#calling of function
print x,y
print list[0]

