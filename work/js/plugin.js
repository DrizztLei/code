#!/usr/bin/node
{
    function createXMLHttpRequest()
    {
        var xmHttp;
        if(window.XMLHttpRequest)
        {
            xmlHttp = new XMLHttpRequest();
            if(xmlHttp.overrideMimeType)
                xmlHttp.overrideMimeType('text/xml');
        }
        else if(window.ActiveXObject)
        {
            try
            {
                xmlHttp = new ActiveXObject("Msxml2.XMLHTTP");
            }
            catch (e)
            {
                try
                {
                    xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
                }
                catch (e)
                {
                    console.log("unknow error");
                }
                return xmlHttp;
            }
        }
    }
    console.log("Run ");
    xmlHttp = createXMLHttpRequest();  
    var url = "getfiledetail.jsp?fileid="+id;  
    xmlHttp.open("GET", url, true);// 异步处理返回   
    xmlHttp.onreadystatechange = callback;   
    xmlHttp.setRequestHeader("Content-Type" , "application/x-www-form-urlencoded;");  
    xmlHttp.send();  
}
