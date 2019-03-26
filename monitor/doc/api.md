# mon_server api设计
## 协议 
采用http+json

## API接口

|功能|URL|方法|备注|
|-----|:----|----|----|
|属性上报|http://ip:port/v1/attrrecords|POST||
|属性申请|http://ip:port/v1/attrinfos|POST||

## 接口详解
### 属性上报
|字段|类型|说明|
|---|---|---|
|report|object|包含上报的所有信息|
|seq|int|序号，单机递增|
|hostname|string|主机名|
|hostip|string|主机ip|
|commattr|array[object]|通用属性|
|attrid|int|属性ID|
|value|int64|属性值|
|statattr|array[object]|统计属性|
|min|int|最小值|
|max|int|最大值|
|count|int64|数目|
|sum|int64|总和|

#### Request
example:

```json
    {
        "report":{
            "seq":1,
            "hostname":"gzm1",
            "hostip":"127.0.0.1",
            "time_min": 1234,
            "commattr":[
                {
                    "attrid":1,
                    "value":123
                },
                {
                    "attrid":2,
                    "value":234
                }
            ],
            "statattr":[
                {
                    "attrid":1,
                    "min":10,
                    "max":100,
                    "count": 40,
                    "sum": 2000
                },
                {
                    "attrid":1,
                    "min":10,
                    "max":100,
                    "count": 40,
                    "sum": 2000
                },
                {
                    "attrid":1,
                    "min":10,
                    "max":100,
                    "count": 40,
                    "sum": 2000
                }
            ]
    
        }
    }
```

#### Response
http code: 201 成功

http body:null

### 属性申请

|字段|类型|说明|
|---|---|---|
|data|object|申请的属性信息|
|commattr|array[object]|通用属性|
|name|string|名字[英文]|
|desc|string|描述|
|statattr|array[object]|统计属性|
|attrid|int|属性ID(由服务器返回，并用于函数调用中使用)|

#### request:
example:
```json
    {
        "data":{
            "commattr":[
                {
                    "name":"ATTR_REQ",
                    "desc":"请求量"
                },
                {
                    "name":"ATTR_RSP",
                    "desc":"响应量"
                }
            ],
            "statattr":[
                {
                    "name":"ATTR_DELAY",
                    "desc":"处理时延"
                }
            ]
        }
    }
```

#### response
example:
```json
    {
        "result":
        {
            "commattr":[
                {
                    "name":"ATTR_REQ",
                    "desc":"请求量",
                    "attrid":1
                },
                {
                    "name":"ATTR_RSP",
                    "desc":"响应量"
                    "attrid":2
                }
            ],
            "statattr":[
                {
                    "name":"ATTR_DELAY",
                    "desc":"处理时延",
                    "attrid":1
                }
            ]
        }
    }
```

