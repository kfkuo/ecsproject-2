#include "XMLReader.h"
#include <expat.h>
#include <deque>


struct CXMLReader::SImplementation{
    std::shared_ptr< CDataSource > DSource; // pointer to data source
    XML_Parser DParser;
    std::deque<SXMLEntity> DDeque; //queue of XML entities

    // creates new start entity, sets its DType, name, and attributes, puts in queue
    static void StartElementHandler(void *userData, const XML_Char *name, const XML_Char **atts){
        SImplementation *This = (SImplementation *)userData;
        SXMLEntity NewEntity;
        
        NewEntity.DType = SXMLEntity::EType::StartElement;
        NewEntity.DNameData = name;
        for(int i = 0; atts[i]; i += 2){
            NewEntity.DAttributes.push_back({atts[i],atts[i+1]});
        }
        This->DDeque.push_back(NewEntity);
    }

    // creates new end entity, sets its dtype and attributes, puts in queue
    static void EndElementHandler(void *userData, const XML_Char *name){
        SImplementation *This = (SImplementation *)userData;
        SXMLEntity NewEntity;
        
        NewEntity.DType = SXMLEntity::EType::EndElement;
        NewEntity.DNameData = name;
        This->DDeque.push_back(NewEntity);
    }

    // creates new charactrer entity, sets its dtype and attributes, puts in queue
    static void CharacterDataHandler(void *userData, const XML_Char *s, int len){
        SImplementation *This = (SImplementation *)userData;
        SXMLEntity NewEntity;
        
        NewEntity.DType = SXMLEntity::EType::CharData;
        NewEntity.DNameData = std::string(s,len);
        This->DDeque.push_back(NewEntity);
    }

    // parses data source
    SImplementation(std::shared_ptr< CDataSource > src){
        DSource = src;
        DParser = XML_ParserCreate(nullptr);
        XML_SetUserData(DParser,(void *)this);
        XML_SetStartElementHandler(DParser,StartElementHandler);
        XML_SetEndElementHandler(DParser,EndElementHandler);
        XML_SetCharacterDataHandler(DParser,CharacterDataHandler);

    }

    // returns true if all entities have been read from xml
    bool End() const{
        return true;
    }

    
    bool ReadEntity(SXMLEntity &entity, bool skipcdata){
        // if queue is empty, read 512 characters of the source and feed it to the parser
        if(DDeque.empty()){
            std::vector<char> Buffer(512);
            DSource->Read(Buffer,Buffer.size());
            XML_Parse(DParser,Buffer.data(),Buffer.size(),DSource->End());

            // take entity out of queue if char data is read
            SXMLEntity Read = DDeque.back();
            if(skipcdata && !DDeque.empty() && (DDeque.back().DType == SXMLEntity::EType::CharData)){
                DDeque.pop_back();
            }
        }
        
        // if queue has entities in it, pop entity off and set entity to that item
        if(!DDeque.empty()){
            entity = DDeque.front();
            DDeque.pop_front();
            return true;
        }

        if(DDeque.empty()){
            
        }

        return false;
    }

};

        

CXMLReader::CXMLReader(std::shared_ptr< CDataSource > src){
    DImplementation = std::make_unique<SImplementation>(src);
}

CXMLReader::~CXMLReader(){

}

bool CXMLReader::End() const{
    return DImplementation->End();
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata){
    return DImplementation->ReadEntity(entity,skipcdata);
}
