#include<cstdio>
#include<algorithm>
#include<fstream>
using namespace  std;
fstream reader, writer;

//#define max(a,b) (a ^ ((a ^ b) & -(a < b)))
//#define min(a,b) (a ^ ((a ^ b) & -(a > b)))
/*
    割点
    连通分量
*/

int N, M;
struct LinkEdge{
    int from;
    int to;
    int nxt;
} edge[100001], nedge[100001];
int head[10001];
int nhead[10001];
int wgt[10001];
int dfn[10001];
int low[10001];
int seq[10001];
int group[10001];
int res[10001];
bool visit[10001];

int Time, Top;
void Tarjan(int idx){
    seq[++Top] = idx;
    dfn[idx] = low[idx] = ++Time;
    visit[idx] = 1;
    for(int i = head[idx], p; i != 0; i = edge[i].nxt){
        p = edge[i].to;
        if(!dfn[p]){
            Tarjan(p);
            low[idx] = min(low[idx], low[p]);
        }
        else if(visit[p])
            low[idx] = min(low[idx], dfn[p]);
    }
    if(dfn[idx] == low[idx]){
        int t = seq[Top--];
        while(t != idx){
            visit[t] = 0;
            group[t] = idx;
            wgt[idx] += wgt[t];
            t = seq[Top--];
        }
        visit[idx] = 0;
        group[idx] = idx;
    }
}

void Rebuild(){
    for(int i = 1, j = 1, a, b; i <= M; ++i){
        a = group[edge[i].from];
        b = group[edge[i].to];
        if(a != b){
            nedge[j].to = b;
            nedge[j].from = a;
            nedge[j].nxt = nhead[a];
            nhead[a] = j++;
        }
    }
}
int Max;
int DFS(int idx){
    if(visit[idx])
        return wgt[idx];
    visit[idx] = 1;
    int i = nhead[idx], m = 0;
    for(; i != 0; i = nedge[i].nxt){
        m = max(m ,DFS(nedge[i].to));
    }
    wgt[idx] += m;
    Max = max(Max, wgt[idx]);
    return wgt[idx];
}

int main(){
    reader.open("/Users/silverknightmacair/Projects/VScode/Project/input.txt");
    writer.open("/Users/silverknightmacair/Projects/VScode/Project/output.txt");
    if(!reader.is_open() || !writer.is_open()){
        printf("file open failure\n");
        assert(0);
    }

    reader >> N >> M;
    //scanf("%d%d", &N, &M);

    for(int i = 1; i <= N; ++i)
        reader >> wgt[i];
        //scanf("%d", wgt + i);

    for(int i = 1, a, b; i <= M; ++i){
        reader >> a >> b;
        //scanf("%d%d", &a, &b);
        edge[i].from = a;
        edge[i].to = b;
        edge[i].nxt = head[a];
        head[a] = i;
    }
    for(int i = 1; i <= N; ++i)
        if(!dfn[i])
            Tarjan(i);
    Rebuild();
    for(int i = 1; i <= N; ++i)
        DFS(i);
    
    writer << Max << ' ';
    //printf("%d ", Max);

    reader.close();
    writer.close();
    return 0;
}
