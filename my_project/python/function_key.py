#! /usr/bin/python
def func(a=10, b=10, c=30):
	print 'a is', a ,' and b is ', b ,' and c is ', c
	if a > b:
		return a
	else:
		return b
	
x=func(3,7)
print x
func(25,c=12)
print x
func(c=50,a=100)
print x
