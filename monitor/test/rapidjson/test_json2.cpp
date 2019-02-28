/**
 * @file        test_json2.cpp
 * @brief       测试rapidjson
 * @version     1.0
 * @date        01/19/2019 12:13:19 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */


#include <iostream>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>


int main()
{
    rapidjson::Document d;
    std::string b="b";

    d.SetObject();
    d.AddMember("a", rapidjson::Value(b.c_str(), b.length()), d.GetAllocator());
    d.AddMember("e", 1, d.GetAllocator());
    rapidjson::Value v;
    v.SetArray();
    v.PushBack(1, d.GetAllocator());
    v.PushBack(2, d.GetAllocator());
    d.AddMember("f", v, d.GetAllocator());

    rapidjson::StringBuffer buf;
    rapidjson::Writer<rapidjson::StringBuffer> w(buf);
    d.Accept(w);
    std::cout<<buf.GetString()<<std::endl;
    return 0;
}
