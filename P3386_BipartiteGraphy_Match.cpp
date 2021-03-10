#include<cstdio>
#include<cstring>
using namespace  std;

int N, M, E;
struct LinkEdge{
    int to;
    int nxt;
    int wgt;
}edge[10010];
int head[1001];
int nhead[1001];
int level[1001];
int st[1001];
bool vis[501][501];
int Stack[1001];
int R, L;

bool BFS(){
    memset(level, 0, sizeof(level));
    L = R = 0;
    for(int i = 1; i <= N; ++i)
        if(st[i] == 0){  // avaliable
            Stack[R++] = i;
            nhead[i] = head[i];
            level[i] = 1;
        }
    int v;
    while(L <= R){
        v = Stack[L++];
        if(st[v] == 0 && v > N)
            return 1;
        for(int i = head[v], j; i != 0; i = edge[i].nxt){
            j = edge[i].to;
            if(!level[j] && edge[i].wgt){
                Stack[R++] = j;
                nhead[j] = head[j];
                level[j] = level[v] + 1;
            }
        }
    }
    return 0;
}


bool DFS(int cur){
    if(!st[cur] && cur > N)
        return (st[cur] = 1);
    for(int i = nhead[cur], j; i; i = edge[i].nxt){
        nhead[cur] = i;
        j = edge[i].to;
        if(level[j] == level[cur] + 1 && edge[i].wgt){
            if(DFS(j)){
                edge[i].wgt = 0;
                edge[i ^ 1].wgt = 1;
                return 1;
            }
        }
    }
    level[cur] = 0;
    return 0;
}


int main(){
    scanf("%d%d%d", &N, &M, &E);
    for(int i = 0, j = 1, a, b; i != E; ++i){
        scanf("%d%d", &a, &b);
        if(!vis[a][b]){
            vis[a][b] = 1;
            b += N;
            edge[++j].to = b;
            edge[j].wgt = 1;
            edge[j].nxt = head[a];
            head[a] = j;
            edge[++j].to = a;
            edge[j].wgt = 0;
            edge[j].nxt = head[b];
            head[b] = j;
        }
    }

    int ans = 0;
    while(BFS())
        for(int i = 1; i <= N; ++i)
            if(st[i] == 0 && DFS(i))
                ++ans, st[i] = 1;

    printf("%d", ans);
    return 0;
}

