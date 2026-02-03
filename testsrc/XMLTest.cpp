#include <gtest/gtest.h>
#include "XMLReader.h"
#include "XMLWriter.h"

TEST(XMLWriter, SimpleTest){
    std::shared_ptr<CStringDataSink> DataSink = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(DataSink);
    SXMLEntity TempEntity;
    TempEntity.DType = SXMLEntity::EType::StartElement;
    TempEntity.DNameData = "tag";
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::EndElement;
    Writer.WriteEntity(TempEntity);
    const std::string Output = DataSink->String();
    EXPECT_EQ(Output, "<tag></tag>");
}

TEST(XMLReader, SimpleTest){
    std::string XMLString = "<tag></tag>";
    std::shared_ptr<CStringDataSource> DataSource = std::make_shared<CStringDataSource>(XMLString);
    CXMLReader Reader(DataSource);
    SXMLEntity TempEntity;
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::StartElement);
    EXPECT_EQ(TempEntity.DNameData,"tag");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::EndElement);
    EXPECT_EQ(TempEntity.DNameData,"tag");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
}

TEST(XMLWriter, CharDataTest){
    std::shared_ptr<CStringDataSink> DataSink = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(DataSink);
    SXMLEntity TempEntity;
    TempEntity.DType = SXMLEntity::EType::StartElement;
    TempEntity.DNameData = "tag";
    TempEntity.SetAttribute("exp", "laugh");
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::CharData;
    TempEntity.DNameData = "hehe";
    TempEntity.DAttributes.clear();
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::EndElement;
    TempEntity.DNameData = "tag";
    Writer.WriteEntity(TempEntity);
    const std::string Output = DataSink->String();
    EXPECT_EQ(Output, "<tag exp=\"laugh\">hehe</tag>");
}

TEST(XMLReader, CharDataTest){
    std::string XMLString = "<tag exp=\"laugh\">hehe</tag>";
    std::shared_ptr<CStringDataSource> DataSource = std::make_shared<CStringDataSource>(XMLString);
    CXMLReader Reader(DataSource);
    SXMLEntity TempEntity;
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::StartElement);
    EXPECT_EQ(TempEntity.DNameData,"tag");
    ASSERT_EQ(TempEntity.DAttributes.size(),1);
    EXPECT_EQ(TempEntity.AttributeValue("exp"),"laugh");
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::CharData);
    EXPECT_EQ(TempEntity.DNameData,"hehe");
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::EndElement);
    EXPECT_EQ(TempEntity.DNameData,"tag");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
}

TEST(XMLWriter, NestedElementsTest){
    std::shared_ptr<CStringDataSink> DataSink = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(DataSink);
    SXMLEntity TempEntity;
    TempEntity.DType = SXMLEntity::EType::StartElement;
    TempEntity.DNameData = "student";
    TempEntity.SetAttribute("type", "undergrad");
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::StartElement;
    TempEntity.DNameData = "college";
    TempEntity.DAttributes.clear();
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::StartElement;
    TempEntity.DNameData = "major";
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::CharData;
    TempEntity.DNameData = "statistics";
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::EndElement;
    TempEntity.DNameData = "major";
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::EndElement;
    TempEntity.DNameData = "college";
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::StartElement;
    TempEntity.DNameData = "gpa";
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::EndElement;
    TempEntity.DNameData = "gpa";
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::EndElement;
    TempEntity.DNameData = "student";
    Writer.WriteEntity(TempEntity);
    const std::string Output = DataSink->String();
    EXPECT_EQ(Output, "<student type=\"undergrad\"><college><major>statistics</major></college><gpa></gpa></student>");
}

TEST(XMLReader, NestedElementsTest){
    std::string XMLString = "<student type=\"undergrad\"><college><major>statistics</major></college><gpa></gpa></student>";
    std::shared_ptr<CStringDataSource> DataSource = std::make_shared<CStringDataSource>(XMLString);
    CXMLReader Reader(DataSource);
    SXMLEntity TempEntity;
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::StartElement);
    EXPECT_EQ(TempEntity.DNameData,"student");
    ASSERT_EQ(TempEntity.DAttributes.size(),1);
    EXPECT_EQ(TempEntity.AttributeValue("type"),"undergrad");
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::StartElement);
    EXPECT_EQ(TempEntity.DNameData,"college");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::StartElement);
    EXPECT_EQ(TempEntity.DNameData,"major");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::CharData);
    EXPECT_EQ(TempEntity.DNameData,"statistics");
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::EndElement);
    EXPECT_EQ(TempEntity.DNameData,"major");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::EndElement);
    EXPECT_EQ(TempEntity.DNameData,"college");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::StartElement);
    EXPECT_EQ(TempEntity.DNameData,"gpa");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::EndElement);
    EXPECT_EQ(TempEntity.DNameData,"gpa");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::EndElement);
    EXPECT_EQ(TempEntity.DNameData,"student");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
}

TEST(XMLWriter, EscapeTest){
    std::shared_ptr<CStringDataSink> DataSink = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(DataSink);
    SXMLEntity TempEntity;
    TempEntity.DType = SXMLEntity::EType::StartElement;
    TempEntity.DNameData = "tag";
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::CharData;
    TempEntity.DNameData = "<>&\"'";
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::EndElement;
    TempEntity.DNameData = "tag";
    Writer.WriteEntity(TempEntity);
    const std::string Output = DataSink->String();
    EXPECT_EQ(Output, "<tag>&lt;&gt;&amp;&quot;&apos;</tag>");
}

TEST(XMLReader, EscapeTest){
    std::string XMLString = "<tag>&lt;&gt;&amp;&quot;&apos;</tag>";
    std::shared_ptr<CStringDataSource> DataSource = std::make_shared<CStringDataSource>(XMLString);
    CXMLReader Reader(DataSource);
    SXMLEntity TempEntity;
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::StartElement);
    EXPECT_EQ(TempEntity.DNameData,"tag");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::CharData);
    EXPECT_EQ(TempEntity.DNameData,"<>&\"'");
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::EndElement);
    EXPECT_EQ(TempEntity.DNameData,"tag");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
}

TEST(XMLWriter, MultipleAttrTest){
    std::shared_ptr<CStringDataSink> DataSink = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(DataSink);
    SXMLEntity TempEntity;
    TempEntity.DType = SXMLEntity::EType::StartElement;
    TempEntity.DNameData = "butterfly";
    TempEntity.SetAttribute("species", "monarch");
    TempEntity.SetAttribute("wingspan", "1.5");
    TempEntity.SetAttribute("color", "orange");
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::EndElement;
    TempEntity.DNameData = "butterfly";
    TempEntity.DAttributes.clear();
    Writer.WriteEntity(TempEntity);
    const std::string Output = DataSink->String();
    EXPECT_EQ(Output, "<butterfly species=\"monarch\" wingspan=\"1.5\" color=\"orange\"></butterfly>");
}

TEST(XMLReader, MultipleAttrTest){
    std::string XMLString = "<butterfly species=\"monarch\" wingspan=\"1.5\" color=\"orange\"></butterfly>";
    std::shared_ptr<CStringDataSource> DataSource = std::make_shared<CStringDataSource>(XMLString);
    CXMLReader Reader(DataSource);
    SXMLEntity TempEntity;
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::StartElement);
    EXPECT_EQ(TempEntity.DNameData,"butterfly");
    ASSERT_EQ(TempEntity.DAttributes.size(),3);
    EXPECT_EQ(TempEntity.AttributeValue("species"),"monarch");
    EXPECT_EQ(TempEntity.AttributeValue("wingspan"),"1.5");
    EXPECT_EQ(TempEntity.AttributeValue("color"),"orange");
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::EndElement);
    EXPECT_EQ(TempEntity.DNameData,"butterfly");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
}

TEST(XMLWriter, FlushTest){
    std::shared_ptr<CStringDataSink> DataSink = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(DataSink);
    SXMLEntity TempEntity;
    TempEntity.DType = SXMLEntity::EType::StartElement;
    TempEntity.DNameData = "tag";
    Writer.WriteEntity(TempEntity);
    TempEntity.DType = SXMLEntity::EType::EndElement;
    Writer.Flush();
    const std::string Output = DataSink->String();
    EXPECT_EQ(Output, "<tag></tag>");
}

TEST(XMLReader, SkipCDataTest){
    std::string XMLString = "<house>white house</house>";
    std::shared_ptr<CStringDataSource> DataSource = std::make_shared<CStringDataSource>(XMLString);
    CXMLReader Reader(DataSource);
    SXMLEntity TempEntity;
    EXPECT_TRUE(Reader.ReadEntity(TempEntity, true));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::StartElement);
    EXPECT_EQ(TempEntity.DNameData,"house");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
    EXPECT_TRUE(Reader.ReadEntity(TempEntity, true));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::EndElement);
    EXPECT_EQ(TempEntity.DNameData,"house");
    EXPECT_TRUE(TempEntity.DAttributes.empty());
    
}

TEST(XMLWriter, CompleteElementTest){
    std::shared_ptr<CStringDataSink> DataSink = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(DataSink);
    SXMLEntity TempEntity;
    TempEntity.DType = SXMLEntity::EType::CompleteElement;
    TempEntity.DNameData = "butterfly";
    TempEntity.SetAttribute("species", "monarch");
    Writer.WriteEntity(TempEntity);
    const std::string Output = DataSink->String();
    EXPECT_EQ(Output, "<butterfly species=\"monarch\"/>");
}

TEST(XMLReader, CompleteElementTest){
    std::string XMLString = "<butterfly species=\"monarch\"/>";
    std::shared_ptr<CStringDataSource> DataSource = std::make_shared<CStringDataSource>(XMLString);
    CXMLReader Reader(DataSource);
    SXMLEntity TempEntity;
    EXPECT_TRUE(Reader.ReadEntity(TempEntity));
    EXPECT_EQ(TempEntity.DType,SXMLEntity::EType::CompleteElement);
    EXPECT_EQ(TempEntity.DNameData,"butterfly");
    ASSERT_EQ(TempEntity.DAttributes.size(),1);
    EXPECT_EQ(TempEntity.AttributeValue("species"),"monarch");
}
