#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() ((p1==p2)&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
int cnt=-1;
inline void read(reg char s[]){
	reg char ch=getchar();
	s[++cnt]='$',s[++cnt]='#';
	while(ch<'a'||'z'<ch)ch=getchar();
	while('a'<=ch&&ch<='z')s[++cnt]=ch,s[++cnt]='#',ch=getchar();
	return;
}

const int MAXLEN=11000000+5;

int T;
char s[MAXLEN<<1];

inline void Work(void);

int main(void){
	read(s);
	Work();
	return 0;
}

int p[MAXLEN<<1];

inline int Manacher(reg char str[],reg int len){
	reg int ans=0;
	for(reg int i=1,r=0,mid=0;i<=len;++i){
		if(i<=r)
			p[i]=min(p[(mid<<1)-i],r-i+1);
		while(str[i-p[i]]==str[i+p[i]])
			++p[i];
		if(p[i]+i>r){
			r=p[i]+i-1,
			mid=i;
		}
		ans=max((int)ans,p[i]);
	}
	return ans-1;
}

inline void Work(void){
	printf("%d\n",Manacher(s,cnt));
	return;
}
