#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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
void add_employee(int salary,int departmant,vector<Employee> &v){
    *fid+=1;
    Employee ey;
    ey.set_id(*fid);
    ey.set_salary(salary);
    ey.set_departmant(departmant);
    v.insert(v.end(),ey);
}

void update_employee(int id,int salary,int departmant,vector<Employee> &v){
    int b=0;
    int a=0;
    for(unsigned int i=0;i<v.size();i++){
        if(id==v[i].get_id()){
            b=1;
            break;
        }
        a++;
    }
    if(b==0){
        cout<<"ERROR: An invalid ID to update";
        return;
    }
    else if(b==1){
        v[a].set_departmant(departmant);
        v[a].set_salary(salary);
    }
}
void delete_employee(int id,vector<Employee> &v){
    int b=0;
    int a=0;
    for(unsigned int i=0;i<v.size();i++){
        if(id==v[i].get_id()){
            b=1;
            break;
        }
        a++;
    }
    //cout<<a;
    if(b==0){
        cout<<"ERROR: An invalid ID to delete";
        return;
    }
    if(v.size()==0){
        cout<<"ERROR: There is no Employee";
        return;
    }
    v.erase(v.begin()+a);    
}

int main(int argc, char** argv){
    ifstream file1;
    file1.open(argv[1]);
    string line;
    vector<Employee> v1;
    int i=0;
    while(getline(file1,line)){
        if(i>0){
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
                    v1.insert(v1.end(),en);
                }
            }
        }
        i++;
    }
    /*cout<<v1.size()<<"\n";
    for(int a=0;a<v1.size();a++){
        cout<<v1[a].get_id()<<"\n";
    }*/
    *fid=v1.size();
    //cout<<*fid<<endl;
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

            add_employee(maas,konum,v1);
        }
        else if(actione=="UPDATE"){
            line2.erase(0,bingo+1);
            size_t bingo2=line2.find(";");
            int kisi=stoi(line2.substr(0,bingo2));
            line2.erase(0,bingo2+1);
            bingo2=line2.find(";");
            maas=stoi(line2.substr(0,bingo));
            konum=stoi(line2.substr(bingo2+1,line2.length()));
            update_employee(kisi,maas,konum,v1);


        }
        else if(actione=="DELETE"){
            line2.erase(0,bingo+1);
            int kim=stoi(line2);
            delete_employee(kim,v1);
        }
    }
    ofstream mifile("vector_solution.csv");
    mifile<<"Employee_ID;Salary;Department"<<"\n";
    //cout<<v1[5].get_id();
    for(unsigned int i=0;i<v1.size();i++){
        mifile<<v1[i].get_id()<<";"<<v1[i].get_salary()<<";"<<v1[i].get_departman()<<"\n";
    }
    mifile.close();
    /* @Author
    StudentName :<Onat_Budak>
    StudentID :<150210086>
    Date :< 22.10.2023 > */

    return 0;
}