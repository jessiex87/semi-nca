#include <algorithm>  
#include <cstdio>
#include <numeric>
using namespace std;

const int N = 100000, M = 500000;
struct Arc { int v, next; } pool[2*M], *pit;
int e[N], ee[N], domch[N], tick, dfn[N], rdfn[N], uf[N], sdom[N], best[N], idom[N];

void dfs(int u) {
  dfn[u] = tick;
  rdfn[tick++] = u;
  for (int v, a = e[u]; ~a; a = pool[a].next) {
    if (dfn[v = pool[a].v] < 0) {
      uf[v] = u;
      dfs(v);
    }
  }
}

int eval(int v, int cur) {
  if (dfn[v] <= cur)
    return v;
  int u = uf[v], r = eval(u, cur);
  if (dfn[best[u]] < dfn[best[v]])
    best[v] = best[u];
  return uf[v] = r;
}

void semiNca(int n, int r) {
  fill_n(idom, n, -1); // delete if unreachable nodes are not needed
  fill_n(dfn, n, -1);
  tick = 0;
  dfs(r);

  printf("DFN:");
  for (int i = 0; i < tick; i++) {
    printf("%d ", dfn[i]);
  }
  printf("\n");
  printf("RDFN:");
  for (int i = 0; i < tick; i++) {
    printf("%d ", rdfn[i]);
  }

  iota(best, best+n, 0);

  printf("BEST:");
  for (int i = 0; i < tick; i++) {
    printf("best[%d]: %d\n", i, best[i]);
  }

  for (int i = tick; --i; ) {
    int v = rdfn[i], u;

    // printf("THIS IS V: %d\n", v);

    sdom[v] = v;

    printf("SDOM:\n");
    for (int j = 0; j < tick; j++) {
      printf("sdom[%d]: %d\n ", j, sdom[j]);
    }
    // printf("Sdom[%d]: %d\n", v, sdom[v]);  // sdom values should at this piont match rdfn (?); values same as index


    for (int a = ee[v]; ~a; a = pool[a].next)
      if (~dfn[u = pool[a].v]) {
        printf("ENTERED \n");
        eval(u, i);
        if (dfn[best[u]] < dfn[sdom[v]])
          printf("2ENTERED \n");
          sdom[v] = best[u];
      }
    best[v] = sdom[v];
    idom[v] = uf[v];

    printf("CHECK OVER HERE\n");
    printf("V: %d\n", v);
    printf("3BEST:\n");
    for (int i = 0; i < tick; i++) {
      printf("best[%d]: %d\n", i, best[i]);
    }
    printf("3SDOM:\n");
    for (int i = 0; i < tick; i++) {
      printf("sdom[%d]: %d\n ", i, sdom[i]);
    }
    printf("3IDOM:\n");  // -1, 0 , -1
    for (int i = 0; i < tick; i++) {
      printf("idom[%d]: %d\n ", i, idom[i]);
    }
    printf("3UF:\n");
    for (int i = 0; i < tick; i++) {
      printf("uf[%d]: %d\n ", i, uf[i]);
    }

  }

  // // check sdom
  // printf("SDOM:\n");
  // for (int i = 0; i < tick; i++) {
  //   printf("sdom[%d]: %d\n ", i, sdom[i]);
  // }

  printf("BEST AFTER\n");
  for (int i = 0; i < tick; i++) {
    printf("best[%d]: %d\n", i, best[i]);
  }


  for (int i = 1; i < tick; i++) {
    int v = rdfn[i];
    while (dfn[idom[v]] > dfn[sdom[v]])
      idom[v] = idom[idom[v]];
  }
}

int main() {
  int n, m;
  printf("enter n, m");
  scanf("%d%d", &n, &m);
  pit = pool;
  fill_n(e, n, -1);
  fill_n(ee, n, -1);
  fill_n(domch, n, -1);
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    Arc temp_arc = {v, e[u]};
    *pit = temp_arc;
    // *pit = Arc(v, e[u]);
    e[u] = pit++-pool;

    Arc temp_arc2 = {u, ee[v]};
    *pit = temp_arc2;
    // *pit = Arc(u, ee[v]);
    ee[v] = pit++-pool;
  }
  semiNca(n, 0);

  // for (int i = 0; i < n; i++)
  //   printf("%d: %d\n", i, sdom[i]);

  
  printf("IDOM:");
  for (int i = 0; i < n; i++)
    printf("%d: %d\n", i, idom[i]);

  printf("POOL:\n");
  for (int i = 0; i < pit - pool; i++) {
    printf("Index: %d, v: %d, next: %d\n", i, pool[i].v, pool[i].next);
  }

  printf("OUTGOING\n");
  for (int i = 0; i < n; i++) {
    for (int a = e[i]; ~a; a = pool[a].next) {
      printf("index: %d, Arc { v: %d, next: %d }\n", i, pool[a].v, pool[a].next);
    }
  }

  printf("INCOMING\n");
  for (int i = 0; i < n; i++) {
    for (int a = ee[i]; ~a; a = pool[a].next) {
      printf("index: %d, Arc { v: %d, next: %d }\n", i, pool[a].v, pool[a].next);
    }
  }
}