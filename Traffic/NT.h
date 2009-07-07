#ifndef NT_H_
#define NT_H_

#include "pcap.h"

extern pcap_if_t *alldevs;
extern pcap_if_t *d;
extern pcap_t *adhandle;
extern char errbuf[PCAP_ERRBUF_SIZE];

extern HANDLE hThread;

extern DWORD MyThreadId;
extern struct timeval st_ts;
extern unsigned int netmask;
extern struct bpf_program fcode;

extern char filter[];

DWORD WINAPI MyThread(LPVOID lpParam);

extern DWORD g_totaltraffic;


void GetAllDevices(void);


#endif