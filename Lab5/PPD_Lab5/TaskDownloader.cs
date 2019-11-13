using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace PPD_Lab5
{
    public class TaskDownloader
    {   
        public TaskDownloader(string url, int port = 80)
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
            state.connectDone.Set();
            
            Console.WriteLine("Connected to: " + this.Domain);
        }

        private void SendCallback(IAsyncResult asyncResult)
        {
            var state = (StateObject) asyncResult.AsyncState;
            var socket = state.workSocket;
            int sentBytes = socket.EndSend(asyncResult);

            Console.WriteLine("Sent " + sentBytes + " bytes to server: " + this.Domain);

            state.sendDone.Set();
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
                    state.receiveDone.Set();
                }  
            } catch (Exception e) {  
                Console.WriteLine(e.ToString());  
            }
        }
        
        private Task ConnectWrapper(StateObject state) {
            state.workSocket.BeginConnect(state.remoteEndpoint, ConnectCallback, state);

            return Task.FromResult(state.connectDone.WaitOne());
        }
        
        private Task SendWrapper(StateObject state, string data) {
            var byteData = Encoding.ASCII.GetBytes(data);
            state.workSocket.BeginSend(byteData, 0, byteData.Length, 0, SendCallback, state);
            return Task.FromResult(state.sendDone.WaitOne());
        }
        
        private Task ReceiveWrapper(StateObject state) {
            state.workSocket.BeginReceive(state.buffer, 0, state.buffer.Length, 0, ReceiveCallback, state);
            return Task.FromResult(state.receiveDone.WaitOne());
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

            // wait for the connection to succeed
            ConnectWrapper(state).Wait();
            
            // send the GET request
            var request = Utils.GetRequest(Target, Domain);
            Console.WriteLine("The request is: " + request);
            SendWrapper(state, request).Wait();
            
            // receive the data
            ReceiveWrapper(state).Wait();
            var response = HttpResponseParser.parse(state.sb.ToString());
            
            Console.WriteLine("Got response with status {0} and header length {1}", response.Status, response.Headers.Count);
            
            socket.Close();
        }
    }
}