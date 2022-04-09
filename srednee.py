import math
def sr(SInputFile="1.txt"):
	"""
	Srednee arifmeticheskoe
	>>> sr('qwewqeqweqw')
	(1, 1)

	>>> g=open('1.txt','w')
	>>> u=g.write('2  \\n 2   ')
	>>> g.close()
	>>> sr()
	(0, 2.0)

	>>> g=open('2.txt','w')
	>>> u=g.write('  \\n      ')
	>>> g.close()
	>>> sr('2.txt')
	(1, 3)

	>>> g=open('1.txt','w')
	>>> u=g.write('  2 11 3  \\n  4  3e    ')
	>>> g.close()
	>>> sr()
	(1, 2)

	"""
	try:
		f=open(SInputFile,"r")
		s=0
		n=0
		for line in f:
			for x in line.split():
				x=float(x)
				n+=1
				s+=x
		return 0,s/n
		f.close()
		return word,count
	except FileNotFoundError:
		return 1,1
	except ValueError:
		return 1,2
	except ZeroDivisionError:
		return 1,3
		
import doctest
doctest.testmod()