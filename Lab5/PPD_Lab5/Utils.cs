namespace PPD_Lab5
{
    public class Utils
    {
        public static string GetRequest(string target, string address)
        {
            // send the GET request
            var request = "GET " + target + " HTTP/1.1\r\n" +
                          "Host: " + address + "\r\n" +
                          "Content-Length: 0\r\n" +
                          "\r\n";

            return request;
        }
    }
}