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


    void EscapeHelper(std::string &charString){
        std::string temp = charString;
        temp = StringUtils::Replace(temp, "&", "&amp;");
        temp = StringUtils::Replace(temp, "<", "&lt;");
        temp = StringUtils::Replace(temp, ">", "&gt;");
        temp = StringUtils::Replace(temp, "\"", "&quot;");
        temp = StringUtils::Replace(temp, "'", "&apos;");
        charString = temp;

    };

    void AttributesHelper(const SXMLEntity &entity, std::string &sentity){

        std::string data = entity.DNameData;
        EscapeHelper(data);
        sentity += data;

        if (!entity.DAttributes.empty()){
            for(auto &Attribute : entity.DAttributes){
                std::string name = std::get<0>(Attribute);
                std::string val = std::get<1>(Attribute);
                EscapeHelper(val);
                sentity += " ";
                sentity += name;
                sentity += "=\"";
                sentity += val;
                sentity += "\"";
            }
        }
    }

    void BracketHelper(std::string &sentity){
        std::string temp = "<";
        temp += sentity;
        temp += ">";
        sentity = temp;
    }

    bool Write(const SXMLEntity &entity){
        std::string sentity = "";
        std::vector <std::string> tempVector;
        std::string temp = "";
        
        if (entity.DType == SXMLEntity::EType::StartElement){
            AttributesHelper(entity, sentity);
            BracketHelper(sentity);
        }

        else if (entity.DType == SXMLEntity::EType::EndElement){
            sentity += "/";
            sentity += entity.DNameData;
            EscapeHelper(sentity);
            BracketHelper(sentity);
        }

        else if (entity.DType == SXMLEntity::EType::CharData){
            sentity += entity.DNameData;
            EscapeHelper(sentity);
        }

        else if (entity.DType == SXMLEntity::EType::CompleteElement){
            AttributesHelper(entity, sentity);
            sentity += "/";
            BracketHelper(sentity);
        }

        // write entity to sink 
        for(char c : sentity){
            if(!DSink->Put(c)){
                return false;
            };
        }
        return true;
    }

    bool Flush(){
        // write all entities on stack to data sink
        if(!DStack.empty()){
            while (!DStack.empty()){
                Write(DStack.top());
                DStack.pop();
            }
        }  

        return false;
    };

    bool WriteEntity(const SXMLEntity &entity){
        SXMLEntity tempEntity;
        //write entity to sink
        if(!Write(entity)){
            return false;
        }

        // if start element, put end element entity on stack
        if (entity.DType == SXMLEntity::EType::StartElement){
            tempEntity.DNameData = entity.DNameData;
            tempEntity.DType = SXMLEntity::EType::EndElement;
            DStack.push(tempEntity);
        }
        
        return true;
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
