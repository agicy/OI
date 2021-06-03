#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e5+5;
const int MAXLOG2N=18+1;
const int inf=0x3f3f3f3f;

int n;
int h[MAXN];
int lef[MAXLOG2N][MAXN],rig[MAXLOG2N][MAXN],jmp[MAXLOG2N][MAXN];

namespace ST{
	int lg[MAXN];
	int posMax[MAXLOG2N][MAXN];
	int *cmp;
	inline void Init(reg int n,reg int a[]){
		lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			lg[i]=lg[i>>1]+1;
		cmp=a;
		for(reg int i=1;i<=n;++i)
			posMax[0][i]=i;
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i<=n;++i)
				if(cmp[posMax[j-1][i]]>cmp[posMax[j-1][i+(1<<(j-1))]])
					posMax[j][i]=posMax[j-1][i];
				else
					posMax[j][i]=posMax[j-1][i+(1<<(j-1))];
		return;
	}
	inline int query(reg int l,reg int r){
		reg int k=lg[r-l+1];
		if(cmp[posMax[k][l]]>cmp[posMax[k][r-(1<<k)+1]])
			return posMax[k][l];
		else
			return posMax[k][r-(1<<k)+1];
	}
}

void init(int N,std::vector<int> H){
	n=N;
	for(int i=0;i<N;++i)
		h[i+1]=H[i];
	h[0]=inf;
	reg int top=0;
	static int S[MAXN];
	for(reg int i=1;i<=n;++i){
		while(top&&h[S[top]]<h[i])
			rig[0][S[top--]]=i;
		lef[0][i]=S[top];
		S[++top]=i;
	}
	for(reg int i=1;i<=n;++i)
		if(h[lef[0][i]]>h[rig[0][i]])
			jmp[0][i]=lef[0][i];
		else
			jmp[0][i]=rig[0][i];
	for(reg int j=1;j<MAXLOG2N;++j)
		for(reg int i=1;i<=n;++i){
			lef[j][i]=lef[j-1][lef[j-1][i]];
			rig[j][i]=rig[j-1][rig[j-1][i]];
			jmp[j][i]=jmp[j-1][jmp[j-1][i]];
		}
	ST::Init(n,h);
	return;
}

int minimum_jumps(int A,int B,int C,int D){
	++A,++B,++C,++D;
	reg int Max_mid=ST::query(B,C-1),Max_rig=ST::query(C,D);
	if(h[Max_mid]>h[Max_rig])
		return -1;
	reg int p=B;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(A<=lef[i][p]&&h[lef[i][p]]<h[Max_rig])
			p=lef[i][p];
	if(h[Max_mid]<=h[p]&&h[p]<h[Max_rig])
		return 1;
	reg int sum=0;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(h[jmp[i][p]]<h[Max_mid]){
			sum+=1<<i;
			p=jmp[i][p];
		}
	if(h[Max_mid]<=h[jmp[0][p]]&&h[jmp[0][p]]<h[Max_rig])
		return sum+2;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(h[rig[i][p]]<h[Max_mid]){
			sum+=1<<i;
			p=rig[i][p];
		}
	return sum+2;
}