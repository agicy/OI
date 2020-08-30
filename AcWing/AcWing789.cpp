#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int n,q;
vector<int> V;

int main(void){
	scanf("%d%d",&n,&q);
	V.resize(n);
	for(reg int i=0;i<n;++i)
		scanf("%d",&V[i]);
	while(q--){
		static int k;
		scanf("%d",&k);
		reg int l=lower_bound(V.begin(),V.end(),k)-V.begin();
		if(l==V.size())
			puts("-1 -1");
		else{
			reg int r=upper_bound(V.begin(),V.end(),k)-V.begin()-1;
			if(l>r)
				puts("-1 -1");
			else
				printf("%d %d\n",l,r);
		}
	}
	return 0;
}