using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace PPD_Lab5
{
    public class StateObject {  
        // Client socket.  
        public Socket workSocket = null;
        
        // Size of receive buffer.  
        public const int BufferSize = 512;
        
        // Receive buffer.  
        public byte[] buffer = new byte[BufferSize];  
        
        // Received data string.  
        public StringBuilder sb = new StringBuilder();
        
        // server's hostname
        public string hostname;

        // request path
        public string endpoint;
        
        // server's ip address and port
        public IPEndPoint remoteEndpoint;

        // mutex for "connect" operation
        public ManualResetEvent connectDone = new ManualResetEvent(false);

        // mutex for "send" operation
        public ManualResetEvent sendDone = new ManualResetEvent(false);

        // mutex for "receive" operation
        public ManualResetEvent receiveDone = new ManualResetEvent(false);
    }  
}