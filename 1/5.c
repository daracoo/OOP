/*
За програмски јазик да се употреби C.


Од стандарден влез се внесува број n, број на кругови кои ќе се внесуваат, каде 0<n<100. Потоа во наредните n линии се внесуваат x и y кои го претставуваат центарот на кругот како и радиусот на кругот. На стандарден излез се печати плоштината и центарот само најголемиот круг (со најголема плоштина).



Напомена: Доколку има повеќе кругови со иста плоштина се печати само првиот круг со таа плоштина.



Во структурата Точка (Point) треба да се чуваат следните информации:

-x координата (int)

-y координата (int)



Во структурата Круг (Circle) треба да се чуваат следните информации:

-Центар (Point)

-Радиус (int)

For example:

Input	Result
3
1 2 3
4 5 6
3 2 3
        Largest circle has area of: 113.04 with centre: (4,5)
10
1 2 3
4 5 3
6 7 3
8 9 3
2 1 3
5 4 3
7 6 3
9 8 3
10 10 3
11 11 3
        Largest circle has area of: 28.26 with centre: (1,2)
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

struct Point{
    int x;
    int y;
};
typedef struct Point Point;

struct Circle{
    Point centar;
    int radius;
};
typedef struct Circle Circle;

int main()
{
    int n;
    scanf("%d", &n);
    Circle c[100];
    for(int i=0;i<n;i++){
        scanf("%d %d %d", &c[i].centar.x, &c[i].centar.y, &c[i].radius);
    }

    float maxArea=0;
    Point maxCenter;
    for(int i=0;i<n;i++){
        float currArea = c[i].radius * c[i].radius * 3.14;
        if(currArea > maxArea){
            maxArea = currArea;
            maxCenter = c[i].centar;
        }
    }

    printf("Largest circle has area of: %.2f with centre: (%d,%d)", maxArea, maxCenter.x, maxCenter.y);
}