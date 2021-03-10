#include<cstdio>
#include<cstring>
using namespace  std;

#define min(a,b) (a ^ ((a ^ b) & -(a > b)))

int N, M, S, T;
struct LinkEdge{
    int to;
    int wgt;
    int nxt;
} edge[20001];
int head[201];
int nhead[201];
long long in[201];
long long out[201];

int L, R;
int Stack[200];
int level[201];

bool BFS(){
    memset(level, 0, sizeof(level));
    level[S] = 1;
    Stack[L = R = 0] = S;
    while(L <= R){
        int v = Stack[L++];
        nhead[v] = head[v];
        for(int i = head[v], t; i != 0; i = edge[i].nxt){
            t = edge[i].to;
            if(!level[t] && edge[i].wgt){
                level[t] = level[v] + 1;
                if(t == T) return 1;
                Stack[++R] = t;
            }
        }
    }
    return 0;
}

long long DFS(int cur){
    if(cur == T)
        return in[T];
    out[cur] = 0;
    for(int i = nhead[cur], t, res; i && in[cur]; i = edge[i].nxt){
        nhead[cur] = i;
        t = edge[i].to;
        if((level[t] == level[cur] + 1) && (edge[i].wgt > 0)){
            in[t] = min(in[cur], edge[i].wgt);
            res = DFS(t);
            edge[i].wgt -= res;
            edge[i ^ 1].wgt += res;
            out[cur] += res;
            in[cur] -= res;
        }
    }
    if(in[cur] != 0)
        level[cur] = 0;
    return out[cur];
}

int main(){
    scanf("%d%d%d%d", &N, &M, &S, &T);
    M <<= 1;
    for(int i = 2, a, b, w; i <= M; i += 2){
        scanf("%d%d%d", &a, &b, &w);
        edge[i].to = b;
        edge[i].wgt = w;
        edge[i].nxt = head[a];
        head[a] = i;
        edge[i + 1].to = a;
        edge[i + 1].wgt = 0;
        edge[i + 1].nxt = head[b];
        head[b] = i + 1;
    }
    long long ans = 0;
    while(BFS()){
        in[S] = 2005020600;
        ans += DFS(S);
    }
    printf("%lld\n", ans);
    return 0;
}