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

const int MAXN=50+5;
const int MAXM=400+5;
const int MAXO=8.2e5+5;

int n,m;
int a[MAXN][MAXM],top[MAXN];
int cnt;
pair<int,int> O[MAXO];
int p[MAXN];

inline void move(int x,int y){
	a[y][++top[y]]=a[x][top[x]--];
	O[++cnt]=make_pair(x,y);
	return;
}

inline int getCnt(reg int id,reg int col){
	reg int res=0;
	for(reg int i=1;i<=m;++i)
		res+=(a[id][i]==col);
	return res;
}

inline int getTop(reg int id){
	return a[id][top[id]];
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			a[i][++top[i]]=read();
	for(reg int i=1;i<=n+1;++i)
		p[i]=i;
	for(reg int id=n;id>=3;--id){
		reg int tmp=getCnt(p[1],id);
		for(reg int i=1;i<=tmp;++i)
			move(p[id],p[id+1]);
		for(reg int i=1;i<=m;++i)
		if(getTop(p[1])==id)
			move(p[1],p[id]);
		else
			move(p[1],p[id+1]);
		for(reg int i=1;i<=m-tmp;++i)
			move(p[id+1],p[1]);
		for(reg int i=1;i<=m;++i)
			if(getTop(p[2])==id||top[p[1]]==m)
				move(p[2],p[id+1]);
			else
				move(p[2],p[1]);
		swap(p[1],p[id]),swap(p[2],p[id+1]);
		for(reg int k=1;k<id;++k){
			reg int tmp=getCnt(p[k],id);
			for(reg int i=1;i<=tmp;++i)
				move(p[id],p[id+1]);
			for(reg int i=1;i<=m;++i)
				if(getTop(p[k])==id)
					move(p[k],p[id]);
				else
					move(p[k],p[id+1]);
			swap(p[k],p[id+1]),swap(p[k],p[id]);
		}
		for(reg int i=1;i<id;++i)
			while(getTop(p[i])==id)
				move(p[i],p[id+1]);
		for(reg int i=1;i<id;++i)
			while(top[p[i]]<m)
				move(p[id],p[i]);
	}
	reg int tmp=getCnt(p[1],1);
	for(reg int i=1;i<=tmp;++i)
		move(p[2],p[3]);
	for(reg int i=1;i<=m;++i)
		if(getTop(p[1])==1)
			move(p[1],p[2]);
		else
			move(p[1],p[3]);
	for(reg int i=1;i<=tmp;++i)
		move(p[2],p[1]);
	for(reg int i=1;i<=m-tmp;++i)
		move(p[3],p[1]);
	while(top[p[3]])
		move(p[3],p[2]);
	for(reg int i=1;i<=m-tmp;++i)
		move(p[1],p[3]);
	for(reg int i=1;i<=m;++i)
		if(getTop(p[2])==1)
			move(p[2],p[1]);
		else
			move(p[2],p[3]);
	printf("%d\n",cnt);
	for(reg int i=1;i<=cnt;++i)
		printf("%d %d\n",O[i].first,O[i].second);
	return 0;
}