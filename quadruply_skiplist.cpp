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

class QuadruplySkipList_Node{
    private:
        Employee * data;
        QuadruplySkipList_Node * next;
        QuadruplySkipList_Node * prev;
        QuadruplySkipList_Node * above;
        QuadruplySkipList_Node * below;
    public:
        QuadruplySkipList_Node(Employee*emmp=NULL){
            data=emmp;
            next=NULL;
            prev=NULL;
            above=NULL;
            below=NULL;
        }
        Employee* get_data(){
            return data;
        }
        QuadruplySkipList_Node* get_next(){
            return next;
        }
        QuadruplySkipList_Node* get_prev(){
            return prev;
        }
        QuadruplySkipList_Node* get_below(){
            return below;
        }
        QuadruplySkipList_Node* get_above(){
            return above;
        }
        void set_data(Employee* empp){
            data=empp;
            return;
        }
        void set_next(QuadruplySkipList_Node* n){
            next=n;
            return;
        }
        void set_prev(QuadruplySkipList_Node* p){
            prev=p;
            return;
        }
        void set_above(QuadruplySkipList_Node* a){
            above=a;
            return;
        }
        void set_below(QuadruplySkipList_Node* b){
            below=b;
            return;
        }
        
};

class QuadruplySkipList{
    private:
        int height;
        QuadruplySkipList_Node * head;
    public:
        QuadruplySkipList(int height_in=0){
            height=height_in;
            head=NULL;
        }
        void insert(Employee* emp){
            QuadruplySkipList_Node * l_hold=NULL;
            if(head==NULL){
                Employee* e=new Employee(INT32_MAX,0,0);
                QuadruplySkipList_Node* temp=new QuadruplySkipList_Node(e);
                QuadruplySkipList_Node* temp1=new QuadruplySkipList_Node(e);
                temp->set_next(temp1);

                head =temp;
                if(height<1){
                    return;
                }
                for(int i=0;i<height-1;i++){
                    QuadruplySkipList_Node *temp2=new QuadruplySkipList_Node(e);
                    QuadruplySkipList_Node *temp3=new QuadruplySkipList_Node(e);
                    temp2->set_next(temp3);
                    temp2->set_above(temp);
                    temp3->set_above(temp1);
                    temp->set_below(temp2);
                    temp1->set_below(temp3);
                    temp=temp->get_below();
                    temp1=temp1->get_below();

                }
            }
            int height_s=2;
            QuadruplySkipList_Node* temp4=head;
            QuadruplySkipList_Node* temp5=new QuadruplySkipList_Node(emp);
            while(true){
                if(temp4->get_next()->get_data()->get_id()<emp->get_id()){
                    temp4=temp4->get_next();
                    //cout<<"1"<<"\n";
                }
                else if(temp4->get_next()->get_data()->get_id()>emp->get_id()){
                    if(temp4->get_below()==NULL){
                        temp5->set_next(temp4->get_next());
                        temp5->set_prev(temp4);
                        temp4->set_next(temp5);
                        l_hold=temp5;
                        while(rand()%2==1){
                            //cout<<4<<endl;
                            if(height_s>height){
                                break;
                            }
                            height_s++;
                            while(temp4->get_above()==NULL){
                                if(temp4->get_prev()==NULL){
                                    break;
                                }
                                temp4=temp4->get_prev();
                            }
                            temp4=temp4->get_above();
                            QuadruplySkipList_Node * temp_ab= new QuadruplySkipList_Node(emp);
                            temp_ab->set_next(temp4->get_next());
                            temp_ab->set_prev(temp4);
                            temp_ab->set_below(l_hold);
                            if(l_hold!=NULL){
                                l_hold->set_above(temp_ab);
                            }
                            l_hold=temp_ab;
                            temp4->set_next(temp_ab);

                        }
                        return;
                    }
                    else if(temp4->get_below()!=NULL){
                        temp4=temp4->get_below();
                    }
                }
            }
        }
        void print(){
            QuadruplySkipList_Node* p=head;
            while(p!=NULL&&p->get_below()!=NULL){
                p=p->get_below();
            }
            while(p->get_next()!=NULL){
                cout<<p->get_data()->get_id()<<endl;
                p=p->get_next();
            }
        }
        Employee* search(int s_id){
            QuadruplySkipList_Node* asli=head;
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
            QuadruplySkipList_Node* remove_f=head;
            while(true){
                if(remove_f->get_next()->get_data()->get_id()<r_id){
                    remove_f=remove_f->get_next();
                }
                else if(remove_f->get_next()->get_data()->get_id()>r_id){
                    if(remove_f->get_below()==NULL){
                        cout<<"ERROR: An invalid ID to delete"<<"\n";
                        return;
                    }
                    remove_f=remove_f->get_below();
                }
                else if(remove_f->get_next()->get_data()->get_id()==r_id){
                    while(true){
                        QuadruplySkipList_Node* remove_temp;
                        remove_f->get_next()->get_next()->set_prev(remove_f);
                        remove_temp=remove_f->get_next();
                        remove_f->set_next(remove_temp->get_next());
                        if(remove_temp->get_below()!=NULL){
                            remove_f=remove_temp->get_below()->get_prev();
                            //delete remove_temp;
                        }
                        else if(remove_temp->get_below()==NULL){
                            //delete remove_temp;
                            return;
                        }
                        
                        

                    }
                    
                }
                
            }
            
        }
        void DumpToFile(ofstream & outfile){
            QuadruplySkipList_Node * write =head;
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
int fid=0;
int main(int argc,char** argv){
    //clock_t start =clock();
    srand(time(0));
    //cout<<INT64_MAX<<endl;
    QuadruplySkipList*L=new QuadruplySkipList(4);
    ifstream file1;
    file1.open(argv[1]);
    int i=0;
    string line;
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
    fid=i;
    ifstream file_o;
    int test=0;
    file_o.open(argv[2]);
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
            fid++;
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
    ofstream file2("quadruply_output.csv");
    L->DumpToFile(file2);
    file2.close();
    //clock_t end= clock();
    return 0;


}
/*      
@Author
    StudentName :<Onat_Budak>
    StudentID :<150210086>
    Date :< 22.10.2023 >
*/

