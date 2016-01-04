package com.b201.foosballstats;

import android.content.Context;
import android.net.DhcpInfo;
import android.net.wifi.WifiManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InterfaceAddress;
import java.net.MulticastSocket;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Enumeration;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        try {
            Log.d("B201", "broadcast = " + getBroadcast());
            Log.d("B201", "broadcast another = " + getBroadcastAddress());
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        Log.d("B201", "local ip = " + getLocalIpAddress());

        new Thread(listen).start();
        new Thread(sender).start();
    }

    public String getLocalIpAddress() {
        try {
            for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();) {
                NetworkInterface intf = en.nextElement();
                for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) {
                    InetAddress inetAddress= enumIpAddr.nextElement();
                    if (!inetAddress.isLoopbackAddress()) {
                        return inetAddress.getHostAddress().toString();
                    }
                }
            }
        } catch (SocketException ex) { }

        return null;
    }

    public static InetAddress getBroadcast() throws SocketException {
//        System.setProperty("java.net.preferIPv4Stack", "true");
//        for (Enumeration<NetworkInterface> niEnum = NetworkInterface.getNetworkInterfaces(); niEnum.hasMoreElements();) {
//            NetworkInterface ni = niEnum.nextElement();
//            if (!ni.isLoopback()) {
//                for (InterfaceAddress interfaceAddress : ni.getInterfaceAddresses()) {
//                    if (interfaceAddress.getBroadcast() != null)
//                        return interfaceAddress.getBroadcast();
//                }
//            }
//        }

        try {
            return InetAddress.getByName("192.168.1.0");
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }

        return null;
    }

    InetAddress getBroadcastAddress() throws IOException {
        WifiManager wifi = (WifiManager) this.getSystemService(Context.WIFI_SERVICE);
        DhcpInfo dhcp = wifi.getDhcpInfo();

        int broadcast = (dhcp.ipAddress & dhcp.netmask) | ~dhcp.netmask;
        byte[] quads = new byte[4];
        for (int k = 0; k < 4; k++)
            quads[k] = (byte) ((broadcast >> k * 8) & 0xFF);

        return InetAddress.getByAddress(quads);
    }

    Runnable listen = new Runnable() {
        @Override
        public void run() {
            MulticastSocket server = null;
            InetAddress addr = null;
            try {
                addr = getBroadcast();
                server = new MulticastSocket(3378);
                server.joinGroup(addr);

                byte[] buf = new byte[512];
                DatagramPacket packet = new DatagramPacket(buf, buf.length);
                while (!server.isClosed()) {
                    server.receive(packet);
                    byte[] incoming = packet.getData();
                    Log.d("B201", "Data = " + new String(incoming, 0, packet.getLength()));
                }
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                if (server != null && addr != null) {
                    try {
                        server.leaveGroup(addr);
                    } catch (IOException e) { }
                    server.close();
                }
            }
        }
    };

    Runnable sender = new Runnable() {
        @Override
        public void run() {
            DatagramSocket sock = null;
            try {
                Thread.sleep(1000);

                InetAddress addr = getBroadcast();
                sock = new DatagramSocket(3378);
                sock.setBroadcast(true);
                int curr = 0;
                while (true) {
                    byte[] bytes = ("Sending packet: " + curr++).getBytes();
                    Log.d("B201", "Sending packet.");
                    DatagramPacket data = new DatagramPacket(bytes, bytes.length, addr, 3378);
                    sock.send(data);

                    Thread.sleep(1000);
                }
            } catch (SocketException e) {
                e.printStackTrace();
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                if (sock != null)
                    sock.close();
            }
        }
    };

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
