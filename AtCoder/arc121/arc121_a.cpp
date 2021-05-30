#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;

struct Point{
	int x,y;
};

int n;
Point a[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].x=read(),a[i].y=read();
	reg int Maxx=1,Maxy=1,Minx=1,Miny=1;
	for(reg int i=1;i<=n;++i){
		if(a[i].x>a[Maxx].x)
			Maxx=i;
		if(a[i].y>a[Maxy].y)
			Maxy=i;
		if(a[i].x<a[Minx].x)
			Minx=i;
		if(a[i].y<a[Miny].y)
			Miny=i;
	}
	set<int> S={Maxx,Maxy,Minx,Miny};
	set<pair<int,int> > T;
	vector<int> ans;
	for(auto j:S)
		for(int i=1;i<=n;++i)
			if(!T.count(make_pair(i,j))){
				ans.push_back(max(abs(a[j].x-a[i].x),abs(a[j].y-a[i].y)));
				T.insert(make_pair(i,j)),T.insert(make_pair(j,i));
			}
	sort(ans.begin(),ans.end());
	reverse(ans.begin(),ans.end());
	printf("%d\n",ans[1]);
	return 0;
}