#include "DSVReader.h"

struct CDSVReader::SImplementation{
    std::shared_ptr<CDataSource> DSource;
    char DDelimiter;

    SImplementation(std::shared_ptr< CDataSource > src, char delimiter){
        DSource = src;
        DDelimiter = delimiter;
    }

    bool ParseValue(std::string &val){
        bool InQuotes = false;
        val.clear();

        while(!DSource->End()){
            char NextChar;
            DSource->Get(NextChar); // Get() consumes the character

            if(!InQuotes &&((NextChar == DDelimiter)||(NextChar == '\n'))){
                return true;
            }

            if(NextChar == '\"'){
                InQuotes = !InQuotes;
                continue;
            }

            else{
                val += std::string(1,NextChar);
            }
        }
    }

    bool End() const{
        return DSource->End();
    }

    bool ReadRow(std::vector<std::string> &row){
        row.clear();
    
        while(!DSource->End()){
            std::string NextValue;
    
            if(ParseValue(NextValue)){
                row.push_back(NextValue);
    
                if(!DSource->End()){
                    char NextChar;
                    DSource->Peek(NextChar);
    
                    if(NextChar == DDelimiter || NextChar == '\n'){
                        DSource->Get(NextChar); 
    
                        if(NextChar == '\n'){
                            return true;
                        }
                    }
                } else {
                    return true;
                }
            }
        }
    
        if (row.size() > 0) {
            return true;
        } else {
            return false;
        }
    }
    

};
        
CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter){
    DImplementation = std::make_unique<SImplementation>(src,delimiter);
}

CDSVReader::~CDSVReader(){

}

bool CDSVReader::End() const{
    return DImplementation->End();
}

bool CDSVReader::ReadRow(std::vector<std::string> &row){
    return DImplementation->ReadRow(row);
}
