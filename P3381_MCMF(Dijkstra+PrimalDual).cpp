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
int ncost[V_NUM];
bool in_queue[V_NUM];
int Queue[8192];
int L, R, S, T, v_num, e_num;

inline void push(int i){ Queue[++R &= 0x1fff] = i;}
inline int pop(){ return Queue[++L &= 0x1fff];} 
inline bool empty(){ return L == R;}

bool SPFA(){
    memset(ncost, 0x3f, sizeof(ncost));
    memset(in_queue, 0, sizeof(in_queue));
    ncost[S] = 0;
    push(S);
    int v;
    while (!empty()){
        v = pop();
        in_queue[v] = 0;
        for(int i = head[v], j; i != 0; i = edge[i].nxt){
            j = edge[i].to;
            if(edge[i].cap && (ncost[j] > ncost[v] + edge[i].cost)){
                ncost[j] = ncost[v] + edge[i].cost;
                if(!in_queue[j]){
                    in_queue[j] = 1;
                    push(j);
                }
            }
        }
    }
    return ncost[T] != INF;
}

struct Pair{
    int dis;
    int vertex;
    bool operator<(const Pair&a)const{
        return dis > a.dis;
    }
};
int nxt_v[V_NUM];
int nxt_e[V_NUM];
int sum_cost;
priority_queue<Pair> Q;
bool Dijkstra(){
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
        for(int i = head[v], j, c; i != 0; i = edge[i].nxt){
            j = edge[i].to;
            c = cost[v] + ncost[v] - ncost[j] + edge[i].cost;
            if(!in_queue[j] && edge[i].cap && cost[j] > c){
                cost[j] = c;
                nxt_v[j] = v;
                nxt_e[j] = i;
                Q.push((Pair){cost[j], j});
            }
        }
    }
    return cost[T] != INF;
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
    SPFA();
    int ans = 0, min_flow;
    while (Dijkstra()){
        for(int i = 1; i <= v_num; ++i)
            ncost[i] += cost[i];
        min_flow = 0x7fffffff;
        for(int i = T, e = nxt_e[T]; i != S; i = nxt_v[i], e = nxt_e[i])
            min_flow = min(min_flow, edge[e].cap);
        for(int i = T, e = nxt_e[T]; i != S; i = nxt_v[i], e = nxt_e[i]){
            edge[e].cap -= min_flow;
            edge[e ^ 1].cap += min_flow;
        }
        sum_cost += ncost[T] * min_flow;
        ans += min_flow; 
    }

    printf("%d %d", ans, sum_cost);
    return 0;
}