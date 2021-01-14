#include<cstdio>
#include<cstring>
#define max(a,b)	( (a) > (b) ? (a) : (b) )

int n,a[5001],f[5001],count[5001];

int main(void){
	register int i,j,Max=0,sum=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(i=1;i<=n;i++){
		for(j=1;j<i;j++)
			if(a[i]<a[j])
				f[i]=max(f[i],f[j]+1);
		if(!f[i])
			f[i]=1;
		Max=max(Max,f[i]);
	}
	for(i=1;i<=n;i++){
		for(j=1;j<i;j++)
			if(!(f[i]^f[j])&&!(a[i]^a[j]))
				count[j]=0;
			else if(!(f[i]^(f[j]+1))&&a[i]<a[j])
				count[i]+=count[j];
		if(!count[i])
			count[i]=1;
	}
	for(i=1;i<=n;i++)
		if(!(f[i]^Max))
			sum+=count[i];
	printf("%d %d",Max,sum);
	return 0;
}