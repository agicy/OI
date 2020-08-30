#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=29+5;

int n;
int a[MAXN];

int main(void){
	int K;
	scanf("%d",&K);
	while(K--){
		scanf("%d",&n);
		int ans=1;
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;++i){
			static int x;
			scanf("%d",&x);
			a[i]=((a[i]^x)|(1<<i));
		}
		static int x,y;
		while(scanf("%d%d",&x,&y)!=EOF&&x!=0&&y!=0)
			a[y]|=(1<<x);
		for(int i=1;i<=n;++i){
			for(int j=i+1;j<=n;++j)
				if(a[j]>a[i])
					swap(a[i],a[j]);
			if(!a[i]){
				ans=1<<(n-i+1);
				break;
			}
			if(a[i]==1){
				ans=0;
				break;
			}
			for(int j=n;j>=1;--j)
				if(a[i]&(1<<j)){
					for(int k=1;k<=n;++k)
						if(i!=k&&(a[k]&(1<<j)))
							a[k]^=a[i];
					break;
				}
		}
		if(ans)
			printf("%d\n",ans);
		else
			puts("Oh,it's impossible~!!");
	}
	return 0;
}