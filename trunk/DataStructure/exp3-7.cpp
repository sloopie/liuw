#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int num;
	int time;
} car_t;

typedef struct linknode {
	car_t	car;
	struct 	linknode *next;
} LiStack;

void InitStack (LiStack *&s) {
	s = (LiStack *) malloc (sizeof (LiStack));
	s->next = NULL;
}

void Refresh (LiStack *s) {
	LiStack *p = s->next;
	while (p != NULL) {
		(p->car).time++;
		p = p->next;
	}
}

void ClearStack (LiStack *&s) {
	LiStack *p = s->next;
	while (p != NULL) {
		free (s);
		s = p;
		p = p->next;
	}
	free (s);
}

int StackLength (LiStack *s) {
	int i = 0;
	LiStack *p;
	p = s->next;
	while (p != NULL) {
		i++;
		p = p->next;
	}
	return i;
}

int StackEmpty (LiStack *s) {
	return s->next == NULL;
}

void Push (LiStack *&s, car_t e) {
	LiStack *p;
	p = (LiStack *) malloc (sizeof (LiStack));
	p->car = e;
	(p->car).time = 0;
	p->next = s->next;
	s->next = p;
	Refresh (s);
}

void DispStack (LiStack *s) {
	LiStack *p = s->next;
	while (p != NULL) {
		printf ("%d, %d\n", (p->car).num, (p->car).time);
		p = p->next;
	}
	puts ("");
}

void Delete (LiStack *s, car_t c) {
	LiStack *p = s, *t;
	while (p->next != NULL) {
		if ((p->next->car).num == c.num) {
			t = p->next;
			p->next = p->next->next;
			free (t);
			return;
		}
		p = p->next;
	}
	Refresh (s);
}


int main (int argc, char **argv) {
	LiStack *st;
	car_t c1, c2;
	c1.num = 1;
	c1.time = 3;
	c2.num = 2;
	c2.time = 4;
	InitStack (st);
	Push (st, c1);
	Push (st, c2);
	DispStack (st);
	Delete (st, c1);
	DispStack (st);
	c1.num = 4;
	c1.time = 1;
	Push (st, c1);
	DispStack (st);
	Delete (st, c2);
	DispStack (st);
	ClearStack (st);
	return 0;
}
