const int MAXN=3e4+5;
const int MAXLOG2N=15+1;
const int MAXLOG3N=10+1;

bool flag;
char f[MAXN][MAXLOG2N][MAXLOG3N];
int base3[MAXLOG3N];

inline int getCeilLog(int n,int base){
	int res=0,x=1;
	while(x<n)
		x*=base,++res;
	return res;
}

extern "C" int _opt(int n,int x,int y){
	if(!flag){
		flag=true;
		int log2n=getCeilLog(n,2),log3n=getCeilLog(n,3);
		base3[0]=1;
		for(int i=1;i<=log3n;++i)
			base3[i]=base3[i-1]*3;
		for(int i=n;i>=0;--i)
			for(int j=log2n;j>=0;--j)
				for(int k=log3n;k>=0;--k)
					if((1<<j)*base3[k]+i>=n)
						f[i][j][k]=0;
					else
						if(!f[i][j+1][k])
							f[i][j][k]=2;
						else if(!f[i][j][k+1])
							f[i][j][k]=3;
						else if(!f[i+(1<<j)*base3[k]][0][0])
							f[i][j][k]=1;
						else
							f[i][j][k]=0;
	}
	int cnt2=0,cnt3=0;
	while(x&&(!(x&1)))
		++cnt2,x>>=1;
	while(x&&(!(x%3)))
		++cnt3,x/=3;
	return f[y][cnt2][cnt3];
}