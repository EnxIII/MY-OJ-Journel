#include<cstdio>
#include<algorithm>
#include<fstream>
using namespace  std;
fstream reader, writer;


#define max(x,y) (x ^ ((x ^ y) & -(x < y)))
#define min(x,y) (x ^ ((x ^ y) & -(x > y)))

struct Edge{
    int from;
    int to;
    int wgt;
    //Edge(int f, int t, int w) : from(f), to(t), wgt(w) {};
} edge[10001];
int cost[5001];
int top;

bool Bellman_Ford(int vertex, int v_num, int e_num){
    for(int i = 1; i <= v_num; ++i)
        cost[i] = 0x40000000;
    for(int i = 0 , a, b, c; i != v_num; ++i){
        for(int j = 0; j != e_num; ++j){
            a = edge[j].from;
            b = edge[j].to;
            c = edge[j].wgt + cost[a];
            cost[b] = min(cost[b], c);
        }
    }
    for(int i = 0, a, b; i != e_num; ++i){
        a = cost[edge[i].from] + edge[i].wgt;
        b = cost[edge[i].to];
        if(b > a)
            return 0;
    }
    return 1;
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

    for(int i = 1, a, b, c; i <= M; ++i){       // generating edge
        reader >> a >> b >> c;
        //scanf("%d%d%d", &a, &b, &c);
        edge[top].from = b;
        edge[top].to = a;
        edge[top].wgt = c;
        ++top;
    }
    for(int i = 1; i <= M; ++i){        // generate orignal vertex
        edge[top].from = 0;
        edge[top].to = i;
        edge[top].wgt = 0;
        ++top;
    }
    
    if(Bellman_Ford(0, N, top)){
        for(int i = 1; i <= N; ++i){
            writer << cost[i] << ' ';
            //printf("%d ", cost[i]);
        }
    }
    else{
        writer << "NO";
        //printf("NO");
    }

    reader.close();
    writer.close();
    return 0;
}
