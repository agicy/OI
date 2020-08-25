#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define lowbit(x) ( (x) & ( - (x) ) )

const int MAXSIZE=9;
const int MAXCSIZE=3;

int cnt[1<<MAXSIZE];
int p[1<<MAXSIZE];

inline void Init(void){
	for(reg int i=0;i<(1<<MAXSIZE);++i)
		cnt[i]=cnt[i>>1]+(i&1);
	for(reg int i=0;i<MAXSIZE;++i)
		p[1<<i]=i;
	return;
}

struct Node{
	int S[MAXSIZE][MAXSIZE];
	char str[MAXSIZE][MAXSIZE+1];
	inline int Read(void){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				S[i][j]=(1<<MAXSIZE)-1;
		char s[MAXSIZE*(MAXSIZE+1)];
		scanf("%s",s);
		if(s[0]=='e')
			exit(0);
		reg int res=0;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				str[i][j]=s[i*MAXSIZE+j];
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				switch(str[i][j]){
					case '.':{
						++res;
						break;
					}
					default:{
						draw(i,j,str[i][j]-'1');
						break;
					}
				}
		return res;
	}
	inline void draw(reg int x,reg int y,reg int v){
		str[x][y]=v+'1';
		for(reg int i=0;i<MAXSIZE;++i){
			S[x][i]&=~(1<<v);
			S[i][y]&=~(1<<v);
		}
		reg int fx=x/MAXCSIZE*MAXCSIZE,fy=y/MAXCSIZE*MAXCSIZE;
		for(reg int i=0;i<MAXCSIZE;++i)
			for(reg int j=0;j<MAXCSIZE;++j)
				S[fx+i][fy+j]&=~(1<<v);
		S[x][y]=1<<v;
		return;
	}
	inline void Print(void){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				putchar(str[i][j]);
		putchar('\n');
		return;
	}
};


inline bool DFS(reg int need,Node a){
	if(need<0)
		return false;
	if(!need){
		a.Print();
		return true;
	}
	for(reg int i=0;i<MAXSIZE;++i)
		for(reg int j=0;j<MAXSIZE;++j)
			if(a.str[i][j]=='.'){
				if(!a.S[i][j])
					return false;
				if(cnt[a.S[i][j]]==1){
					a.draw(i,j,p[a.S[i][j]]);
					--need;
				}
			}
	for(reg int i=0;i<MAXSIZE;++i){
		reg int sor=0,sand=(1<<MAXSIZE)-1,drawn=0;
		for(reg int j=0;j<MAXSIZE;++j){
			sand&=~(sor&a.S[i][j]);
			sor|=a.S[i][j];
			if(a.str[i][j]!='.')
				drawn|=a.S[i][j];
		}
		if(sor!=(1<<MAXSIZE)-1)
			return false;
		for(reg int j=sand;j;j-=lowbit(j))
			if(!(drawn&lowbit(j)))
				for(reg int k=0;k<MAXSIZE;++k)
					if(a.S[i][k]&lowbit(j)){
						--need;
						a.draw(i,k,p[lowbit(j)]);
						break;
					}
	}
	for(reg int i=0;i<MAXSIZE;++i){
		reg int sor=0,sand=(1<<MAXSIZE)-1,drawn=0;
		for(reg int j=0;j<MAXSIZE;++j){
			sand&=~(sor&a.S[j][i]);
			sor|=a.S[j][i];
			if(a.str[j][i]!='.')
				drawn|=a.S[j][i];
		}
		if(sor!=(1<<MAXSIZE)-1)
			return false;
		for(reg int j=sand;j;j-=lowbit(j))
			if(!(drawn&lowbit(j)))
				for(reg int k=0;k<MAXSIZE;++k)
					if(a.S[k][i]&lowbit(j)){
						--need;
						a.draw(k,i,p[lowbit(j)]);
						break;
					}
	}
	for(reg int i=0;i<MAXSIZE;++i){
		reg int sor=0,sand=(1<<MAXSIZE)-1,drawn=0;
		for(reg int j=0;j<MAXSIZE;++j){
			reg int sx=i/MAXCSIZE*MAXCSIZE,sy=i%MAXCSIZE*MAXCSIZE;
			reg int dx=j/MAXCSIZE,dy=j%MAXCSIZE;
			sand&=~(sor&a.S[sx+dx][sy+dy]);
			sor|=a.S[sx+dx][sy+dy];
			if(a.str[sx+dx][sy+dy]!='.')
				drawn|=a.S[sx+dx][sy+dy];
		}
		if(sor!=(1<<MAXSIZE)-1)
			return false;
		for(reg int j=sand;j;j-=lowbit(j))
			if(!(drawn&lowbit(j)))
				for(reg int k=0;k<MAXSIZE;++k){
					reg int sx=i/MAXCSIZE*MAXCSIZE,sy=i%MAXCSIZE*MAXCSIZE;
					reg int dx=k/MAXCSIZE,dy=k%MAXCSIZE;
					if(a.S[sx+dx][sy+dy]&lowbit(j)){
						--need;
						a.draw(sx+dx,sy+dy,p[lowbit(j)]);
						break;
					}
				}
	}
	if(!need){
		a.Print();
		return true;
	}
	reg int Min=MAXSIZE,posx=-1,posy=-1;
	for(reg int i=0;i<MAXSIZE;++i)
		for(reg int j=0;j<MAXSIZE;++j)
			if(a.str[i][j]=='.'&&cnt[a.S[i][j]]<Min){
				Min=cnt[a.S[i][j]];
				posx=i,posy=j;
			}
	if(posx==-1&&posy==-1)
		return false;
	reg int k=a.S[posx][posy];
	while(k){
		Node temp=a;
		temp.draw(posx,posy,p[lowbit(k)]);
		if(DFS(need-1,temp))
			return true;
		k-=lowbit(k);
	}
	return false;
}

Node a;

int main(void){
	Init();
	while(true){
		reg int n=a.Read();
		DFS(n,a);
	}
	return 0;
}