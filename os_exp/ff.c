#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MEMSIZE 32

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
	printf("not enough memory\n");
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
	int i, j, k, proc_nr;
	for (i = 0; i < MEMSIZE; ++i)
		m[i] = 0;
	
	struct proc p_a[5];
	printf("How many processes(less than 5)?\n");
	scanf("%d", &proc_nr);
	
	for (j = 1; j <= proc_nr; ++j) {
		printf("input demand memory of process %d: ", j);
		scanf("%d", &k);
		p_a[j-1].mem = k;
		p_a[j-1].pid = j;
	}

	printf("There are %d processes in total.\n", proc_nr);

	int op;
	while (1) {
		printf("Select your option: \n"
				"1. Allocate memory for process i\n"
				"2. Free memory of process i\n"
				"3. Memory info\n"
				"4. Quit\n");
		scanf("%d", &op);
		switch (op) {
			case 1:
				printf("process id: ");
				scanf("%d", &i);
				alloc(&p_a[i-1]);
				break;
			case 2:
				printf("process id: ");
				scanf("%d", &i);
				myfree(p_a[i-1]);
				break;
			case 3:
				puts("\nMemory info:");
				meminfo();
				break;
			case 4:
				exit(0);
		}
	}

	return 0;
}
