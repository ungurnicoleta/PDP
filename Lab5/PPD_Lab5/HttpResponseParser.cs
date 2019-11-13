using System;
using System.Collections.Generic;
using System.Net.NetworkInformation;

namespace PPD_Lab5
{
    public static class HttpResponseParser
    {
        private static int GetStatus(string statusLine)
        {
            var tokens = statusLine.Split(" ");

            return int.Parse(tokens[1]);
        }

        private static Dictionary<string, string> GetHeaders(string[] lines)
        {
            var headers = new Dictionary<string, string>( StringComparer.OrdinalIgnoreCase);
            
            for(int i = 1; i < lines.Length; i++)
            {
                var line = lines[i];
                
                if (string.IsNullOrEmpty(line)) break;
                
                var tokens = line.Split(":");

                if (tokens.Length != 2) continue;
                
                headers.Add(tokens[0], tokens[1]);
            }

            return headers;
        }
        
        public static HttpResponse parse(string response)
        {
            var lines = response.Split("\r\n");
            
            var status = GetStatus(lines[0]);
            var headers = GetHeaders(lines);
            
            return new HttpResponse(status, headers);
        }
    }
}