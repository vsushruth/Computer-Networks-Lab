#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/packet-sink.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{

  bool tracing = false;
  uint32_t maxBytes = 512;

  CommandLine cmd;
  cmd.AddValue ("tracing", "Flag to enable/disable tracing", tracing);
  cmd.AddValue ("maxBytes", "Total number of bytes for application to send", maxBytes);
  cmd.Parse (argc, argv);

  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer nodes;
  nodes.Create (3);
  NodeContainer link1 = NodeContainer(nodes.Get(0), nodes.Get(1));
  NodeContainer link2 = NodeContainer(nodes.Get(1), nodes.Get(2));

//----------------------------------------------------------------------------

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices1;
  devices1 = pointToPoint.Install (link1);

  NetDeviceContainer devices2;
  devices2 = pointToPoint.Install (link2);

//-----------------------------------------------------------------------------

  InternetStackHelper stack;
  stack.Install (nodes);

//-----------------------------------------------------------------------------

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces1 = address.Assign (devices1);

  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces2 = address.Assign (devices2);

//------------------------------------------------------------------------------

  UdpEchoServerHelper echoServer (9);
  ApplicationContainer serverApps = echoServer.Install (nodes.Get (0));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (5.0));

//-------------------

  uint16_t port = 9;   // Discard port (RFC 863)
  OnOffHelper onoff ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces1.GetAddress (0), port)));
  ApplicationContainer apps = onoff.Install (nodes.Get (1));
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (3.0));


  PacketSinkHelper sink ("ns3::UdpSocketFactory", Address (InetSocketAddress (Ipv4Address::GetAny (), port)));
  apps = sink.Install (nodes.Get (1));
  apps.Start (Seconds (0.0));
  apps.Stop (Seconds (10.0));


  BulkSendHelper source ("ns3::TcpSocketFactory", InetSocketAddress (interfaces2.GetAddress (0), port));
  source.SetAttribute ("MaxBytes", UintegerValue (maxBytes));
  ApplicationContainer sourceApps = source.Install (nodes.Get (1));
  sourceApps.Start (Seconds (5.0));
  sourceApps.Stop (Seconds (10.0));


//-------------------

  PacketSinkHelper sinkTCP ("ns3::TcpSocketFactory", Address (InetSocketAddress (Ipv4Address::GetAny (), port)));
  apps = sinkTCP.Install (nodes.Get (2));
  apps.Start (Seconds (0.0));
  apps.Stop (Seconds (10.0));

//--------------------------------------------------------------------------------


  if (tracing)
    {
      AsciiTraceHelper ascii;
      pointToPoint.EnableAsciiAll (ascii.CreateFileStream ("basic.tr"));
      pointToPoint.EnablePcapAll ("basic", false);
    }

  NS_LOG_INFO ("Run Simulation.");
  Simulator::Stop (Seconds (11.0));
  Simulator::Run ();
  Simulator::Destroy ();
  NS_LOG_INFO ("Done.");

  return 0;
}





