# DSVWriter

## Overview
DSV, also known as delimiter-separated-values is a class that is utilized through the exchanging of information. The most common forms of this class would be comma-sperated-values (CSV), and tab-separated values (TSV). The DSVWriter is used to write this DSV data, writing rows of data into DataSink.h. The writer automatically places values in double quotes if necessary, and is able to be configured to quote all values. The DSVWriter writes one row at a time, appends a newline character after. This is utilized when data should be written row-by-row.

## Constructor
```cpp
CDSVWriter::CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall){

    DImplementation = std::make_unique<SImplementation>(sink,delimiter,quoteall);

}
```

PURPOSE: The purpose of the constructor is to write DSV data into a specific data sink. In this case, CDataSink is the sink that has been specified where the output is written. The constructor initializes the writer's implementation, these settings being stored for use when rows are written.

## Deconstructor
```cpp
CDSVWriter::~CDSVWriter(){

}
```

PURPOSE: The purpose of the deconstructor is to destroy the DSVWriter object, releasing any resources it owns. This further ensures that the implementation obejct is cleaned up well when the writer goes out of scope.

## Public Member Functions
```cpp
bool CDSVWriter::WriteRow(const std::vector<std::string> &row){

    return DImplementation->WriteRow(row);

}
```

PURPOSE: The purpose of the WriteRow is to write a single row of DSV into the data sink. Each string in "row" is representative of one column, and a new line is written after each row. If the row has been written successfully, it will return TRUE.
