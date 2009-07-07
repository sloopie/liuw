#include <stdlib.h>
#include <stdio.h>


struct PCB {
	char name[3];
	struct PCB* p;
	int runtime;
	int demandtime;
	int state;
};

#define R 1
#define E 0

struct PCB* current;
struct PCB* head;

void resched()
{
	struct PCB* t, *prev, *next;
	t = head;
	while (t) {
		if (t->state == E) {
			printf("%s finished\n", t->name);
			if (t == head)
				head = head->p;
			else {
				prev = head;
				
				while (prev) {
					if (prev->p == t) {
						prev->p = t->p;
						break;
					}
					prev = prev->p;
				}
				
			}
		}
		t = t->p;
	}
	return;
}

void run()
{
	int i = 1;
	while (head) {
		current = head;
		printf("Round %d: ", i);
		while (current) {
			current->runtime += 1;
			current->demandtime -= 1;
			printf("%s\t", current->name);
			if (current->demandtime == 0) {
				current->state = E;
			}

			current = current->p;
		}
		puts("");
		i++;
		resched();
		puts("");
	}
	puts("");
}

int main(int argc, char **argv)
{
	struct PCB Q1 = {
		.name = "Q1",
		.p = NULL,
		.runtime = 0,
		.demandtime = 1,
		.state = R
	};
	struct PCB Q2 = {
		.name = "Q2",
		.p = NULL,
		.runtime = 0,
		.demandtime = 5,
		.state = R
	};
	struct PCB Q3 = {
		.name = "Q3",
		.p = NULL,
		.runtime = 0,
		.demandtime = 2,
		.state = R
	};
	struct PCB Q4 = {
		.name = "Q4",
		.p = NULL,
		.runtime = 0,
		.demandtime = 9,
		.state = R
	};
	struct PCB Q5 = {
		.name = "Q5",
		.p = NULL,
		.runtime = 0,
		.demandtime = 7,
		.state = R
	};

	head = &Q1;
	Q1.p = &Q2;
	Q2.p = &Q3;
	Q3.p = &Q4;
	Q4.p = &Q5;

	run();

	return 0;
}

