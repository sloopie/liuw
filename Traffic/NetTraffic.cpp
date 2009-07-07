#include "StdAfx.h"
#include "Traffic.h"
#include "TrafficDlg.h"



#include "pcap.h"

#pragma comment(lib,"packet.lib")
#pragma comment(lib,"wpcap.lib")

#include "NT.h"

pcap_if_t *alldevs;
pcap_if_t *d;
pcap_t *adhandle;
char errbuf[PCAP_ERRBUF_SIZE];
struct timeval st_ts;
HANDLE hThread;

DWORD MyThreadId;

unsigned int netmask;
struct bpf_program fcode;

char filter[100];

DWORD g_totaltraffic;




void packet_handler(u_char* state, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	CTrafficDlg *p = (CTrafficDlg *)::AfxGetApp()->GetMainWnd();	
	
	struct timeval *old_ts = (struct timeval *)state;
	unsigned int delay;
	LARGE_INTEGER Bps, Pps;
	struct tm *ltime;
	char timestr[16];
	time_t local_tv_sec;
	CString l;


	delay = (header->ts.tv_sec - old_ts->tv_sec) * 1000000 
		- old_ts->tv_usec + header->ts.tv_usec;


	Bps.QuadPart = (((*(LONGLONG*)(pkt_data+8)) * 8 * 1000000) / (delay));

	Pps.QuadPart = (((*(LONGLONG*)(pkt_data)) * 1000000) / (delay));

	local_tv_sec = header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);
	strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);


	g_totaltraffic = Bps.QuadPart;

	old_ts->tv_sec = header->ts.tv_sec;
	old_ts->tv_usec = header->ts.tv_usec;

	return;
}


DWORD WINAPI MyThread(LPVOID lpParam)
{
	pcap_loop(adhandle, 0, packet_handler, (PUCHAR)&st_ts);	
	return 0;
}


void GetAllDevices(void)
{
	CTrafficDlg *p = (CTrafficDlg *)::AfxGetApp()->GetMainWnd();
	if (pcap_findalldevs(&alldevs, errbuf) == -1) {
		p->m_list_devices.AddString("Error");
		return;
	}

	for (d = alldevs; d; d = d->next)
		if (d->description)
			p->m_list_devices.AddString(d->description);
		else
			p->m_list_devices.AddString(d->name);

	return;
}
