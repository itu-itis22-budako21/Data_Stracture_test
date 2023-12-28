#include <iostream>
#include <fstream>
#include <string>
#include <map>
//#include <time.h>

using namespace std;

class Employee{
    private:
        int id;
        int salary;
        int department;
    public:
        Employee(int idd=0,int salaryy=0,int departmannt=0){
            set_id(idd);
            set_salary(salaryy);
            set_department(departmannt);
        }
        //~Employee();
        void set_salary(int a){
            salary=a;
        };
        void set_id(int a){
            id=a;
        };
        void set_department(int a){
            department=a;
        };
        int get_id(){
            return id;
        };
        int get_salary(){
            return salary;
        };
        int get_department(){
            return department;
        };
};
int size=0;
int main(int argc, char *argv[]){
    //clock_t start =clock();
    ifstream file1;
    file1.open(argv[1]);
    string line;
    map<int,Employee*>tree;
    int o=0;
    while(getline(file1,line)){
        if(o==0){
            o++;
            continue;
        }
        string id;
        int indc=0;
        indc =line.find(";");
        id=line.substr(0,indc);
        line.erase(0,indc+1);
        indc=line.find(";");
        string sal=line.substr(0,indc);
        line.erase(0,indc+1);
        string dep=line;
        Employee *temp=new Employee;
        temp->set_department(stoi(dep));
        temp->set_id(stoi(id));
        temp->set_salary(stoi(sal));
        tree[temp->get_id()]=temp;
        size++;
    }
    ifstream file2;
    file2.open(argv[2]);
    while(getline(file2,line)){
        string actione = line;
        int nokta=0;
        nokta = line.find(";");
        actione=line.substr(0,nokta);
        string numara;
        string salar;
        string depart;
        line.erase(0,nokta+1);
        if(actione=="ADD"){
            nokta = line.find(";");
            salar = line.substr(0,nokta);
            line.erase(0,nokta+1);
            depart=line;
            Employee* tempA=new Employee;
            tempA->set_id(++size);
            tempA->set_department(stoi(depart));
            tempA->set_salary(stoi(salar));
            tree[tempA->get_id()]=tempA;
            
        }
        if(actione=="DELETE"){
            int rem=0;
            rem=stoi(line);
            if(rem>size||tree[rem]==0){
                cout<<"ERROR: An invalid ID to delete"<<"\n";
                continue;
            }
            tree.erase(rem);
        }
        if(actione=="UPDATE"){
            //Employee* tempU=new Employee;
            nokta=line.find(";");
            int idu=stoi(line.substr(0,nokta));
            line.erase(0,nokta+1);
            if(idu>size||tree[idu]==0){
                cout<<"ERROR: An invalid ID to update"<<"\n";
                continue;
            }
            nokta= line.find(";");
            tree[idu]->set_salary(stoi(line.substr(0,nokta)));
            line.erase(0,nokta+1);
            tree[idu]->set_department(stoi(line));
        }

    }    
        ofstream file3("output.csv");
        file3<<"Employee_ID;Salary;Department"<<"\n";
        for (auto itr = tree.begin(); itr != tree.end(); ++itr) {
            file3<<itr->second->get_id()<<";"<<itr->second->get_salary()<<";"<<itr->second->get_department()<<"\n";
        }
        //clock_t end= clock();

}
/* @Author
StudentN ame :< Onat Budak >
StudentID :< 150210086 >
Date :< 18.12.2023 > */