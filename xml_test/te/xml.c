#include "mxml.h"

int main(int argc, const char* argv[])
{

    FILE *fp=fopen("test.xml","w");

    mxml_node_t *xml=mxmlNewXML("1.1");
    mxml_node_t *node=mxmlNewElement(xml,"node");
        
        //node_son
        mxml_node_t *student=mxmlNewElement(node,"student");
            //son_son
            mxml_node_t *s_name=mxmlNewElement(student,"s_name");
            mxmlNewText(s_name,0,"老何");
            mxmlElementSetAttr(s_name,"name","中文");

        mxml_node_t *teacher=mxmlNewElement(node,"teacher");
            mxml_node_t* t_name=mxmlNewElement(teacher,"t_name");
            mxmlNewText(t_name,0,"wangfei");
            mxmlElementSetAttr(t_name,"name","English");

    mxmlSaveFile(xml,fp,MXML_NO_CALLBACK);

    return 0;
}
