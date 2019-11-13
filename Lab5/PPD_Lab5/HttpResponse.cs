using System;
using System.Collections.Generic;

namespace PPD_Lab5
{
    public class HttpResponse
    {        
        public HttpResponse(int status, Dictionary<string, string> headers)
        {
            Headers = headers;
            Status = status;
        }

        public int Status { get; }

        public Dictionary<string, string> Headers { get; }

        public string header(string name)
        {
            return Headers[name];
        }
    }
}