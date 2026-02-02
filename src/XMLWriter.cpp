#include "XMLWriter.h"
#include <expat.h>
#include <stack>
#include "StringUtils.h"

struct CXMLWriter::SImplementation{
    std::shared_ptr< CDataSink > DSink;
    std::stack<SXMLEntity> DStack;

    SImplementation(std::shared_ptr< CDataSink > sink){
        DSink = sink;
    };

    ~SImplementation(){

    };

    

    bool Flush(){
        // if(!DStack.empty()){
        //     while (!DStack.empty()){
        //         WriteEntity(DStack.top());
        //         DStack.pop();
        //     }
        // }  

        return false;
    };

    void EscapeHelper(std::string &charString){
        //REPLACE RETURNS THE STRING
        std::string temp = charString.substr(1,charString.size() - 1);
        StringUtils::Replace(temp, "<", "&lt");
        StringUtils::Replace(temp, ">", "&gt");
        StringUtils::Replace(temp, "&", "&amp");
        StringUtils::Replace(temp, "\"", "&quot");
        StringUtils::Replace(temp, "'", "&apos");
        StringUtils::Replace(charString, charString.substr(1,charString.size() + 1), temp);
    };

    void AttributesHelper(){
        
    }

    bool WriteEntity(const SXMLEntity &entity){
        std::string sentity = "<";
        std::vector <std::string> tempVector;
        sentity += entity.DNameData;
        if (entity.DType == SXMLEntity::EType::StartElement){
            if (!entity.DAttributes.empty()){
                for(auto &Attribute : entity.DAttributes){
                    sentity += " ";
                    sentity += std::get<0>(Attribute);
                    sentity += "=";
                    sentity += std::get<1>(Attribute); 
                }
                sentity += ">";
            }
            
        }
        else if (entity.DType == SXMLEntity::EType::CharData){
            
        }
        else if (entity.DType == SXMLEntity::EType::EndElement){
            
        }
        else if (entity.DType == SXMLEntity::EType::CompleteElement){
            
        }

        //EscapeHelper(sentity);

        // write entity to sink
        for(int i = 0; sentity[i]; i++){
            DSink->Put(sentity[i]);
        }

        DStack.push(entity);
        

        
        return false;
    };
};

CXMLWriter::CXMLWriter(std::shared_ptr< CDataSink > sink){
    DImplementation = std::make_unique<SImplementation>(sink);
}


CXMLWriter::~CXMLWriter(){
    
}

bool CXMLWriter::Flush(){
    return DImplementation -> Flush();
}

bool CXMLWriter::WriteEntity(const SXMLEntity &entity){
    return DImplementation -> WriteEntity(entity);
}