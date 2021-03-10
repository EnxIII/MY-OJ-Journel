#include<cstdio>
using namespace  std;

#define max(x,y) (x ^ ((x ^ y) & -(x < y)))
#define Max_Size 5010

int map[Max_Size][Max_Size];
int N, M, X, Y;

int main(){
    scanf("%d%d", &N, &M);
    for(int i = 1, a, b, c; i <= N; ++i){
        scanf("%d%d%d", &a, &b, &c);
        a += 1;
        b += 1;
        X = max(X, a);
        Y = max(Y, b);
        map[a][b] = c;
    }
    for(int i = 1; i <= X; ++i){
        for(int j = 1; j <= Y; ++j){
            map[i][j] += map[i][j - 1] + map[i - 1][j] - map[i - 1][j - 1];
        }
    }
    if(M > X){
        int MY = 0, temp;
        for(int j = M; j <= Y; ++j){
            temp = map[X][j] - map[X][j - M];
            MY = max(MY, temp);   
        }
        printf("%d", MY);
        return 0;
    }
    int ans = 0, temp;
    for(int i = M; i <= X; ++i){
        for(int j = M; j <= Y; ++j){            
            temp = map[i][j] - map[i][j - M] - map[i - M][j] + map[i - M][j - M];
            ans = max(ans, temp);
        }
    }
    printf("%d", ans);
    return 0;
}
