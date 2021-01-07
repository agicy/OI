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

inline short readhd(void){
	reg char ch=getchar();
	reg short res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline short max(reg short a,reg short b){
	return a<b?b:a;
}
inline short min(reg short a,reg short b){
	return a<b?a:b;
}

const int MAXN=200+5;

struct Node{
	short x,y,z;
	inline Node(reg short x=0,reg short y=0,reg short z=0):x(x),y(y),z(z){
		return;
	}
};

int n;
bool vis[MAXN][MAXN][MAXN];
short M[MAXN][MAXN][MAXN];
queue<Node> Q;

int main(void){
	n=read();
	reg short Minx,Miny,Minz,Maxx,Maxy,Maxz;
	Minx=Miny=Minz=202;
	Maxx=Maxy=Maxz=1;
	for(reg int i=1;i<=n;++i){
		static short x1,y1,z1,x2,y2,z2;
		x1=readhd()+2,y1=readhd()+2,z1=readhd()+2,
		x2=readhd()+1,y2=readhd()+1,z2=readhd()+1;
		Minx=min(Minx,x1),Maxx=max(Maxx,x2),
		Miny=min(Miny,y1),Maxy=max(Maxy,y2),
		Minz=min(Minz,z1),Maxz=max(Maxz,z2);
		++M[x1][y1][z1],
		--M[x2+1][y1][z1],--M[x1][y2+1][z1],--M[x1][y1][z2+1],
		++M[x2+1][y2+1][z1],++M[x2+1][y1][z2+1],++M[x1][y2+1][z2+1],
		--M[x2+1][y2+1][z2+1];
	}
	--Minx,--Miny,--Minz,
	++Maxx,++Maxy,++Maxz;
	for(reg int i=Minx;i<=Maxx;++i)
		for(reg int j=Miny;j<=Maxy;++j)
			for(reg int k=Minz;k<=Maxz;++k){
				M[i][j][k]+=
					M[i-1][j][k]+M[i][j-1][k]+M[i][j][k-1]
					-M[i-1][j-1][k]-M[i-1][j][k-1]-M[i][j-1][k-1]
					+M[i-1][j-1][k-1];
			}
	vis[Minx][Miny][Minz]=true,Q.push(Node(Minx,Miny,Minz));
	reg int ans=0;
	while(!Q.empty()){
		static Node s;
		s=Q.front();
		Q.pop();
		reg short x=s.x,y=s.y,z=s.z;
		const short dx[]={-1,1,0,0,0,0};
		const short dy[]={0,0,-1,1,0,0};
		const short dz[]={0,0,0,0,-1,1};
		for(reg int i=0;i<6;++i){
			reg short fx=x+dx[i],fy=y+dy[i],fz=z+dz[i];
			if(Minx<=fx&&fx<=Maxx&&Miny<=fy&&fy<=Maxy&&Minz<=fz&&fz<=Maxz){
				if(!vis[fx][fy][fz]&&!M[fx][fy][fz]){
					vis[fx][fy][fz]=true;
					Q.push(Node(fx,fy,fz));
				}
				else if(M[fx][fy][fz])
					++ans;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}