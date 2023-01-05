#include <stdio.h>
struct lab {
    double experiment1;
    double experiment2;
    double experiment3;
};

struct theory {
    double test;
    double final;
};

struct ele709_record {
    long ID_number;
    struct lab lab_mark;
    struct theory theory_mark;
};

double total_mark(struct ele709_record *p)
{
    double mark=((p->lab_mark.experiment1+p->lab_mark.experiment2+p->lab_mark.experiment3)/3)*0.2+(p->theory_mark.test)*0.3+(p->theory_mark.final)*0.5;
}

int main()
{
	struct ele709_record john_doe;
    struct ele709_record *p;

    p=&john_doe;

        p->ID_number = 12345678;
        p->lab_mark.experiment1 = 90.2;
        p->lab_mark.experiment2 = 70.5;
        p->lab_mark.experiment3 = 80.4;
        p->theory_mark.test = 82.3;
        p->theory_mark.final = 79.2;
    double john_doe_mark = total_mark(&john_doe);
    printf("%lf\n",john_doe_mark);

}
