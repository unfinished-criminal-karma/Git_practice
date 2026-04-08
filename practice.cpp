//
// Created by HP on 2026/3/31.
//
#include<bits/stdc++.h>
using namespace std;
class Student {
public:
    Student(int nu = 0,string nam = "zhangsan",char se = 'm');
    void display() {
        cout<<"num:"<<num<<endl;
        cout<<"name:"<<name<<endl;
        cout<<"sex:"<<sex<<endl;
    }
private:
    int num;
    string name;
    char sex;
};
Student :: Student(int nu,string nam,char se) {
    num = nu;
    name = nam;
    sex = se;
}
//公有继承//
/*
class Student1 : public Student {
    public:
    void display1() {
        display();
        cout<<"grade:"<<grade<<endl;
    }
    void getgrade() {
        cin>>grade;
    }
    private:
    int grade;
};
*/
//私有继承//
/*
class Student1 : private Student {
    public:
    void display1() {
        display();
        cout<<"grade:"<<grade<<endl;
    }
    void getGrade() {
        cin>>grade;
    }
    private:
    int grade;
};
*/
//保护继承//
class Student1 : protected Student {
public:
    Student1(int nu = 0,string nam = "zhangsan",char se = 'm',int gr = 0):Student(nu,nam,se),grade(gr){}
    void display1() {
        display();
        cout<<"grade:"<<grade<<endl;
    }
    void getGrade() {
        cin>>grade;
    }
    ~Student1(){}
private:
    int grade;
};
int main() {
    Student1 stu1(1,"lisi",'f',12);
    stu1.getGrade();
    stu1.display1();
    return 0;
}