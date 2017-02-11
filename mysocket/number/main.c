#include "my_head.h"

int main(int argc, const char* argv[])
{
    int arr[]={1,4,3,5,4,3,7,8,4,2};
    num_order(&arr);

    for(int i=0;i<sizeof(arr);i++)
        printf("%d ",i);
    return 0;
}
