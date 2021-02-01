#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int query(reg int x){
	printf("%d\n",x);
	fflush(stdout);
	int res;
	scanf("%d",&res);
	return res;
}

int main(void){
	reg int l=1,r=1e9,mid;
	while(l<=r){
		mid=(l+r)>>1;
		reg int res=query(mid);
		switch(res){
			case 0:{
				return 0;
				break;
			}
			case -1:{
				l=mid+1;
				break;
			}
			case 1:{
				r=mid-1;
				break;
			}
		}
	}
	return 0;
}