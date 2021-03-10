#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace  std;

#define VecProduct(a1,a2,b1,b2) ((a1.x-a2.x) * (b1.y-b2.y) - (b1.x-b2.x) * (a1.y-a2.y))

int N, Top = -1;
struct Vertex{
    double x;
    double y;
} cord[100000], Stack[100000];

bool cmp(Vertex &a, Vertex& b){
    double res = VecProduct(a, cord[0], b, cord[0]);
    return(res > 0 || (res == 0 && (abs(b.y) < abs(a.y))));
}

int main(){
    scanf("%d", &N);
    scanf("%lf%lf", &cord[0].x, &cord[0].y);
    for(int i = 1; i < N; ++i){
        scanf("%lf%lf", &cord[i].x, &cord[i].y);
        if(cord[i].y < cord[0].y){
            Vertex tmp = cord[0];
            cord[0] = cord[i];
            cord[i] = tmp;
        }
    }
    sort(cord + 1, cord + N, cmp);
    Stack[++Top] = cord[0];
    for(int i = 1; i < N; ++i){
        while(Top >= 2 && VecProduct(cord[i], Stack[Top], Stack[Top - 1], Stack[Top]) <= 0)
            --Top;
        Stack[++Top] = cord[i];
    }
    double len = 0, t1, t2;
    Stack[++Top] = Stack[0];
    for(int i = 1; i <= Top; ++i){
        t1 = Stack[i].x - Stack[i-1].x;
        t1 *= t1;
        t2 = Stack[i].y - Stack[i-1].y;
        t2 *= t2;
        len += sqrt(t1 + t2);
    }
    
    printf("%.2lf\n", len);
    return 0;
}
