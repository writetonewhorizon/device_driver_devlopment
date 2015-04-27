#! /usr/bin/python
a=10
b=6
c="dharm"
d="sharma"
e=1
g=2
print a+b
print a-b
print a*b
print a/b
print a//b
print a&b
print a|b
print c+d
print a<<3
print a>>3
a=input('input number first no. for comparision : ')#takes only integer i/o and return integer
b=input('input number second no. for comparision : ')#takes both integer and string as input and return respectively
c=raw_input('enter first name : ')
d=raw_input('enter secomd name : ')
if a>b and d>c:
	print c
	if b>a or a>b:
		for i in range(1,10):
			if i==4:
				continue
			else:
				print i
	else:
		print c
elif a<b:
	g=input('enter nuber for while loop : ')
	while g>e:
		m=raw_input('enter string : ')
		print m
		if m == "dharm":
			break
		else:
	 		print g
			g=g-1
else:
	print d
