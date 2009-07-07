#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MEMSIZE 128

struct proc {
	int pid;
	int mem;
	int memstart;
	int memend;
};

static unsigned char m[MEMSIZE];


void myfree(struct proc p)
{
	int i;
	for (i = p.memstart; i <= p.memend; ++i)
		m[i] = 0;
}

void alloc(struct proc *p)
{
	int s, e, found;
	for (s = 0; s < MEMSIZE; ) {
		found = 0;
		if (m[s] == 0) {
			e = s;
			while (m[e] == 0 && e < MEMSIZE)
				e++;
			e--;
			if (e-s+1 >= (*p).mem) {
				(*p).memstart = s;
				(*p).memend = s + (*p).mem - 1;
				int i;
				for (i = s; i <= (*p).memend; ++i)
					m[i] = (*p).pid;
				found = 1;
			}
			if (found) return;
			s += e;
		}else
			++s;
	}
	printf("not enought memory\n");
}

void meminfo()
{
	int i;
	for (i = 1; i <= MEMSIZE; ++i) {
		printf("%d ", m[i-1]);
		if (i % 16 == 0 && i != 0)
			puts("");
	}
	puts("");
}

void procinfo(struct proc p)
{
	printf("PID: %d, mem: %d, memstart: %d, memend: %d\n",
			p.pid, p.mem, p.memstart, p.memend);
	return;
}

int main(int argc, char **argv)
{
	int i;
	for (i = 0; i < MEMSIZE; ++i)
		m[i] = 0;
	struct proc p1 = {
		.pid = 1,
		.mem = 11,
		.memstart = 0,
		.memend = 0
	};
	struct proc p2 = {
		.pid = 2,
		.mem = 5,
		.memstart = 0,
		.memend = 0
	};
	struct proc p3 = {
		.pid = 3,
		.mem = 1,
		.memstart = 0,
		.memend = 0
	};
	struct proc p4 = {
		.pid = 4,
		.mem = 2,
		.memstart = 0,
		.memend = 0
	};
	alloc(&p1);
	meminfo();
	procinfo(p1);	
	myfree(p1);
	alloc(&p2);
	meminfo();
	procinfo(p2);
	alloc(&p3);
	meminfo();
	myfree(p2);
	meminfo();
	alloc(&p4);
	meminfo();
	meminfo();

	return 0;
}
