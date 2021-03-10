#include<cstdio>
#include<algorithm>
#include<fstream>
using namespace  std;
fstream reader, writer, writer2;

struct LinkEdge{
    int to;
    int nxt;
} edge[100001];
int head[100001];
int N, M;
int set[100001];
int res[100001];
bool visit[100001];
int dfn[100001];
int low[100001];

int Find(int a){
	if(set[a] < 0)
		return a;
	else {
		set[a] = Find(set[a]);
		return set[a];
	}
}

inline bool Connect(int a, int b) {
	a = Find(a);
    b = Find(b);
	if (a == b)
		return 0;
	if (set[a] <= set[b]) {
		set[a] += set[b];
		set[b] = a;
	}
	else {
		set[b] += set[a];
		set[a] = b;
	}
	return 1;
}

int seq;
void tarjan(int idx){
    dfn[idx] = low[idx] = ++seq;
    visit[seq] = 1;
    for(int i = head[idx], p; i != -1; i = edge[i].nxt){
        p = edge[i].to;
        if(!dfn[p]){
            tarjan(p);
            if(low[idx] > low[p]){
                low[idx] = low[p];
                Connect(p, idx);
            }
        }
        else if(visit[low[p]]){
            low[idx] = min(low[idx], low[p]);
            Connect(p, idx);
        }
    }
    visit[dfn[idx]] = 0;
}

int DFS(int idx){
    if(visit[idx])
        return res[Find(idx)];
    visit[idx] = 1;
    int i = head[idx], f = Find(idx);
    res[f] = max(res[f], idx);
    for(; i != -1; i = edge[i].nxt){
        res[f] = max(res[f], DFS(edge[i].to));
    }
    return res[f];
}

int main(){
    reader.open("/Users/silverknightmacair/Projects/VScode/Project/input.txt");
    writer.open("/Users/silverknightmacair/Projects/VScode/Project/output.txt");
    writer2.open("/Users/silverknightmacair/Projects/VScode/Project/output2.txt");
    if(!reader.is_open() || !writer.is_open()){
        printf("file open failure\n");
        assert(0);
    }

    reader >> N >> M;
    //scanf("%d%d", &N, &M);

    for(int i = 1; i <= N; ++i){
        head[i] = -1;
        set[i] = -1;
    }

    for(int i = 0, a, b; i != M; ++i){
        //scanf("%d%d", &a, &b);
        reader >> a >> b;
        if(a == 154 || b == 154)
            writer2 << i + 1 << '\n';
        edge[i].to = b;
        edge[i].nxt = head[a];
        head[a] = i;
    }

    for(int i = 1; i <= N; ++i)
        tarjan(i);
    for(int i = 1; i <= N; ++i)
        DFS(i);

    for(int i = 1; i <= N; ++i)
        //printf("%d ", res[Find(i)]);
        writer << res[Find(i)] << '\n';


    reader.close();
    writer.close();
    return 0;
}