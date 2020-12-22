import math

def P(n,m):
	if(m<0 or m>n):
		return 0
	else:
		return math.factorial(n)//math.factorial(n-m)

n,m=map(int,input().split())
print(P(n+3,m)*P(n+2,n+2)-2*P(n+2,m)*P(n+1,n+1))