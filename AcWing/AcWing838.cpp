#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int n,m;
priority_queue<int> Q;
stack<int> S;

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i){
		static int x;
		scanf("%d",&x);
		Q.push(x);
		while(Q.size()>m)
			Q.pop();
	}
	while(!Q.empty())
		S.push(Q.top()),Q.pop();
	for(reg int i=1;i<=m;++i){
		printf("%d%c",S.top(),i==m?'\n':' ');
		S.pop();
	}
	return 0;
}