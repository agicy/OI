#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <random>
#include <unordered_map>
#include <vector>

#include "hypercube.h"

using namespace std;

#define LOG(f...) fprintf(stderr, f)

namespace sample_grader {
const char token[] = "Correct!";

mt19937 rng;

const int N = 3005;
const int LOG_LIM = 500;

vector<int> G[N];
int st[16][N * 2];
int lg[N * 2];
int fst[N], dep[N], dis[N], euler_dfc = 0, dfc = 0;
int dfn[N];

void DFS(int x, int fa = 0) {
  dis[x] = dis[fa] ^ x;
  st[0][++euler_dfc] = x;
  fst[x] = euler_dfc;
  dfn[++dfc] = x;
  if (fa)
    G[x].erase(find(begin(G[x]), end(G[x]), fa));
  for (int v : G[x]) {
    dep[v] = dep[x] + 1;
    DFS(v, x);
    st[0][++euler_dfc] = x;
  }
}

int min_dep(int x, int y) { return dep[x] < dep[y] ? x : y; }

void pre_log2() {
  for (int i = 2; i < (N * 2); i <<= 1)
    lg[i] = 1;
  for (int i = 3; i < (N * 2); ++i)
    lg[i] += lg[i - 1];
}
void build_st() {
  for (int i = 1; i <= lg[euler_dfc]; ++i)
    for (int j = 1, li = euler_dfc - (1 << i) + 1; j <= li; ++j)
      st[i][j] = min_dep(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}

int LCA(int x, int y) {
  x = fst[x];
  y = fst[y];
  if (x > y)
    swap(x, y);
  int k = lg[y - x + 1];
  return min_dep(st[k][x], st[k][y - (1 << k) + 1]);
}

unordered_map<uint32_t, bool> edges;
int cnt_query = 0;
int n, Q, data_type;
int reported = 0;
}  // namespace sample_grader

int query(int u, const vector<int> &S) {
  using namespace sample_grader;
  ++cnt_query;
  if (cnt_query > Q * 1.16)
    printf("FAIL : Query limit exceeded\n"), exit(0);
  if ((int)S.size() < 1)
    printf("FAIL : Query with |S| < 1\n"), exit(0);
  if (u < 1 || u > n)
    printf("FAIL : Vectex id not in [1, n]\n"), exit(0);
  for (int x : S)
    if (x < 1 || x > n)
      printf("FAIL : Vertex id not in [1, n]\n"), exit(0);

  int ans = 0;
  vector<int> A = S;
  sort(A.begin(), A.end());
  if (unique(A.begin(), A.end()) != A.end())
    printf("FAIL : Duplicate vertices in single query\n"), exit(0);
  for (int x : S) {
    ans ^= dis[x] ^ dis[u] ^ LCA(x, u);
  }
  return ans;
}

void report(int u, int v) {
  using namespace sample_grader;
  if (u < 1 || u > n)
    printf("FAIL : Report u not in [1, n]\n"), exit(0);
  if (v < 1 || v > n)
    printf("FAIL : Report v not in [1, n]\n"), exit(0);
  if (u > v)
    swap(u, v);
  uint32_t id = uint32_t(u) << 15 | uint32_t(v);
  auto it = edges.find(id);
  if (it == edges.end())
    printf("FAIL : Reported edge (%d, %d) does not exist\n", u, v), exit(0);
  if (it->second)
    printf("FAIL : Duplicate edge (%d, %d) reported\n", u, v), exit(0);
  it->second = true;
  ++reported;
}

double f(double x) {
  if (x <= 1)
    return 1;
  else
    return std::min(-6 * std::exp(x - 1) + 7, 0.);
}

int main() {
  freopen("hypercube.in", "r", stdin);
  freopen("hypercube.out", "w", stdout);
  using namespace sample_grader;
  pre_log2();
  int T;
  double x = 0;
  assert(scanf("%d", &T) == 1);
  for (int caseid = 1; caseid <= T; ++caseid) {
    euler_dfc = 0;
    dfc = 0;
    assert(scanf("%d%d%d", &n, &Q, &data_type) == 3);
    edges.clear();
    reported = 0;
    cnt_query = 0;
    for (int i = 1; i <= n; ++i)
      G[i].clear();
    for (int i = 1; i < n; ++i) {
      int u, v;
      assert(scanf("%d%d", &u, &v) == 2);
      if (u > v)
        swap(u, v);
      edges.emplace(uint32_t(u) << 15 | uint32_t(v), false);
      G[u].emplace_back(v);
      G[v].emplace_back(u);
    }
    assert((int)edges.size() == n - 1);
    DFS(1);
    build_st();

    solve(n, Q, data_type);
    if (reported != n - 1)
      printf("FAIL : Some edges not reported\n"), exit(0);
    printf("%d %d\n", cnt_query, Q);
    x = std::max(x, cnt_query * 1. / Q);
  }
  printf("%s\n", token);
  printf("Your score : %d\n", int(f(x) * 100));
  printf("Real time : %lldms\n", clock() * 1000LL / CLOCKS_PER_SEC);
  return 0;
}
