#include <bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=2000000+5;

struct Node{
	int l,r,diff;
	inline Node(reg int l,reg int r,reg int diff):l(l),r(r),diff(diff){
		return;
	}
	inline bool operator<(const Node& a)const{
		return diff==a.diff?l>a.l:diff>a.diff;
	}
};

int n;
int a[MAXN];
bool vis[MAXN],f[MAXN];
vector<pair<int,int>/**/> V;
priority_queue<Node> Q;

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		static char ch;
		cin>>ch;
		f[i]=(ch=='B');
	}
	for(reg int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(reg int i=1;i<n;++i)
		if(f[i]!=f[i+1])
			Q.push(Node(i,i+1,abs(a[i]-a[i+1])));
	while(!Q.empty()){
		reg int l=Q.top().l,r=Q.top().r;
		Q.pop();
		if(!vis[l]&&!vis[r]){
			vis[l]=vis[r]=true;
			V.push_back(make_pair(l,r));
			while(l>0&&vis[l])
				--l;
			while(r<=n&&vis[r])
				++r;
			if(0<l&&r<=n&&f[l]!=f[r])
				Q.push(Node(l,r,abs(a[l]-a[r])));
		}
	}
	printf("%d\n",(int)V.size());
	for(reg int i=0,size=V.size();i<size;++i)
		printf("%d %d\n",V[i].first,V[i].second);
	return 0;
}
