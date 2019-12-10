#include<cstdio>
typedef long long ll;

const int MAXN=500000+5;

int n;
ll ans;
ll a[MAXN];
ll temp[MAXN];

void Merge_Sort(int l,int r){
	if(l==r)
		return;
	register int mid=(l+r)>>1;
	register int i=l,j=mid+1,k=l;
	Merge_Sort(l,mid),Merge_Sort(mid+1,r);
	while(i<=mid&&j<=r)
		if(a[i]>a[j])
			temp[k++]=a[j++],ans+=mid-i+1;
		else
			temp[k++]=a[i++];
	while(i<=mid)
		temp[k++]=a[i++];
	while(j<=r)
		temp[k++]=a[j++];
	for(i=l;i<=r;++i)
		a[i]=temp[i];
	return;
}

int main(void){
	register int i;
	while(scanf("%d",&n)!=EOF&&n){
		ans=0;
		for(i=1;i<=n;++i)
			scanf("%lld",&a[i]);
		Merge_Sort(1,n);
		printf("%lld\n",ans);
	}
	return 0;
}
