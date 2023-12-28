#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int sira=0;
int buyukluk=0;
int* fid=&sira;
int* fsi=&buyukluk;

class Employee{
    private:
        int id;
        int salary;
        int departmant;
        Employee* next;
    public:
        Employee(int idd=0,int salaryy=0,int departmannt=0,Employee* ee=NULL){
            set_id(idd);
            set_salary(salaryy);
            set_departmant(departmannt);
            set_next(ee);
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
        void set_next(Employee * ee){
            next=ee;
        }
        int get_id(){
            return id;
        };
        int get_salary(){
            return salary;
        };
        int get_departman(){
            return departmant;
        };
        Employee* nextt(){
            return next;
        }   
};

void add(int id,int salary,int depart,Employee* &ptr){
    Employee* muz=new Employee();
    muz->set_next(ptr);
    muz->set_id(id);
    muz->set_salary(salary);
    muz->set_departmant(depart);
    ptr=muz;
}

void add_employee(int salary,int depart,Employee* &ptr){
    Employee* yah=new Employee();
    Employee* asl;
    *fid+=1;
    *fsi+=1;
    asl=ptr;
    while(asl->nextt()!=NULL){
        asl=asl->nextt();
    }
    asl->set_next(yah);
    yah->set_id(*fid);
    yah->set_salary(salary);
    yah->set_departmant(depart);

}

void employee_update(int id,int salary,int dep,Employee* &ptr){
    Employee* yun=NULL;
    yun=ptr;
    int d=0;
    for(int i=0;i<(*fsi);i++){
        if(yun->get_id()==id){
            d++;
            break;
        }
        yun=yun->nextt();
    }
    if(d==0){
        cout<<"ERROR: An invalid ID to update";
    }
    else if(d==1){
        yun->set_salary(salary);
        yun->set_departmant(dep);
    }
}

void employee_delete(int id,Employee* &ptr){
    //cout<<*fsi<<"\n";
    Employee* er=NULL;
    //Employee* ar=NULL;
    int a=0;
    if((*fsi)==0){
        cout<<"ERROR: There is no Employee";
    }
    er=ptr;
    //ar=ptr;
    /*for(int j=0;j<(*fsi);j++){
        cout<<ar->get_id()<<"\n";
        ar=ar->nextt();
    }*/
    //cout<<id<<endl;
    for(int i=0;i<(*fsi);i++){
        if(er->nextt()==NULL){
            break;
        }
        if(er->get_id()==id){
            er=er->nextt();
            a++;
            *fsi-=1;
            break;
        }
        if(er->nextt()->get_id()==id){
            er->set_next(er->nextt()->nextt());
            *fsi-=1;
            a++;
            break;
        }
        er=er->nextt();
    }
    if(a==0){
        cout<<"ERROR: An invalid ID to delete";
    }
}

int main(int argc,char** argv){
    ifstream file;
    file.open(argv[1]);
    string line;
    Employee* ilk=NULL;
    int i=0;
    while(getline(file,line)){
        if(i>0){
            for(int j=0;j<3;j++){
                
                size_t indc=line.find(";");
                string part=line.substr(0,indc);
                int id;
                int salary;
                int dep;
                if(j==2){
                    part=line;
                }
                if(j==0){
                    id=stoi(part);
                    line.erase(0,indc+1);
                }
                if(j==1){
                    salary=stoi(part);
                    //cout<<part;
                    line.erase(0,indc+1);
                }
                if(j==2){
                    dep=(stoi(part));
                    add(id,salary,dep,ilk);
                }
            }
        (*fid)++;
        (*fsi)++;
        }
        i++;
    }
    Employee* prev=NULL;
    Employee* cur=ilk;
    Employee* nex=ilk;

    while(cur!=NULL){
        nex=nex->nextt();
        cur->set_next(prev);
        prev=cur;
        cur=nex;

    }
    ilk=prev;
    
    /*for(int j=0;j<(*fsi);j++){
        cout<<cur->get_id()<<"\n";
        cur=cur->nextt();
    }*/



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

            add_employee(maas,konum,ilk);
            //cout<<*fid<<"\n";
        }
        else if(actione=="UPDATE"){
            line2.erase(0,bingo+1);
            size_t bingo2=line2.find(";");
            int kisi=stoi(line2.substr(0,bingo2));
            line2.erase(0,bingo2+1);
            bingo2=line2.find(";");
            maas=stoi(line2.substr(0,bingo));
            konum=stoi(line2.substr(bingo2+1,line2.length()));
            employee_update(kisi,maas,konum,ilk);


        }
        else if(actione=="DELETE"){
            line2.erase(0,bingo+1);
            int kim=stoi(line2);
            employee_delete(kim,ilk);
        }
    }

















    ofstream mifile("linked_list_solution.csv");
    mifile<<"Employee_ID;Salary;Department"<<endl;
    Employee* temp=NULL;
    temp=ilk;
    for(int i=0;i<(*fsi);i++){
        mifile<<temp->get_id()<<";"<<temp->get_salary()<<";"<<temp->get_departman()<<"\n";
        temp=temp->nextt();
    }
    mifile.close();
        /* @Author
    StudentName :<Onat_Budak>
    StudentID :<150210086>
    Date :< 22.10.2023 > */
    return 0;
}