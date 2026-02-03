# XMLReader

## Overview
The CXMLReader class reads elements one at a time from XML source data of the StringDataSink class. Each element's attributes and data are then outputted into an XMLEntity class. It has the option to exclude character data elements from the output.

## Constructor
CXMLReader(std::shared_ptr< CDataSource > src)

Creates CXMLReader object and initializes with pointer to its data source.

Usage:
```
std::string xmlString = "<tag></tag>";
std::shared_ptr<CStringDataSource> src = std::make_shared<CStringDataSource>(xmlString);
CXMLReader Reader(src);

```
## Deconstructor
~CXMLReader()

Automatically deallocates the CXMLReader class instance's memory when instance goes out of scope or is deleted through a pointer.

## Public Member Functions
bool End()

Returns true if the CXMLReader has read all of its source data, false otherwise.

Usage:
```
bool finished = Reader.End();

```

bool ReadEntity(SXMLEntity &entity, bool skipcdata = false)

Reads elements one at a time from XML source data of the StringDataSink class. Each element's attributes and data are outputted into SXMLEntity class. Optional skipcdata parameter exclude character data elements from the output

Usage:
```
SXMLEntity tempEntity;
bool success = Reader.ReadEntity(TempEntity, true);

//

```
