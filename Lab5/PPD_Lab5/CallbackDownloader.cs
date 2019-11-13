using System;
using System.Net;
using System.Net.Sockets;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading;

namespace PPD_Lab5
{
    public class CallbackDownloader
    {
        // mutex for "receive" operation
        public ManualResetEvent receiveDone = new ManualResetEvent(false);
        
        public CallbackDownloader(string url, int port = 80)
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
            var state = (StateObject) asyncResult.AsyncState;
            var socket = state.workSocket;
            socket.EndConnect(asyncResult);
            
            Console.WriteLine("Connected to: " + this.Domain);

            var request = Utils.GetRequest(this.Target, this.Domain);
            
            Console.WriteLine("The request is: " + request);
            
            socket.BeginSend(Encoding.UTF8.GetBytes(request), 0, request.Length, SocketFlags.None, SendCallback, state);
        }

        private void SendCallback(IAsyncResult asyncResult)
        {
            var state = (StateObject) asyncResult.AsyncState;
            var socket = state.workSocket;
            int sentBytes = socket.EndSend(asyncResult);

            Console.WriteLine("Sent " + sentBytes + " bytes to server: " + this.Domain);
            
            socket.BeginReceive(state.buffer, 0, state.buffer.Length, SocketFlags.None, ReceiveCallback, state);
        }

        private void ReceiveCallback(IAsyncResult asyncResult)
        {
            try {  
                StateObject state = (StateObject) asyncResult.AsyncState;  
                Socket client = state.workSocket;  
                
                int bytesRead = client.EndReceive(asyncResult);  
                if (bytesRead > 0) {  
                    state.sb.Append(Encoding.ASCII.GetString(state.buffer,0,bytesRead));  
                    client.BeginReceive(state.buffer,0,StateObject.BufferSize,0,ReceiveCallback, state);  
                } else {
                    // we have received all the data
                    var response = HttpResponseParser.parse(state.sb.ToString());
                    Console.WriteLine("Got response with status {0} and header length {1}", response.Status, response.Headers.Count);
                    receiveDone.Set();
                    client.Close();
                }  
            } catch (Exception e) {  
                Console.WriteLine(e.ToString());  
            }
        }

        public void DownloadPage()
        {
            var ipHostInfo = Dns.GetHostEntry(this.Domain);  
            var ipAddress = ipHostInfo.AddressList[0];  
            var remoteEp = new IPEndPoint(ipAddress, this.Port); 
            
            var socket = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            
            // create a wrapper for the connection information
            var state = new StateObject {
                workSocket = socket,
                hostname = Domain,
                endpoint = Target,
                remoteEndpoint = remoteEp,
            };
            
            // connect to the provided target
            socket.BeginConnect(remoteEp, ConnectCallback, state);
        }

        public void Wait()
        {
            receiveDone.WaitOne();
        }
    }
}