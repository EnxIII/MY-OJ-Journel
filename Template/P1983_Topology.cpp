#include<cstdio>
#include<algorithm>
#include<fstream>
using namespace  std;
fstream reader, writer;
#define max(x,y) (x ^ ((x ^ y) & -(x < y)))
#define STACKSIZE 0x1fff

struct LinkEdge{
    int nxt;
    int to;
} edge [1501];  // 10000
int head[2001];
int degree[2001];
int level[2001];
int seq[2048];
int top;

void AddEdge(int from, int to){
    static int top = 1;
    edge[top].to = to;
    edge[top].nxt = head[from];
    head[from] = top;
    ++top;
    ++degree[to];
}

int main(){
    reader.open("/Users/silverknightmacair/Projects/VScode/Project/input.txt");
    writer.open("/Users/silverknightmacair/Projects/VScode/Project/output.txt");
    if(!reader.is_open() || !writer.is_open()){
        printf("file open failure\n");
        assert(0);
    }

    int N, M;
    reader >> N >> M;
    //scanf("%d%d", &N, &M);

    int n = N + 1;
    for(int i = 0, j, t, h; i != M; ++i, ++n){
        reader >> j >> h;
        //scanf("%d%d", &j, &h);
        AddEdge(h, n);
        for(--j; j > 0; --j){
            reader >> t;
            //scanf("%d", &t);
            AddEdge(t, n);
            for(++h; h != t; ++h)
                AddEdge(n, h);
        }
    }

    for(int i = 1; i <= N; ++i){
        if(!degree[i]){
            seq[top++] = i;
            level[i] = 1;
        }
    }
    int MAX = 0;
    for(int i = 0; i != top; (++i) &= STACKSIZE){
        MAX = max(MAX, level[seq[i]]);
        for(int j = head[seq[i]], p, nl; j != 0; j = edge[j].nxt){
            p = edge[j].to;
            nl = level[seq[i]] + (p <= N);
            level[p] = max(level[p], nl);
            if(--degree[p] == 0){
                seq[top] = p;
                (++top) &= STACKSIZE;
            }
        }
    }

    writer << MAX;
    
    reader.close();
    writer.close();
    return 0;
}
