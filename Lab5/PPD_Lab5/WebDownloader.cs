using System;
using System.Net;
using System.Net.Sockets;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading;

namespace PPD_Lab5
{
    
    public class WebDownloader
    {
        private ManualResetEvent _connectDone = 
            new ManualResetEvent(false);
        
        private ManualResetEvent _sendDone = 
            new ManualResetEvent(false);

        private ManualResetEvent _receiveDone =
            new ManualResetEvent(false);
        
        public WebDownloader(string url, int port = 80)
        {
            this.Url = url;
            this.Port = port;
            this.Domain = GetDomain(url);
            this.Target = GetTarget(url);
        }

        public string Url { get; }
        public string Domain { get; }
        public string Target { get; }
        public int Port { get; }

        private string GetDomain(string address)
        {
            int domainEndIndex = address.IndexOf('/');

            return domainEndIndex < 0 ? address : address.Substring(0, domainEndIndex);
            
        }

        private string GetTarget(string address)
        {
            int domainEndIndex = address.IndexOf('/');

            return domainEndIndex < 0 ? "/" : address.Substring(domainEndIndex);
        }
        
        private void ConnectCallback(IAsyncResult asyncResult)
        {
            try
            {
                var socket = (Socket) asyncResult.AsyncState;
                socket.EndConnect(asyncResult);

                Console.WriteLine("Connected to: " + this.Domain);
                _connectDone.Set();
                
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }
        }

        private void SendCallback(IAsyncResult asyncResult)
        {
            try
            {
                var socket = (Socket) asyncResult.AsyncState;
                socket.EndSend(asyncResult);
                Console.WriteLine("Sent data to: " + this.Domain);
                _sendDone.Set();

            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }
        }

        private void ReceiveCallback(IAsyncResult asyncResult)
        {
            try
            {
                var socket = (Socket) asyncResult.AsyncState;
                int bytesRead = socket.EndReceive(asyncResult);
                Console.WriteLine("Received " + bytesRead + " bytes.");
                _receiveDone.Set();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }
        }

        public void DownloadPage()
        {
            var ipHostInfo = Dns.GetHostEntry(this.Domain);  
            var ipAddress = ipHostInfo.AddressList[0];  
            var remoteEp = new IPEndPoint(ipAddress, this.Port); 
            
            var socket = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            
            // connect to the provided target
            socket.BeginConnect(remoteEp, ConnectCallback, socket);
            _connectDone.WaitOne();
            
            // send the GET request
            var request = "GET " + this.Target + " HTTP/1.1\r\n" + 
                          "Host: " + ipAddress + "\r\n" +
                          "Content-Length: 0\r\n" +
                          "\r\n";
            
            Console.WriteLine("The request is: " + request);
            
            socket.BeginSend(Encoding.UTF8.GetBytes(request), 0, request.Length, SocketFlags.None, SendCallback, socket);
            _sendDone.WaitOne();
            
            // receive the data from the target
            var buffer = new byte[2048];
            socket.BeginReceive(buffer, 0, buffer.Length, SocketFlags.None, ReceiveCallback, socket);
            _receiveDone.WaitOne();
            
            string result = Encoding.UTF8.GetString(buffer, 0, buffer.Length);
            HttpResponseParser.parse(result);
            Console.WriteLine(result);
        }
    }
}