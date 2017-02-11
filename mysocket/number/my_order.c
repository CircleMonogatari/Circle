#include "my_head.h"

void num_order(int *arr[])
{
    int num=sizeof(*arr);

    for(int i=0;i<num;i++)
        for(int j=0;j<num-i-1;j++)
        {
            if(*arr[j]<*arr[j+1])
            {
                *arr[j]=*arr[j]|*arr[j+1];
                *arr[j+1]=*arr[j]|*arr[j+1];
                *arr[j]=*arr[j]|*arr[j+1];

            }


        }


}
