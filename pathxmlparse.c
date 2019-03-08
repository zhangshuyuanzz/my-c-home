#include <libxml/parser.h>  
#include <libxml/xmlstring.h>  

#include <libxml/xpath.h>  
//#include <rgb_api.h>

#define PARSE_FILE "for_data.xml"
#define PARSE_NODE "//book"
#define PARSE_ATTR "content"


void  func_free(xmlChar **data_p)
{
	if(*data_p != NULL)
		xmlFree(*data_p);
	*data_p = NULL;
	return;
}
void func_print_xmlpath_result(xmlNodeSetPtr node_set_ptr)
{
	int i = 0;
	for(i = 0;i < node_set_ptr->nodeNr;i++){
		xmlChar *x_data= xmlGetProp(node_set_ptr->nodeTab[i],BAD_CAST(PARSE_ATTR));
		//Ddebug_log(RGB_NORMAL, "x_data=%s ",x_data);
		func_free(&x_data);
		xmlChar *content_data = xmlNodeGetContent(node_set_ptr->nodeTab[i]);
		//Ddebug_log(RGB_NORMAL, "content_data=%s ",content_data);
		func_free(&content_data);
	 }
	return;
}

int main()
{
	//Ddebug_log(RGB_NORMAL, "main start ");
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL;
	//xmlParseDoc(const xmlChar * cur);

	xmlKeepBlanksDefault(0);
	pdoc = xmlParseFile(PARSE_FILE);

	if(pdoc == NULL){
		//Ddebug_log(RGB_RED, "open file error ");
		return 1;
	}
	proot = xmlDocGetRootElement(pdoc);
	if(proot == NULL){
		//Ddebug_log(RGB_RED, "get root node error ");
		return 1;
	}
	xmlChar *xml_cmd = BAD_CAST(PARSE_NODE);
	//xmlXPathObjectPtr result = getNodeset(pdoc, xpath);
	//Ddebug_log(RGB_NORMAL, "xml_cmd=%s ",xml_cmd);

	//获取xpath符合结果的数据
	xmlXPathContextPtr xml_context = NULL;
	xmlXPathObjectPtr xml_data = NULL;
	xml_context = xmlXPathNewContext(pdoc);
	
	xml_data =xmlXPathEvalExpression(xml_cmd, xml_context);
	
	xmlXPathFreeContext(xml_context);
	
	if(xmlXPathNodeSetIsEmpty(xml_data->nodesetval)){
		//Ddebug_log(RGB_RED, "get data empty");
		xmlXPathFreeObject(xml_data);
		return 1;
	}
	//Ddebug_log(RGB_NORMAL, "stringval=%s-- type[%d]nodeNr[%d]nodeMax[%d]",xml_data->stringval,xml_data->type,xml_data->nodesetval->nodeNr,xml_data->nodesetval->nodeMax);
	func_print_xmlpath_result(xml_data->nodesetval);
	return 0;
}
