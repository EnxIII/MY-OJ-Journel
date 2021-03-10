// 2维递推  只需要打一次标记

#include<cstdio>

int mat[1002][1002];
int N, M;

int main(){
    scanf("%d%d", &N, &M);
    for(int i = 0, a, b, c, d; i < M; ++i){
        scanf("%d%d%d%d", &a, &b, &c, &d);
        ++mat[a][b]; --mat[a][d + 1]; --mat[c + 1][b]; ++mat[c + 1][d + 1];
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            printf("%d ", mat[i][j] += mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1]);
        }
        printf("\n");
    }

}