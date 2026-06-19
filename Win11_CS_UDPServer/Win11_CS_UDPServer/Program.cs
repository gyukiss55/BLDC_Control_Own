using System;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Text;
using System.Diagnostics;

class Program
{
    static void Main()
    {
        const int port = 8888;
        Console.WriteLine("=== UDP SERVER ===");
        Console.WriteLine();
        Debug.WriteLine("=== UDP SERVER ===");

        // Helyi IP címek listázása
        Console.WriteLine("Local IPv4 addresses:");
        Debug.WriteLine("Local IPv4 addresses:");
        foreach (NetworkInterface ni in NetworkInterface.GetAllNetworkInterfaces())
        {
            if (ni.OperationalStatus != OperationalStatus.Up)
                continue;

            foreach (UnicastIPAddressInformation ip in ni.GetIPProperties().UnicastAddresses)
            {
                if (ip.Address.AddressFamily == AddressFamily.InterNetwork)
                {
                    Console.WriteLine($"  {ni.Name,-20} {ip.Address}");
                    Debug.WriteLine($"  {ni.Name,-20} {ip.Address}");
                }
            }
        }

        Console.WriteLine();
        Console.WriteLine($"[DEBUG] Opening UDP socket on port {port}");
        Debug.WriteLine($"[DEBUG] Opening UDP socket on port {port}");


        using (UdpClient udpServer = new UdpClient(port))
        {
            Console.WriteLine($"UDP Server listening on port {port}...");
            IPEndPoint remoteEP = new IPEndPoint(IPAddress.Any, 0);

            while (true)
            {
                try
                {
                    byte[] data = udpServer.Receive(ref remoteEP);

                    Console.WriteLine(
                        $"\n[{DateTime.Now:HH:mm:ss}] Packet from {remoteEP.Address}:{remoteEP.Port}");
                    Console.WriteLine($"Length: {data.Length} bytes");


                    // ASCII/UTF8 dump
                    string text = Encoding.UTF8.GetString(data);
                    Console.WriteLine($"TEXT: {text}");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error: {ex.Message}");
                }
            }
        }
    }
}
