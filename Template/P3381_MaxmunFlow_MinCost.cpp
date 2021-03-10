#include<cstdio>
#include<cstring>
#include<queue>
using namespace  std;
#define max(x,y) (x ^ ((x ^ y) & -(x < y)))
#define min(x,y) (x ^ ((x ^ y) & -(x > y)))
#define INF 0x3f3f3f3f
#define V_NUM 5010
#define E_NUM 50010
struct LinkEdge{
    int to;
    int cap;
    int cost;
    int nxt;
} edge[E_NUM << 1];
int head[V_NUM];
int nhead[V_NUM];
int cost[V_NUM];
bool in_queue[V_NUM];
int Queue[8192]; // 0x2000
int L, R, S, T, v_num, e_num;

inline void push(int i){ Queue[++R &= 0x1fff] = i;}
inline int pop(){ return Queue[++L &= 0x1fff];} 
inline bool empty(){ return L == R;}

bool SPFA(int s, int t){
    for(int i = 1; i <= v_num; ++i){
        nhead[i] = head[i];
    }
    memset(cost, 0x3f, sizeof(cost));
    memset(in_queue, 0, sizeof(in_queue));
    cost[s] = 0;
    push(s);
    int v;
    while (!empty()){
        v = pop();
        in_queue[v] = 0;
        for(int i = head[v], j; i != 0; i = edge[i].nxt){
            j = edge[i].to;
            if(edge[i].cap && (cost[j] > cost[v] + edge[i].cost)){
                cost[j] = cost[v] + edge[i].cost;
                if(!in_queue[j]){
                    in_queue[j] = 1;
                    push(j);
                }
            }
        }
    }
    return cost[t] != INF;
}

struct Pair{
    int dis;
    int vertex;
    bool operator<(const Pair&a)const{
        return dis > a.dis;
    }
};

priority_queue<Pair> Q;
bool Dijkstra(){                // unable to process neg-weight edge
    for(int i = 1; i <= v_num; ++i)
        nhead[i] = head[i];
    memset(cost, 0x3f, sizeof(cost));
    memset(in_queue, 0, sizeof(in_queue));
    cost[S] = 0;
    Q.push((Pair){0, S});
    int v;
    while(!Q.empty()){
        v = Q.top().vertex;
        Q.pop();
        if(in_queue[v])
            continue;
        in_queue[v] = 1;
        for(int i = head[v], j; i != 0; i = edge[i].nxt){
            j = edge[i].to;
            if(edge[i].cap && cost[j] > cost[v] + edge[i].cost){
                cost[j] = cost[v] + edge[i].cost;
                Q.push((Pair){cost[j], j});
            }
        }
    }
    return cost[T] != INF;
}

int in[V_NUM];
int out[V_NUM];
int min_cost;
int DFS(int cur){
    if(cur == T)
        return in[T];
    in_queue[cur] = 1;
    out[cur] = 0;
    for(int i = head[cur], j, res; i != 0 && in[cur]; i = edge[i].nxt){
        j = edge[i].to;
        nhead[cur] = i;
        if(!in_queue[j] && edge[i].cap && cost[j] == cost[cur] + edge[i].cost){
            in[j] = min(in[cur], edge[i].cap);
            res = DFS(j);
            if(res){
                min_cost += res * edge[i].cost;
                edge[i].cap -= res;
                edge[i ^ 1].cap += res;
                in[cur] -= res;
                out[cur] += res;
            }
        }
    }
    if(in[cur] == 0)
        in_queue[cur] = 0;
    return out[cur];
}

int main(){
    scanf("%d%d%d%d", &v_num, &e_num, &S, &T);
    e_num <<= 1;
    for(int i = 2, a, b, c, d; i <= e_num; i += 2){
        scanf("%d%d%d%d", &a, &b, &c, &d);
        edge[i].to = b;
        edge[i].cap = c;
        edge[i].cost = d;
        edge[i].nxt = head[a];
        head[a] = i;
        edge[i + 1].to = a;
        edge[i + 1].cap = 0;
        edge[i + 1].cost = -d;
        edge[i + 1].nxt = head[b];
        head[b] = i + 1;
    }

    in[S] = 0x7fffffff;
    int ans = 0;
    while (Dijkstra()){
        ans += DFS(S);
    }
    
    printf("%d %d", ans, min_cost);
    
    return 0;
}
