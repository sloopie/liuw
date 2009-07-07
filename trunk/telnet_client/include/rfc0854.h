/* Definitions from RFC0854
   by liuw
   liuw@liuw.name
*/

#ifndef _RFC0854_H

/* RFC0854 DEFINES */
#define TELNET_SE	240	/* End of subnegotiation parameters. */
#define TELNET_NOP	241	/* No operation. */
#define TELNET_DM	242	/* (Data Mark) The data stream portion of a
				 * Synch. This should always be accompanied
				 * by a TCP Urgent notification. */
#define TELNET_BRK	243	/* (Break) NVT character BRK. */
#define TELNET_IP	244	/* (Interrupt Process) The function IP. */
#define TELNET_AO	245	/* (Abort output) The function AO. */
#define TELNET_AYT	246	/* (Are You There) The function AYT. */
#define TELNET_EC	247	/* (Erase character) The function EC. */
#define TELNET_EL	248	/* (Erase Line) The function EL. */
#define TELNET_GA	249	/* (Go ahead) The GA signal. */
#define TELNET_SB	250	/* Indicates that what follows is
				 * subnegotiation of the indicated option. */
#define TELNET_WILL	251	/* Indicates the desire to begin performing,
				 * or confirmation that you are now performing,
				 * the indicated option. */
#define TELNET_WONT	252	/* Indicates the refusal to perform, or to
				 * continue performing, the indicated option. */
#define TELNET_DO	253	/* Indicates the request that the other party
				 * perform, or confirmation that you are
				 * expecting the other party to perform, the
				 * indicated option. */
#define TELNET_DONT	254	/* Indicates the demand that the other party
				 * stop performing, or confirmation that you
				 * are no longer expecting the other party
				 * to perform, the indicated option. */
#define TELNET_IAC	255	/* Data Byte 255. */


#endif
