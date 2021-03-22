#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int query(reg int l1,reg int r1,reg int l2,reg int r2){
	printf("? %d %d\n",r1-l1+1,r2-l2+1);
	for(reg int i=l1;i<=r1;++i)
		printf("%d%c",i,i==r1?'\n':' ');
	for(reg int i=l2;i<=r2;++i)
		printf("%d%c",i,i==r2?'\n':' ');
	fflush(stdout);
	static char res[16];
	scanf("%s",res);
	switch(res[0]){
		case 'F':
			return 1;
		case 'S':
			return 2;
		case 'E':
			return 0;
		default:
			exit(0);
	}
}

const int MAXN=1e3+5;

int n;

inline int myrand(reg int l,reg int r){
	return rand()%(r-l+1)+l;
}

int main(void){
	srand(time(0));
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%*d",&n);
		reg bool flag=false;
		const int lim=min(30,n-1);
		for(reg int i=1;i<=lim;++i){
			reg int pos=myrand(2,n);
			if(query(1,1,pos,pos)==2){
				flag=true;
				break;
			}
		}
		if(flag)
			puts("! 1");
		else{
			reg int ptr=1;
			while((ptr<<1)<=n){
				if(query(1,ptr,ptr+1,ptr<<1)==1)
					break;
				ptr<<=1;
			}
			reg int l=ptr+1,r=min(ptr<<1,n),mid;
			while(l<r){
				mid=(l+r)>>1;
				if(query(1,mid-l+1,l,mid)==0)
					l=mid+1;
				else
					r=mid;
			}
			printf("! %d\n",l);
		}
		fflush(stdout);
	}
	return 0;
}