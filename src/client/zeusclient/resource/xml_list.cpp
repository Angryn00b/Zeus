#include "xml_list.h"
#include "cpicturexml_parse.h"

CXMLResource* Singleton<CXMLResource>::m_pInst = NULL;

CXMLResource::CXMLResource()
{
}

CXMLResource::~CXMLResource()
{
}

bool CXMLResource::Initialize()
{
		return true;
}

bool CXMLResource::LoadXML(const std::string& strPath)
{
	TiXmlDocument XmlParse;

	if (strPath.empty())
	{
			return false;
	}

	if (XmlParse.LoadFile(strPath.c_str()))
	{
			return _Parse(XmlParse);
	}
	return true;
}


bool CXMLResource::_Parse(TiXmlDocument& tiDoc)
{
	TiXmlElement* tiRoot = tiDoc.RootElement();
	if (!tiRoot)
	{
		  return false;
	}
	std::string sRootName = tiRoot->Value();
	if (sRootName != XMLLIST_ROOT )
	{
		  return false;
	}

	TiXmlNode * tiFirst = tiRoot->FirstChild(XMLLIST_XML);
	if(tiFirst == NULL)
	{
		  return false;
	}
	for (TiXmlElement* indexElement = tiFirst->ToElement();
		  indexElement != NULL;
		  indexElement = indexElement->NextSiblingElement())
	{
		  std::string strPath;
		  std::string strType;
		  strPath = indexElement->Attribute(XMLLIST_PATH);
		  strType = indexElement->Attribute(TYPE_OBJECT);
		  if (strPath.empty() == 0&& strType.empty() == 0)
		  {
				m_mapXMLList[strType] = strPath;
          }
	}	 
	return true;
}


const mapXMLList::const_iterator CXMLResource::Begin() const
{
	return m_mapXMLList.begin();
}

const mapXMLList::const_iterator CXMLResource::End() const
{
	return m_mapXMLList.end();
}

int CXMLResource::Size() const
{
	return m_mapXMLList.size();
}