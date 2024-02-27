#include <iostream>
using namespace std;
// A node for storing the non-zero element in the sparse vector
struct Student
{
	int id;
	char name[20];
	float gpa;
};

Student* find(Student** studs, int id){
	if(studs){
		cout << studs[(sizeof(studs)/sizeof(Student))/2]->id << endl;
		if(studs[(sizeof(studs)/sizeof(Student))/2]->id < id){
			return find(studs+((sizeof(studs)/sizeof(Student))/2), id);
		}
		else{
			return find(studs-((sizeof(studs)/sizeof(Student))/2), id);
		}
	}else {
		return nullptr;
	}
}
// Sparse vector with a linked list of non-zero element
int main(){
	Student* studs[5];
	Student s1 = {1, "A", 3.5};
	Student s2 = {2, "B", 3.6};
	Student s3 = {3, "C", 3.7};
	Student s4 = {4, "D", 3.8};
	Student s5 = {5, "E", 3.9};
	studs[0] = &s1;
	studs[1] = &s2;
	studs[2] = &s3;
	studs[3] = &s4;
	studs[4] = &s5;
	Student* s = find(studs, 3);
	cout << s->name << endl;
	return 0;
}
