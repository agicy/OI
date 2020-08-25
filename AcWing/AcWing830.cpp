#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;

int n;
int a[MAXN];
stack<int> S;
int ans[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	S.push(-1);
	for(reg int i=1;i<=n;++i){
		while(!S.empty()&&S.top()>=a[i])
			S.pop();
		ans[i]=S.top();
		S.push(a[i]);
	}
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}