#include "week11_bonus.h"
#include <stdio.h>
stbrp_context context;

struct stbrp_rect rects[100];
int main(){
for (int i=0; i< 100; i++)
{
    rects[i].id = i;
    rects[i].w = 123+i;
    rects[i].h = 60+i;
    rects[i].x = 0;
    rects[i].y = 0;
    rects[i].was_packed = 0;
}

int rectsLength = sizeof(rects)/sizeof(rects[0]);

int nodeCount = 4096*2;
struct stbrp_node nodes[nodeCount];


stbrp_init_target(&context, 1024, 4096, nodes, nodeCount);
stbrp_pack_rects(&context, rects, rectsLength);
    printf("Height is %d\n ",rects[0].y);
for (int i=0; i< 100; i++)
{
    //printf("rect %i (%hu,%hu) was_packed=%i\n", rects[i].id, rects[i].x, rects[i].y, rects[i].was_packed);
}
}
