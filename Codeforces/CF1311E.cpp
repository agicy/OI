#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=5e3+5;

int n,d;
int fa[MAXN],dep[MAXN];

int main(void){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&d);
		dep[0]=-1;
		reg int sum=0;
		reg int pos=-1;
		for(reg int i=1;i<=n;++i){
			dep[i]=dep[i>>1]+1;
			sum+=dep[i];
			fa[i]=(i>>1);
			if(!(i&(i-1)))
				pos=i;
		}
		d-=sum;
		if(d<0)
			puts("NO");
		else{
			if(!d){
				puts("YES");
				for(reg int i=2;i<=n;++i)
					printf("%d%c",fa[i],i==n?'\n':' ');
			}
			else{
				for(reg int i=n;i>=1;--i){
					if(!(i&(i-1)))
						continue;
					d-=dep[pos]+1-dep[i];
					if(d<=0){
						while(d) pos=fa[pos],++d;
						d=0;
						fa[i]=pos;
						break;
					}
					fa[i]=pos,dep[i]=dep[pos]+1,pos=i;
				}
				if(d)
					puts("NO");
				else{
					puts("YES");
					for(reg int i=2;i<=n;++i)
						printf("%d%c",fa[i],i==n?'\n':' ');
				}
			}
		}
	}
	return 0;
}