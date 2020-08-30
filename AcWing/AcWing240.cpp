#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=5e4+5;
const int MAXK=1e5+5;

int n,k;
int fa[MAXN*3];

inline int find(int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

inline void merge(int a,int b){
	int ra=find(a),rb=find(b);
	if(ra!=rb)
		fa[rb]=ra;
	return;
}

inline bool search(int a,int b){
	return find(a)==find(b);
}

int main(void){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=3*n;++i)
		fa[i]=i;
	int ans=0;
	for(int i=1;i<=k;++i){
		static int d,x,y;
		scanf("%d%d%d",&d,&x,&y);
		if(x>n||y>n){
			++ans;
			continue;
		}
		if(d==1){
			if(search(x+2*n,y)||search(x,y+2*n))
				++ans;
			else{
				merge(x,y);
				merge(x+n,y+n);
				merge(x+2*n,y+2*n);
			}
		}
		else if(d==2){
			if(search(x,y)||search(x,y+2*n))
				++ans;
			else{
				merge(x,y+n);
				merge(x+n,y+2*n);
				merge(x+2*n,y);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}