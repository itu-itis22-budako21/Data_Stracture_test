#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int sira=0;
int buyukluk=0;
int *for_id=&sira;
int *for_size=&buyukluk;


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

Employee* add_employe(int salary,int derpartmant,Employee arr[]){
    *for_size+=1;
    *for_id+=1;
    Employee*a=new Employee[*for_size];
    for(int i=0;i<(*for_size);i++){
        a[i]=arr[i];
    }
    a[(*for_size)-1].set_id(*for_id);
    a[(*for_size)-1].set_salary(salary);
    a[*(for_size)-1].set_departmant(derpartmant);
    //delete arr;
    return a;
};
void employee_update(int id,int salary,int departman,Employee arr[]){
    int b=0;
    int a=0;
    for(int i=0;i<*for_size;i++){
        if(id==arr[i].get_id()){
            b=1;
            break;
        }
        a++;
    }
    if(b==0){
        cout<<"ERROR: An invalid ID to update";
    }
    else if(b==1){
        arr[a].set_departmant(departman);
        arr[a].set_salary(salary);
    }
}
Employee* employee_delete(int id,Employee arr[]){

    int b=0;
    int a=0;
    for(int i=0;i<*for_size;i++){
        if(id==arr[i].get_id()){
            b=1;
            break;
        }
        a++;
    }
    //cout<<a;
    if(b==0){
        cout<<"ERROR: An invalid ID to delete";
    }
    if(*for_size==0){
        cout<<"ERROR: There is no Employee";
    }
    *for_size-=1;
    Employee* c=new Employee[*for_size];
    //cout<<*for_size;
    int d=0;
    for(int i=0;i<*for_size;i++){
        if(i==a){
            d++;
        }
        c[i]=arr[d];
        d++;
        
    }
    //cout<<c[499998].get_salary();
    delete []arr;
    return c;
}


int main(int argc, char** argv){
    ifstream file;
    file.open(argv[1]);
    string line;
    
    int i=0;
    while (getline(file,line)){
        *for_id+=1;
        *for_size+=1;
        //cout<<line<<endl;
    }
    *for_id-=1;
    *for_size-=1;
    Employee *e=new Employee[*for_size+1];
    file.close();
    file.open(argv[1]);
    //cout<<*for_size<<endl;
    while (getline(file,line)){
        if(i>0){
            for(int j=0;j<3;j++){
                
                size_t indc=line.find(";");
                string part=line.substr(0,indc);
                if(j==2){
                    part=line;
                }
                if(j==0){
                    e[i-1].set_id(stoi(part));
                    line.erase(0,indc+1);
                }
                if(j==1){
                    e[i-1].set_salary(stoi(part));
                    //cout<<part;
                    line.erase(0,indc+1);
                }
                if(j==2){
                    e[i-1].set_departmant(stoi(part));
                }
            }
        }

        i++;
    }
    ifstream file2;
    file2.open(argv[2]);
    string line2;
    //e=add_employe(56,56,e);
    //cout<<*for_size;


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

            e=add_employe(maas,konum,e);
        }
        else if(actione=="UPDATE"){
            line2.erase(0,bingo+1);
            size_t bingo2=line2.find(";");
            int kisi=stoi(line2.substr(0,bingo2));
            line2.erase(0,bingo2+1);
            bingo2=line2.find(";");
            maas=stoi(line2.substr(0,bingo));
            konum=stoi(line2.substr(bingo2+1,line2.length()));
            employee_update(kisi,maas,konum,e);


        }
        else if(actione=="DELETE"){
            line2.erase(0,bingo+1);
            int kim=stoi(line2);
            e=employee_delete(kim,e);
        }
    }

    file.close();
    ofstream mifile("array_solution.csv");
    mifile<<"Employee_ID;Salary;Department"<<endl;
    for(int i=0;i<*for_size;i++){
        mifile<<e[i].get_id()<<";"<<e[i].get_salary()<<";"<<e[i].get_departman()<<"\n";
    }
    mifile.close();
    /* @Author
    StudentName :<Onat_Budak>
    StudentID :<150210086>
    Date :< 22.10.2023 > */














    return 0;
    
}

