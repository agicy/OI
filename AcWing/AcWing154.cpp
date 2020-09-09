#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e6+5;

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
};

int n,k;
int ans[2][MAXN];
deque<Node> Qmin,Qmax;

int main(void){
	scanf("%d%d",&n,&k);
	for(reg int i=1;i<=n;++i){
		static int x;
		scanf("%d",&x);
		Node tmp=Node(i,x);
		while(!Qmin.empty()&&Qmin.back().val>x)
			Qmin.pop_back();
		while(!Qmax.empty()&&Qmax.back().val<x)
			Qmax.pop_back();
		Qmin.push_back(tmp),Qmax.push_back(tmp);
		while(i-k>=Qmin.front().id)
			Qmin.pop_front();
		while(i-k>=Qmax.front().id)
			Qmax.pop_front();
		if(i>=k)
			ans[0][i-k+1]=Qmin.front().val,
			ans[1][i-k+1]=Qmax.front().val;
	}
	for(reg int i=1;i+k-1<=n;++i)
		printf("%d%c",ans[0][i],i+k-1==n?'\n':' ');
	for(reg int i=1;i+k-1<=n;++i)
		printf("%d%c",ans[1][i],i+k-1==n?'\n':' ');
	return 0;
}