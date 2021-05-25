#include<bits/stdc++.h>
using namespace std;

inline int read(){
	char ch=getchar();
	int v=0;
	while(ch < '0' || ch > '9') ch=getchar();
	while(ch >= '0' && ch<='9') v=v * 10 + ch - '0',ch=getchar();
	return v;
}

int n,m,q;
bool s1[101010];
int type[101010];
int s0Length;

struct Question{
	int id;
	int l,r,area,curProgress=0;
}qu[101010],questionSortTmp[101010];

inline bool check(int l){
	for(int i=1;i < 40 / l;i++)
		for(int j=0;j < l;j++)
			if(s1[j + 1] != s1[i * l + j + 1] && i * l + j + 1<=m)
			{
				//printf("%d fake in %d and %d\n",l + 1,j,i * l + j + 1);
				return false;
			}
	return true;
}
inline void measureS0Length(){
	for(int res=1;res<=20;res++){
		if(m % res != 0) continue;
		if(res > m) continue;

		if(check(res)) {
			s0Length=res;
			return;
		}
	}
}
inline void readS1(){
	int ptr=0;
	char ch;
	while(ch < '0' || ch > '1') ch=getchar();
	for(int i=1;i<=m;i++) s1[i]=ch == '1',ch=getchar();
}

bool vis[101010];
int nex[201010],to[201010],head[101010],edgeCnt=0;
inline void Add_Edge(int u,int v){
	nex[++edgeCnt]=head[u];
	to[edgeCnt]=v;
	head[u]=edgeCnt;
}

bool gravityVis[101010];
int siz[101010];
int curGravity,curGravityWeight,totSize;
void dfs1(int p){
	gravityVis[p]=true;
	siz[p]=1;
	for(int i=head[p];i;i=nex[i]){
		int v=to[i];
		if(vis[v] || gravityVis[v]) continue;
		dfs1(v);
		siz[p] += siz[v];
	}
}
void dfs2(int p){
	gravityVis[p]=false;
	int res=0;
	for(int i=head[p];i;i=nex[i]){
		int v=to[i];
		if(vis[v] || !gravityVis[v]) continue;
		res=max(res,siz[v]);
	}
	res=max(res,totSize - siz[p]);
	if(res < curGravityWeight){
		curGravityWeight=res;
		curGravity=p;
	}
	for(int i=head[p];i;i=nex[i]){
		int v=to[i];
		if(vis[v] || !gravityVis[v]) continue;
		dfs2(v);
	}
}
inline void getGravity(int start){
	curGravity=-1,curGravityWeight=0x3f3f3f3f;
	dfs1(start);
	//for(int i=1;i<=n;i++) printf("%d ",siz[i]);
	totSize=siz[start];
	dfs2(start);
	//printf("%d",curGravity);
}

bool dtvis[101010];
int area[101010];
inline void spreadArea(int p){
	dtvis[p]=true;
	//printf("%d ",p);
	for(int i=head[p];i;i=nex[i]){
		int v=to[i];
		if(vis[v] || dtvis[v]) continue;
		area[v]=area[p];
		spreadArea(v);
	}
	dtvis[p]=false;
}

int areaCnt;
int areaSize[101010];
int nextArea[101010];
int dist[21][101010];

void getTargetDist(int p){
	dtvis[p]=true;/*
	for(int j=0;j < s0Length;j++){
		printf("dist:(%d,%d) -> %d\n",j,p,dist[j][p]);
	}*/

	for(int i=head[p];i;i=nex[i]){
		int v=to[i];
		if(vis[v] || dtvis[v]) continue;
		
		for(int j=0;j < s0Length;j++){
			if(type[v] == s1[j + 1]) dist[j][v]=dist[j + 1 < s0Length ? j + 1 : 0][p] + 1;
			else dist[j][v]=dist[j][p];
		}

		getTargetDist(v);
	}
	dtvis[p]=false;
}
inline void getDistArea(int p){
	areaCnt=0;
	for(int i=head[p];i;i=nex[i]){
		int v=to[i];
		if(vis[v]) continue;
	//	printf("area %d:",areaCnt + 1);
		nextArea[++areaCnt]=v;
		area[v]=areaCnt;
		spreadArea(v);
	//	printf("\n");
	}
	if(!areaCnt) return;
	
	area[p]=areaCnt + 1;
	nextArea[areaCnt + 1]=0;

	for(int i=0;i < s0Length;i++){
		if(type[p] == s1[i + 1]) dist[i][p]=1;
		else dist[i][p]=0;
	}
	getTargetDist(p);
}

int sortTmp[101010]={1};
inline void sortQuestions(int l,int r,int areaCnt){
	for(int i=1;i<=areaCnt + 1;i++) areaSize[i]=0;
	for(int i=l;i<=r;i++){
		qu[i].area=area[qu[i].r];
		//printf("quest %d(%d,%d) area=%d\n",i,qu[i].l,qu[i].r,qu[i].area);
		areaSize[qu[i].area]++;
	}
	areaSize[0]=0;
	for(int i=1;i<=areaCnt + 1;i++){
		sortTmp[i]=sortTmp[i - 1] + areaSize[i - 1];
		//printf("Area %d siz=%d pos=%d\n",i,areaSize[i],sortTmp[i]);
	}
	for(int i=l;i<=r;i++){
		int pos=sortTmp[qu[i].area]++;
		questionSortTmp[pos + (l - 1)]=qu[i];
	}
	//printf("sorted:\n");
	for(int i=l;i<=r;i++){
		qu[i]=questionSortTmp[i];
	//	printf("%d->(%d~%d,%d)",i,qu[i].l,qu[i].r,qu[i].area);
	}
	//printf("\n");
}

inline void cutQuestions(int l,int r,int areaCnt){
	for(int i=l;i<=r;i++){
	//	printf("->");
		if(area[qu[i].l] == qu[i].area) continue;
	//	printf("solving %d (%d~%d,progress=%d)\n",i,qu[i].l,qu[i].r,qu[i].curProgress);
		qu[i].curProgress += dist[qu[i].curProgress % s0Length][qu[i].l];
		qu[i].l=nextArea[qu[i].area];
		if(!qu[i].l) qu[i].r=0;
	//	printf("get new: (%d~%d),progress=%d\n",qu[i].l,qu[i].r,qu[i].curProgress);
	}
}

struct Vector3{
	int x,y,z;
	Vector3(int x,int y,int z) : x(x),y(y),z(z){}
	void Print(){ printf("(%d,%d,%d)",x,y,z);}
};

void Solve(int p,int l,int r){
	//printf("-----solving %d,(%d-%d)-----\n",p,l,r);
	vis[p]=true;
	getDistArea(p);
	if(areaCnt == 0) return;
	sortQuestions(l,r,areaCnt);
	cutQuestions(l,r,areaCnt);
	//printf("next solve:\n");
	stack<Vector3> solvingList;
	for(int i=1;i<=areaCnt;i++){
		if(areaSize[i] == 0) continue;
		getGravity(nextArea[i]);
		int v=curGravity;
	//	printf("%d(i=%d):",v,i);
		solvingList.push(Vector3(v,sortTmp[i - 1] + l - 1,sortTmp[i - 1] + areaSize[i] + l - 2));
	//	solvingList.top().Print();
	//	printf("\n");
	}
	while(!solvingList.empty()){
		Vector3 v=solvingList.top();
		solvingList.pop();
		Solve(v.x,v.y,v.z);
	}
}

int finalRes[101010];
inline void answer(){
	for(int i=1;i<=q;i++){
		int p=qu[i].curProgress;
		if(qu[i].l != 0){
			if(qu[i].l != qu[i].r) printf("!");
			if(type[qu[i].l] == s1[qu[i].curProgress % s0Length + 1]) 
				p++;
		}
		finalRes[qu[i].id]=p;
	}
	for(int i=1;i<=q;i++) printf("%d\n",finalRes[i]);
}
int main(){
	memset(vis,0,sizeof vis);
	memset(gravityVis,0,sizeof gravityVis);
	n=read(),m=read(),q=read();
 	readS1();
	measureS0Length();
	fprintf(stderr,"stage1 %.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	for(int i=1;i<=n;i++)
	    type[i]=read();
	for(int i=1;i < n;i++){
		int u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	for(int i=1;i<=q;i++){
		qu[i].l=read();
		qu[i].r=read();
		qu[i].id=i;
	}
	fprintf(stderr,"stage2 %.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	getGravity(1);
	int x=curGravity;
	fprintf(stderr,"stage3 %.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	Solve(x,1,q);
	fprintf(stderr,"stage4 %.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	answer();
	fprintf(stderr,"final %.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}