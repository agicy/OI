def fac(x):
	if x<0:
		return 0
	res=1
	for i in range (1,x+1):
		res*=i
	return res

n=int(input())
cnt=0
sum=0
ans1=ans2=1
for i in range(0,n):
	d=int(input())
	if d!=-1:
		cnt=cnt+1
		sum=sum+d-1
		ans2=ans2*fac(d-1)
ans1=fac(sum)
ans=fac(n-2)//(fac(sum)*fac(n-sum-2))*ans1//ans2*(n-cnt)**(n-sum-2)
print(ans)