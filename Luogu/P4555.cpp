#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=2e5+5;

int p[MAXN],L[MAXN],R[MAXN];
char s[MAXN],S[MAXN];

int main(void){
	scanf("%s",S);
	reg int len=strlen(S),cnt=0;
	s[++cnt]='$',s[++cnt]='#';
	for(reg int i=0;i<len;++i){
		s[++cnt]=S[i];
		s[++cnt]='#';
	}
	s[++cnt]='\0';
	reg int mid=0,r=0;;
	for(reg int i=1;i<=cnt;++i){
		if(i<r)
			p[i]=min(p[mid*2-i],r-i);
		else
			p[i]=1;
		while(s[i-p[i]]==s[i+p[i]])
			++p[i];
		if(r<i+p[i])
			mid=i,r=i+p[i];
		L[i+p[i]-1]=max(L[i+p[i]-1],p[i]-1);
		R[i-p[i]+1]=max(R[i-p[i]+1],p[i]-1);
	}
	for(reg int i=2;i<=cnt;i+=2)
		R[i]=max(R[i],R[i-2]-2);
	for(reg int i=cnt;i>=2;i-=2)
		L[i]=max(L[i],L[i+2]-2);
	int ans=0;
	for(reg int i=2;i<=cnt;i+=2)
		if(R[i]&&L[i])
			ans=max(ans,L[i]+R[i]);
	printf("%d\n",ans);
	return 0;
}