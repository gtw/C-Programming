#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{

	char *last;
	char *first;
	float gpa;

} Student;

void print_students(Student * students, int n);
void sort_students_by_name(Student * students, int n);
void sort_students_by_gpa(Student * students, int n);
int stdnt_gpa_comp(const void *a, const void *b);
int stdnt_name_comp(const void *a, const void *b);

int main(void)
{
	Student students[4];

	students[0].last = "Tramm";
	students[0].first= "John";
	students[0].gpa = 1.9;
	
	students[1].last = "Siegel";
	students[1].first= "Andrew";
	students[1].gpa = 1.8;
	
	students[2].last = "Tchoua";
	students[2].first= "Roselyne";
	students[2].gpa = 3.9;
	
	students[3].last = "Siegel";
	students[3].first= "Robert";
	students[3].gpa = 3.95;

	printf("Unsorted Students:\n");
	print_students(students, 4);

	printf("Students sorted by name:\n");
	sort_students_by_name(students, 4);
	print_students(students, 4);

	printf("Students sorted by gpa:\n");
	sort_students_by_gpa(students, 4);
	print_students(students, 4);

	return 0;
}

void print_students(Student * students, int n)
{
	int i;
	for( i = 0; i < n; i++ )
	{
		char * full = (char *) malloc( 50 * sizeof(char ) );
		sprintf(full, "%s, %s", students[i].last, students[i].first);
		printf("Name: %-20s GPA: %.2f\n", full, students[i].gpa);
	}
}

void sort_students_by_name(Student * students, int n)
{
	qsort(students,n,sizeof(Student),stdnt_name_comp);
}

void sort_students_by_gpa(Student * students, int n)
{
	qsort(students,n,sizeof(Student),stdnt_gpa_comp);
}
/* Basically just a wrapper function for strcmp.
If last names are equal, it returns strcmp of first names */
int stdnt_name_comp(const void *a, const void *b){
	
	Student *ai = (Student*)a;
	Student *bi = (Student*)b;
	
	if(strcmp(ai->last,bi->last)!=0)
		return strcmp(ai->last,bi->last);
	else
		return strcmp(ai->first,bi->first);
}
/* Simple Comparator of Student's GPAs */
int stdnt_gpa_comp(const void *a, const void *b){

	Student *ai = (Student*)a;
	Student *bi = (Student*)b;
	float a_gpa = ai->gpa;
	float b_gpa = bi->gpa;

	return ( (a_gpa > b_gpa) - (a_gpa < b_gpa) );
	
}
