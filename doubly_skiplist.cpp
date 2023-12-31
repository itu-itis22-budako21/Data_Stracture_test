#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

class Employee{
    private:
        int id;
        int salary;
        int department;

    public:
        Employee(int i=0,int s=0,int d=0){
            id=i;
            salary=s;
            department=d;
        }
        int get_id(){
            return id;
        }
        int get_dep(){
            return department;
        }
        int get_sal(){
            return salary;
        }
        void set_id(int idd){
            id=idd;
            return; 
        }
        void set_dep(int depp){
            department=depp;
            return;
        }
        void set_sal(int sal){
            salary=sal;
            return;
        }
};

class DoublySkipList_Node{
    private:
        Employee* data;
        DoublySkipList_Node * next;
        DoublySkipList_Node * below;
    public:
        DoublySkipList_Node(Employee*emmp=NULL){
            data=emmp;
            next=NULL;
            below=NULL;
        }
        ~DoublySkipList_Node(){
        }
        Employee* get_data(){
            return data;
        }
        void set_data(Employee* empp){
            data=empp;
            return;
        }
        DoublySkipList_Node* get_next(){
            return next;
        }
        void set_next(DoublySkipList_Node* nxt){
            next=nxt;
        }
        DoublySkipList_Node* get_below(){
            return below;
        }
        void set_below(DoublySkipList_Node* blw){
            below=blw;
        }
};
int fid=0;
class DoublySkipList{
    private:
        DoublySkipList_Node* head;
        int height; 
    public:
        DoublySkipList(int height_in=0){
            height=height_in;
            head=NULL;
        }
        ~DoublySkipList(){
            while(head!=NULL){
                DoublySkipList_Node* left;
                left=head;
                head=head->get_below();
                    while(left!=NULL){
                        DoublySkipList_Node* move1=left;
                        left=left->get_next();
                        if(move1->get_below()==NULL){
                            delete move1->get_data();
                        }
                        delete move1;
                        
                    }

                
            }

        }
        void insert(Employee* emp){
            fid++;
            if(head==NULL){
                Employee* e=new Employee(INT32_MAX,0,0);
                DoublySkipList_Node* temp1= new DoublySkipList_Node(e);
                DoublySkipList_Node* temp2= new DoublySkipList_Node(e);
                temp1->set_next(temp2);
                head=temp1;
                if(height<1){
                    return;
                }
                for (int i = 0; i < height-1; i++)
                {
                    DoublySkipList_Node* temp3=new DoublySkipList_Node(e);
                    DoublySkipList_Node* temp4=new DoublySkipList_Node(e);
                    temp1->set_below(temp3);
                    temp2->set_below(temp4);
                    temp3->set_next(temp4);
                    temp1=temp1->get_below();
                    temp2=temp2->get_below();
                    //delete temp3;
                    //delete temp4;
                }
                //delete temp1;
                //delete temp2;
            }
            DoublySkipList_Node* temp5=head;
            DoublySkipList_Node* l_hold=NULL;
            
            int times=0;
            while(times<(height-1)&&rand()%2==1){
                times++;
            }
            //cout<<times<<endl;
            for(int i=0;i<(height-1)-times;i++){
                temp5=temp5->get_below();
            }
            for(int j=0;j<times+1;j++){
                while(temp5->get_next()->get_data()->get_id()<emp->get_id()){
                    temp5=temp5->get_next();
                }
                DoublySkipList_Node* add=new DoublySkipList_Node(emp);
                add->set_next(temp5->get_next());
                temp5->set_next(add);
                if(l_hold!=NULL){
                    l_hold->set_below(add);
                }
                l_hold=add;
                temp5=temp5->get_below();
                

            }
            return;
        }
        Employee* search(int s_id){
            DoublySkipList_Node* asli=head;
            while(true){
                if(asli->get_next()->get_data()->get_id()<s_id){
                    asli=asli->get_next();
                }
                else if(asli->get_next()->get_data()->get_id()>s_id){
                    if(asli->get_below()==NULL){
                        return NULL;
                    }
                    asli=asli->get_below();
                }
                else if(asli->get_next()->get_data()->get_id()==s_id){
                    return asli->get_next()->get_data();
                }
            }
            return asli->get_next()->get_data();
        }
        void remove(int r_id){
            DoublySkipList_Node* top_r=head;
            while(true){
                if(top_r->get_next()->get_data()->get_id()<r_id){
                    top_r=top_r->get_next();
                }
                else if(top_r->get_next()->get_data()->get_id()>r_id){
                    if(top_r->get_below()==NULL){
                        cout<<"ERROR: An invalid ID to delete"<<"\n";
                        return;
                    }
                    top_r=top_r->get_below();
                }
                else if(top_r->get_next()->get_data()->get_id()==r_id){
                    DoublySkipList_Node* r=top_r->get_next();
                    top_r->set_next(r->get_next());
                    if(r->get_below()==NULL){
                        delete r->get_data();
                    }
                    delete r;
                    if(top_r->get_below()==NULL){
                        break;
                    }
                    top_r=top_r->get_below();
                }
            }
        }
        void DumpToFile(ofstream & outfile){
            DoublySkipList_Node * write =head;
            while(write->get_below()!=NULL){
                write=write->get_below();
            }
            outfile<<"Employee_ID;Salary;Department"<<"\n";
            int check =0;
            while(write->get_next()!=NULL){
                if(check==0){
                    check++;
                    write=write->get_next();
                    continue;
                }
                outfile<<write->get_data()->get_id()<<";"<<write->get_data()->get_sal()<<";"<<write->get_data()->get_dep()<<"\n";
                write=write->get_next();
                
            }
        }
};

int main(int argc,char** argv){
    srand(time(0));
    //clock_t start =clock();
    DoublySkipList* L=new DoublySkipList(4);
    ifstream file1;
    file1.open("10k_employees.csv");
    string line;
    int i=0;
    while (getline(file1,line)){
        if(i>0){
            Employee* add=new Employee;
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
                    add->set_id(id);
                    add->set_sal(salary);
                    add->set_dep(dep);
                    L->insert(add);
                    //cout<<"s"<<"\n";
                }
            }
        }
        i++;
    }
    cout<<fid<<endl;
    ifstream file_o;
    int test=0;
    file_o.open("operations_for_10k_1.csv");
    while(getline(file_o,line)){
        test++;
        size_t bingo=line.find(";");
        string actione=line.substr(0,bingo);
        int maas=0;
        int konum=0;
        //cout<<test<<"\n";
        if(actione=="ADD"){
            line.erase(0,bingo+1);
            size_t bingo2=line.find(";");
            //cout<<bingo2;
            maas=stoi(line.substr(0,bingo2));
            konum=stoi(line.substr(bingo2+1,line.length()));

            Employee * ad= new Employee(fid,maas,konum);
            L->insert(ad);
            //cout<<"as"<<endl;


            //cout<<*fid<<"\n";
        }
        else if(actione=="UPDATE"){
            line.erase(0,bingo+1);
            size_t bingo2=line.find(";");
            int kisi=stoi(line.substr(0,bingo2));
            line.erase(0,bingo2+1);
            bingo2=line.find(";");
            maas=stoi(line.substr(0,bingo));
            konum=stoi(line.substr(bingo2+1,line.length()));
            Employee* update=L->search(kisi);
            if(update==NULL){
                cout<<"ERROR: An invalid ID to update"<<"\n";
                continue;
            }
            update->set_sal(maas);
            update->set_dep(konum);
        }
        else if(actione=="DELETE"){
            line.erase(0,bingo+1);
            int kim=stoi(line);
            L->remove(kim);
            //cout<<"del"<<endl;
            
        }
    }

    ofstream file3("outputt.csv");
    L->DumpToFile(file3);
    //cout<<fid<<endl;
    file3.close();
    delete L;
    //clock_t end =clock();
    //cout<<L->search(1)->get_dep()<<endl;
    return 0;
}
/*      
@Author
    StudentName :<Onat_Budak>
    StudentID :<150210086>
    Date :< 22.10.2023 >
*/