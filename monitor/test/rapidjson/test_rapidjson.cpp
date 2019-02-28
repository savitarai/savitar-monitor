/**
 * @file        test_rapidjson.cpp
 * @brief       
 * @version     1.0
 * @date        01/17/2019 04:58:26 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>


int main()
{
    std::string x="{\"x\":1, \"y\":\"xx\"}";
    rapidjson::Document d;
    d.Parse(x.c_str());
    rapidjson::Value & value=d["x"];
    std::cout<<value.GetInt()<<std::endl;
    value.SetInt(value.GetInt()+1);
    rapidjson::Value & val2=d["y"];
    std::cout<<val2.GetString()<<std::endl;


    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    std::cout<<buffer.GetString()<<std::endl;
    return 0;
}
