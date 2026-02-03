# XMLWriter

## Overview
The CXMLWriter class writes XML entity class elements one at a time to an output data sink class. It can write all of the elements individually or there is the option to automatically close all elements with beginning elements using its Flush function. The class writes all XML escape characters in the correct formatting.

## Constructor
CXMLWriter(std::shared_ptr< CDataSink > sink);

Creates CXMLWriter object and initializes with pointer to its data output sink.

Usage:
```
std::shared_ptr<CStringDataSink> sink = std::make_shared<CStringDataSink>();
CXMLWriter Writer(sink);

```

## Deconstructor
~CXMLWriter();

Automatically deallocates the CXMLWriter class instance's memory when instance goes out of scope or is deleted through a pointer.

## Public Member Functions
bool Flush();

Automatically closes all beginning elements already written to data sink. ex: <tag> -> <tag></tag>

Usage:
```
bool success = Writer.Flush();

```


bool WriteEntity(const SXMLEntity &entity);

Writes passed entity to data sink.

Usage:
```
SXMLEntity input;
input.DType = SXMLEntity::EType::StartElement;
input.DNameData = "tag";
bool success = Writer.WriteEntity(input)

```



