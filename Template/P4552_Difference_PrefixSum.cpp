#include<cstdio>
#include<algorithm>
using namespace  std;

#define max(x,y) (x ^ ((x ^ y) & -(x < y)))
#define min(x,y) (x ^ ((x ^ y) & -(x > y)))
#define Max_Size 100010

int list[Max_Size];
int N;

int main(){
    scanf("%d", &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d", list + i);
        list[i - 1] = list[i] - list[i - 1];
    }

    long long pos = 0, neg = 0;
    for(int i = 1; i < N; ++i){
        if(list[i] >= 0)
            pos += list[i];
        else 
            neg -= list[i];
    }

    printf("%lld\n%lld", max(neg, pos), 1 + abs(pos - neg));
    return 0;
}
