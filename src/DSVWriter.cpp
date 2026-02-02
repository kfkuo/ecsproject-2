#include "DSVWriter.h"

struct CDSVWriter::SImplementation{
    std::shared_ptr< CDataSink > DSink;
    char DDelimiter;
    bool DQuoteAll;

    SImplementation(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall){
        DSink = sink;
        DDelimiter = delimiter;
        DQuoteAll = quoteall;
    }

    ~SImplementation(){

    }

    bool WriteRow(const std::vector<std::string> &row){
        bool First = true;

        for(auto &Column : row){

            if(!First){
                DSink->Put(DDelimiter);
            }
            First = false;

            bool NeedsQuotes = DQuoteAll;

            if(!NeedsQuotes){
                for(int i = 0; i < Column.size(); i++){
                    char c = Column[i];
                    if(c == DDelimiter || c == '"' || c == '\n'){
                        NeedsQuotes = true;
                        break;
                    }
                }
            }

            if(NeedsQuotes){
                DSink->Put('"');

                for(int i = 0; i < Column.size(); i++){
                    char c = Column[i];
                    if (c == '"'){
                        DSink->Put('"');
                    }
                    DSink->Put(c);
                }
                DSink->Put('"');
            }
            
            else{
                std::vector<char> Buffer(Column.begin(),Column.end());
                DSink->Write(Buffer);
            }
        }
        DSink->Put('\n');
        return true;
    }

};

CDSVWriter::CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall){
    DImplementation = std::make_unique<SImplementation>(sink,delimiter,quoteall);
}

CDSVWriter::~CDSVWriter(){

}

bool CDSVWriter::WriteRow(const std::vector<std::string> &row){
    return DImplementation->WriteRow(row);
}
