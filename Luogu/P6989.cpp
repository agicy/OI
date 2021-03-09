#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=100+5;
const int MAXS=5e4+5;

int n;
int tot,tim;
int C[MAXN],trans[MAXN][3];
int antiC[MAXS],antiTrans[MAXS][3];
int id[MAXN][MAXN];

inline int AtoI(reg char x){
	switch(x){
		case 'R':return 0;
		case 'P':return 1;
		case 'S':return 2;
		default:return -1;
	}
}

inline char ItoA(reg int x){
	switch(x){
		case 0:return 'R';
		case 1:return 'P';
		case 2:return 'S';
		default:return -1;
	}
}

inline int CtoaC(reg int x){
	switch(x){
		case 0:return 1;
		case 1:return 2;
		case 2:return 0;
		default:return -1;
	}
}

inline void getNex(void){
	++tim;
	for(reg int i=1;i<=n;++i){
		id[tim][i]=++tot;
		antiC[tot]=CtoaC(C[i]);
	}
	for(reg int i=1;i<=n;++i)
		antiTrans[id[tim][i]][C[i]]=id[tim][trans[i][antiC[id[tim][i]]]];
	return;
}

inline void getInf(reg int x){
	reg int u=1,cnt=0;
	while(antiTrans[u][C[x]]&&cnt<=tot){
		reg int op=antiC[u],cp=C[x];
		u=antiTrans[u][cp],x=trans[x][op];
		++cnt;
	}
	if(cnt>tot)
		return;
	getNex();
	antiTrans[u][C[x]]=id[tim][trans[x][antiC[u]]];
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		do
			C[i]=getchar();
		while(!isalpha(C[i]));
		C[i]=AtoI(C[i]);
		trans[i][0]=read(),trans[i][1]=read(),trans[i][2]=read();
	}
	getNex();
	for(reg int i=1;i<=n;++i)
		getInf(i);
	printf("%d\n",tot);
	for(reg int i=1;i<=tot;++i)
		printf("%c %d %d %d\n",ItoA(antiC[i]),max(antiTrans[i][0],1),max(antiTrans[i][1],1),max(antiTrans[i][2],1));
	return 0;
}