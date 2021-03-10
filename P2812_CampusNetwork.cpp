#include<cstdio>
using namespace  std;

#define max(x,y) (x ^ ((x ^ y) & -(x < y)))
#define min(x,y) (x ^ ((x ^ y) & -(x > y)))
#define V_NUM 10010
#define E_NUM 5000010
struct LinkEdge{
    int to;
    int nxt;
} edge[E_NUM], rvedge[E_NUM];
int head[V_NUM];
int rvhead[V_NUM];
bool visit[V_NUM];
int Stack[V_NUM];
int Group[V_NUM];
int N, M, T, G;

void DFS(int cur){
    visit[cur] = 1;
    for(int i = head[cur]; i; i = edge[i].nxt){
        if(!visit[edge[i].to])
            DFS(edge[i].to);
    }
    Stack[++T] = cur;
}

void ReDFS(int cur){
    Group[cur] = G;
    for(int i = rvhead[cur]; i; i = rvedge[i].nxt){
        if(!Group[rvedge[i].to])
            ReDFS(rvedge[i].to);
    }
}

int in[V_NUM];
int out[V_NUM];
int inz, outz;
void in_out_DFS(int cur){
    visit[cur] = 0;
    for(int i = head[cur], j; i; i = edge[i].nxt){
        j = edge[i].to;
        if(Group[cur] != Group[j]){
            if(in[Group[j]]++ == 0)
                --inz;
            if(out[Group[cur]]++ == 0)
                --outz;
        }
        if(visit[j])
            in_out_DFS(j);
    }
}

int Kosaraju(){
    for(int i = 1; i <= N; ++i)
        if(!visit[i])
            DFS(i);
    for(; T != 0; --T)
        if(!Group[Stack[T]]){
            ++G;
            ReDFS(Stack[T]);
        }
    inz = outz = G;
    for(int i = 1; i <= N; ++i)
        if(visit[i])
            in_out_DFS(i);
    return G;
}


int main(){
    scanf("%d", &N);
    for(int i = 1, a; i <= N; ++i){
        scanf("%d", &a);
        while(a != 0){
            edge[++M].to = a;
            edge[M].nxt = head[i];
            head[i] = M;
            rvedge[M].to = i;
            rvedge[M].nxt = rvhead[a];
            rvhead[a] = M;
            scanf("%d", &a);
        }
    }    
    Kosaraju();
    printf("%d\n%d", inz, max(inz, outz));
    return 0;
}