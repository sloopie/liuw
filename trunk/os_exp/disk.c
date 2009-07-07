#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define UNALLOCATED 	0
#define EMPTY		1

//free zone node
struct fznode {
	int startblock;
	int unused;
	int state;
};

struct file {
	//starblock = (cylinder*20+track)*6+record
	int cylinder;
	int track;
	int record;

	int length;
};

#define TABLELEN	5
struct fznode t[TABLELEN] = {
	{5, 6, UNALLOCATED}, 
	{14, 3, UNALLOCATED},
	{21, 30, UNALLOCATED},
	{0, 0, EMPTY},
	{0, 0, EMPTY}
};

void print_file(struct file f)
{
	printf("Cylinder\tTrack\tRecord\tLength\n");
	printf("%d\t\t%d\t%d\t%d\n", f.cylinder, f.track, f.record, f.length);
}

void print_table()
{
	int i;
	printf("No.\tStart\tUnused\tState\n");
	for (i = 0; i < TABLELEN; ++i)
		printf("%d\t%d\t%d\t%s\n", i+1, t[i].startblock, t[i].unused, 
				(t[i].state==EMPTY)?"EMPTY":"UNALLOCATED");
}

void putfileto(struct fznode *t, struct file *f)
{
	if (!t)
		return;

	int cylinder, track, record;
	int M, m;
	M = (*t).startblock / 6;
	m = (*t).unused % 6;
	record = m;
	cylinder = M / 20;
	track = M % 20;

	(*f).cylinder = cylinder;
	(*f).track = track;
	(*f).record = record;

	(*t).startblock = (*t).startblock + (*f).length;
	(*t).unused = (*t).unused - (*f).length;
	if ((*t).unused == 0) {
		(*t).startblock = 0;
		(*t).state = EMPTY;
	}

}

void del(struct fznode *t, struct file f)
{
	(*t).startblock = (f.cylinder*20+f.track)*6+f.record;
	(*t).unused = f.length;
	(*t).state = UNALLOCATED;
}

struct fznode *findfit(struct file f)
{
	int i;
	for (i = 0; i < TABLELEN; ++i) {
		if (t[i].unused >= f.length)
			return &t[i];
	}
	return NULL;
}

struct fznode *findempty()
{
	int i;
	for (i = 0; i < TABLELEN; ++i) {
		if (t[i].state == EMPTY)
			return &t[i];
	}
	return NULL;
}

int main(int argc, char **argv)
{
	struct file f1 = {0, 0, 0, 10};
	struct file f2 = {1, 2, 0, 4};

	puts("Original table:");
	print_table();
	puts("");

	putfileto(findfit(f1), &f1);
	puts("Wrote file1 to disk:");
	print_table();
	puts("File state of file1:");
	print_file(f1);
	puts("");

	puts("File state of file2:");
	print_file(f2);
	del(findempty(), f2);
	puts("Removed file2 from disk:");
	print_table();

	return 0;
}
