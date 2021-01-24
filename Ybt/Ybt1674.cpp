#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=3e6+5;
const int MAXR=3e6+5;

int n;
int T[MAXR];
int cnt[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		++T[read()];
	for(reg int i=1;i<=n;++i)
		++cnt[T[i]];
	reg int ptr1=n,ptr2=n,ptr3=n;
	reg int ans=0;
	while(ptr1&&ptr2&&ptr3){
		while(ptr1&&!cnt[ptr1])
			--ptr1;
		--cnt[ptr1];
		while(ptr2&&!cnt[ptr2])
			--ptr2;
		--cnt[ptr2];
		while(ptr3&&!cnt[ptr3])
			--ptr3;
		--cnt[ptr3];
		if(ptr1&&ptr2&&ptr3){
			++cnt[ptr1-1],++cnt[ptr2-1],++cnt[ptr3-1];
			++ans;
		}
	}
	printf("%d\n",ans);
	return 0;
}