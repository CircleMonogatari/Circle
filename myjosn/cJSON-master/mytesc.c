#include "cJSON.h"

int main(int argc, const char* argv[])
{

    FILE*fd=fopen("myjson.json","w");
    cJSON *json = cJSON_CreateObject();//创建一个空对象
    //{}
    cJSON_AddItemToObject(json,"name",cJSON_CreateString("大锤王"));
    //cJSON_AddStringToObject(json,"name","大锤王");

    cJSON_AddItemToObject(json,"age",cJSON_CreateNumber(18));
    //cJSON_AddNumberToObject(json,"age",18);

    cJSON *array =NULL;
    array=cJSON_CreateArray();
    cJSON_AddItemToObject(json,"love",array);
    //cJSON_AddItemToObiect(json,"love",array=cJSON_CreateArray());
    cJSON_AddItemToObject(array,cJSON_CreataeString("LOL"));
    cJSON_AddItemToObject(array,cJSON_CreateNumber(500));

    char *p=cJSON_Print(json);
    fwrite(p,1,strlen(p),fd)
    fclose(fd);

    return 0;
}
