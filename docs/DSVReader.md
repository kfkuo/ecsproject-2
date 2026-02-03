# DSVReader

## Overview
DSV, also known as delimiter-separated-values is a class that is utilized through the exchanging of information. The most common forms of this class would be comma-sperated-values (CSV), and tab-separated values (TSV). The DSVReader is used to read data from the DataSource.h, and splitting each line into individual values. Data is separated through a delimiter, such as ",", "|", or "\t".

## Constructor
```cpp
CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter){

    DImplementation = std::make_unique<SImplementation>(src,delimiter);

}
```

PURPOSE: The constructor creates a DSVReader, and using a delimiter, reads from a data source


## Deconstructor
```cpp
CDSVReader::~CDSVReader(){

}
```

PURPOSE: The Deconstructor destroys the reader, and then it releases resources

## Public Member Functions
```cpp
bool CDSVReader::End() const{

    return DImplementation->End();

}
```

PURPOSE: The End is for when the data source has reached its end, it will return TRUE.

```cpp
bool CDSVReader::ReadRow(std::vector<std::string> &row){

    return DImplementation->ReadRow(row);

}
```

PURPOSE: The ReadRow reads one row from the data source, and then stores each column in row. return DImplementation->ReadRow(row); means that if a row was read, it will return TRUE, and if there are no more rows, it will return FALSE
