#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

struct Point{
	int x,y;
	inline Point(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
	inline bool operator<(const Point& a)const{
		if(y!=a.y)
			return y<a.y;
		else
			return x<a.x;
	}
};

const int MAXN=1e3+5;
const int MAXM=1e3+5;
const int MAXQ=1e6+5;
const int inf=1e3+5;

int n,m;
Point st,ed;
int q;
Point p[MAXQ];
vector<int> V;

inline double calc(reg int xa,reg int ya,reg int xb,reg int yb,reg int x){
	return 1.0*(xa*xa-xb*xb+2*x*(xb-xa))/(ya-yb)+ya+yb;
}

int dis[MAXN][MAXM];
Point fr[MAXN];

inline void getDis(void){
	sort(p+1,p+q+1);
	static int _head[MAXM],_tail[MAXM];
	for(reg int l=1,r;l<=q;l=r){
		r=l+1;
		while(r<=q&&p[l].y==p[r].y)
			++r;
		_head[p[l].y]=l,_tail[p[l].y]=r;
	}
	for(reg int i=1;i<=n;++i){
		fr[0]=Point(inf,-inf);
		reg int tot=0,top=0;
		for(reg int j=1;j<=m;++j){
			if(!_tail[j])
				continue;
			reg int Min=abs(p[_head[j]].x-i);
			while(_tail[j]-_head[j]>1&&abs(p[_head[j]+1].x-i)<Min)
				++_head[j],Min=abs(p[_head[j]].x-i);
			fr[++tot]=p[_head[j]];
		}
		static int id[MAXQ],S[MAXQ];
		for(reg int j=1;j<=tot;++j){
			reg double res=calc(fr[j].x,fr[j].y,fr[id[top]].x,fr[id[top]].y,i);
			while(top&&res<=S[top])
				--top,res=calc(fr[j].x,fr[j].y,fr[id[top]].x,fr[id[top]].y,i);
			S[++top]=res,id[top]=j;
		}
		for(reg int j=1,l=1;j<=m;++j){
			while(S[l+1]<(j<<1)&&l+1<=top)
				++l;
			dis[i][j]=(i-fr[id[l]].x)*(i-fr[id[l]].x)+(j-fr[id[l]].y)*(j-fr[id[l]].y);
			V.push_back(dis[i][j]);
		}
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	return;
}

inline bool check(reg int lim){
	if(dis[st.x][st.y]<lim)
		return false;
	static bool vis[MAXN][MAXM];
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			vis[i][j]=false;
	reg int _head=0,_tail=0;
	static int Qx[MAXN*MAXM],Qy[MAXN*MAXM];
	vis[st.x][st.y]=true,Qx[_tail]=st.x,Qy[_tail]=st.y,++_tail;
	while(_head<_tail){
		reg int x=Qx[_head],y=Qy[_head];
		++_head;
		if(x==ed.x&&y==ed.y)
			return true;
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		for(reg int k=0;k<4;++k){
			reg int fx=x+dx[k],fy=y+dy[k];
			if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&!vis[fx][fy]&&dis[fx][fy]>=lim)
				vis[fx][fy]=true,Qx[_tail]=fx,Qy[_tail]=fy,++_tail;
		}
	}
	return false;
}

int main(void){
	n=read(),m=read();
	st.x=read(),st.y=read(),ed.x=read(),ed.y=read();
	q=read();
	for(reg int i=1;i<=q;++i)
		p[i].x=read(),p[i].y=read();
	getDis();
	reg int l=0,r=V.size()-1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(V[mid+1]))
			l=mid+1;
		else
			r=mid;
	}
	printf("%d\n",V[l]);
	return 0;
}