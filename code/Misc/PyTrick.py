from itertools import permutations
op = ['+', '-', '*', '']
a, b, c, d = input().split()
ans = set()
for (x,y,z,w) in permutations([a, b, c, d]):
	for op1 in op:
		for op2 in op:
			for op3 in op:
				val = eval(f"{x}{op1}{y}{op2}{z}{op3}{w}")
				if (op1 == '' and op2 == '' and op3 == '') or val < 0:
					continue
				ans.add(val)
print(len(ans))
#
from decimal import *
from fractions import *
s = input()
n = int(input())
f = Fraction(s)
g = Fraction(s).limit_denominator(n)
h = f * 2 - g
if h.numerator <= n and h.denominator <= n and h < g:
	g = h
print(g.numerator, g.denominator)