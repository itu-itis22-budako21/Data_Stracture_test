#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>

using namespace std;
int sira=0;
int* fid=&sira;


class Employee{
    private:
        int id;
        int salary;
        int departmant;
    public:
        Employee(int idd=0,int salaryy=0,int departmannt=0){
            set_id(idd);
            set_salary(salaryy);
            set_departmant(departmannt);
        }
        //~Employee();
        void set_salary(int a){
            salary=a;
        };
        void set_id(int a){
            id=a;
        };
        void set_departmant(int a){
            departmant=a;
        };
        int get_id(){
            return id;
        };
        int get_salary(){
            return salary;
        };
        int get_departman(){
            return departmant;
        };

};
void add_employee(int salary,int dep,list<Employee> &l){
    (*fid)++;
    //cout<<l.size();
    Employee mu;
    mu.set_id(*fid);
    mu.set_salary(salary);
    mu.set_departmant(dep);
    l.insert(l.end(),mu);
    return;
}

void update_employee(int id,int salary,int dep,list<Employee> &li){
    int c=0;
    for(auto itr=li.begin();itr!=li.end();itr++){
        if(id==(*itr).get_id()){
            (*itr).set_salary(salary);
            (*itr).set_departmant(dep);
            c++;
        }
    }
    if(c==0){
        cout<<"ERROR: An invalid ID to update";
    }
}

void delete_employee(int id,list<Employee> &li){
    int b=0;
    for(auto itr=li.begin();itr!=li.end();itr++){
        if(id==(*itr).get_id()){
            li.erase(itr);
            b++;
            break;
        }
    }
    if(b==0){
        cout<<"ERROR: An invalid ID to delete";
    }
    if(li.size()==0){
        cout<<"ERROR: There is no Employee";
    }
}

int main(int argc,char** argv){
    ifstream file1;
    file1.open(argv[1]);
    string line;
    list<Employee> l1;
    int u=0;
    while(getline(file1,line)){
        if(u>0){
            Employee en;
            for(int j=0;j<3;j++){

                size_t indc=line.find(";");
                string part=line.substr(0,indc);
                if(j==2){
                    part=line;
                }
                if(j==0){
                    //cout<<part<<endl;
                    en.set_id(stoi(part));
                    line.erase(0,indc+1);
                }
                if(j==1){
                    en.set_salary(stoi(part));
                    //cout<<part;
                    line.erase(0,indc+1);
                }
                if(j==2){
                    en.set_departmant(stoi(part));
                    l1.insert(l1.end(),en);
                }
            }
        }
        u++;
    }
    /*for(auto itr=l1.begin();itr!=l1.end();itr++){
        cout<<(*itr).get_id()<<"\n";
    }*/
    //cout<<l1.size();
    *fid=l1.size();
    file1.close();


    ifstream file2;
    file2.open(argv[2]);
    string line2;
    while(getline(file2,line2)){
        size_t bingo=line2.find(";");
        string actione=line2.substr(0,bingo);
        int maas=0;
        int konum=0;
        if(actione=="ADD"){
            line2.erase(0,bingo+1);
            size_t bingo2=line2.find(";");
            //cout<<bingo2;
            maas=stoi(line2.substr(0,bingo2));
            konum=stoi(line2.substr(bingo2+1,line2.length()));

            add_employee(maas,konum,l1);
        }
        else if(actione=="UPDATE"){
            line2.erase(0,bingo+1);
            size_t bingo2=line2.find(";");
            int kisi=stoi(line2.substr(0,bingo2));
            line2.erase(0,bingo2+1);
            bingo2=line2.find(";");
            maas=stoi(line2.substr(0,bingo));
            konum=stoi(line2.substr(bingo2+1,line2.length()));
            update_employee(kisi,maas,konum,l1);


        }
        else if(actione=="DELETE"){
            line2.erase(0,bingo+1);
            int kim=stoi(line2);
            delete_employee(kim,l1);
        }
    }
    //cout<<l1.size();
    ofstream file3;
    file3.open("list_solution.csv");
    file3<<"Employee_ID;Salary;Department"<<"\n";

    for(auto itr=l1.begin();itr!=l1.end();itr++){
        file3<<(*itr).get_id()<<";"<<(*itr).get_salary()<<";"<<(*itr).get_departman()<<"\n";
    }
    file3.close();
        /* @Author
    StudentName :<Onat_Budak>
    StudentID :<150210086>
    Date :< 22.10.2023 > */
    return 0;
}