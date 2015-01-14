#include <stdio.h>
#include <stdlib.h>

typedef struct { int x, y; } coord;
typedef struct { void* x; void* y; } tuple;

int main(int argc, char const *argv[]) {

    int cases;

    int offices, modems, cut, cheap, expensive;
    coord* coordinates;

    scanf("%d", &cases);

    for (; cases > 0; --cases) {

        scanf("%d %d %d %d %d", &offices, &modems, &cut, &cheap, &expensive);


        coordinates = (coord*) malloc(sizeof(coord) * offices);

        // read the offices coordinates
        for (int off = 0; off < offices; ++off) {
            scanf("%d %d", &(coordinates[off].x), &(coordinates[off].y));
        }

        for (int off = 0; off < offices; ++off) {
            printf("(%d, %d)\n", coordinates[off].x, coordinates[off].y);
        }

        // solution
        // priority_queue<tuple>
    }

    return 0;
}

