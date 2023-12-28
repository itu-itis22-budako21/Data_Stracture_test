#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
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
int a=0;
int*for_id=&a;
class Node{
    private:
        Employee * EmpPtr;
        Node * NodeLeft;
        Node* NodeRight;
    public:
        Node(){
            NodeLeft=NULL;
            NodeRight=NULL;
        }
        void set_empptr(Employee * ptr){
            EmpPtr=ptr;
        }
        void set_left(Node * ptrleft){
            NodeLeft=ptrleft;
        }
        void set_right(Node *ptrright){
            NodeRight=ptrright;
        }
        Node * get_left(){
            return NodeLeft;
        }
        Node * get_right(){
            return NodeRight;
        }
        Employee* get_employee(){
            return EmpPtr;
        }
};

class BinaryTree{
    private:
        Node* root;
    public:
        void set_root(Node* rot){
            root=rot;
        }
        Node* get_root(){
            return root;
        }
        BinaryTree(){
            root=NULL;
        }
        void printToConsole(){
            if(root==NULL){
                return;
            }
            BinaryTree fakeL;
            BinaryTree fakeR;
            fakeL.set_root(root->get_left());
            fakeR.set_root(root->get_right());
            cout<<root->get_employee()->get_id()<<";"<<root->get_employee()->get_salary()<<";"<<root->get_employee()->get_department()<<"\n";
            
            fakeL.printToConsole();
            fakeR.printToConsole();        
        }
        void insert(Employee* emptr){
            int idd=emptr->get_id();
            Node* temp_i=root;
            Node* parent=new Node;
            if(root==NULL){
                root=parent;
                //cout<<root<<endl;
                root->set_empptr(emptr);
            }
            while(temp_i!=NULL){
                if(idd<temp_i->get_employee()->get_id()){
                    parent=temp_i;
                    temp_i=temp_i->get_left();
                }
                else if(idd>temp_i->get_employee()->get_id()){
                    parent=temp_i;
                    temp_i=temp_i->get_right();
                }  
            }
            if(parent->get_employee()->get_id()<idd){
                Node* yeni=new Node;
                yeni->set_empptr(emptr);
                parent->set_right(yeni);
            }
            else if(parent->get_employee()->get_id()>idd){
                Node* yeni1=new Node;
                yeni1->set_empptr(emptr);
                parent->set_left(yeni1);
            }
            (*for_id)++;
        }
        Employee* search(int id){
            /*Employee*Find=NULL;     ////with recursion
            Node* tempN=root;
            if(tempN==NULL){
                return NULL;
            }
            else if(tempN->get_employee()->get_id()==id){
                Find=tempN->get_employee();
            }
            if(Find!=NULL){
                return Find;
            }
            BinaryTree tempB;
            tempB.set_root(tempN->get_left());
            Find=tempB.search(id);
            if(Find!=NULL){
                return Find;
            }
            tempB.set_root(tempN->get_right());
            Find=tempB.search(id);
            return Find;*/
            Employee * find=NULL;
            Node* tempN=root;
            if(tempN==NULL){
                return NULL;
            }
            while(true){
                if(tempN->get_employee()->get_id()==id){
                    find=tempN->get_employee();
                    return find;
                }
                else if(tempN->get_employee()->get_id()<id){
                    if(tempN->get_right()==NULL){
                        return find;
                    }
                    tempN=tempN->get_right();
                }
                else if(tempN->get_employee()->get_id()>id){
                    if(tempN->get_left()==NULL){
                        return find;
                    }
                    tempN=tempN->get_left();
                }
            }
            
        }
        void printToFile(ofstream &ofile){
            stack<Node*> st;
            Node* cur=root;
            while (cur!=NULL || st.empty()==false){
                while(cur!=NULL){
                    st.push(cur);
                    cur=cur->get_left();
                }
                cur=st.top();
                st.pop();
                ofile<<cur->get_employee()->get_id()<<";"<<cur->get_employee()->get_salary()<<";"<<cur->get_employee()->get_department()<<"\n";
                cur=cur->get_right();
            }
        }
        void remove(int kod){
            int right=0;
            Node * Find;
            Node * parent=NULL;
            Find=root;
            if (root==NULL){
                cout<<"ERROR: An invalid ID to delete"<<"\n";
                return;
            }
            while(root!=NULL){
                if(Find->get_employee()->get_id()==kod){
                    break;
                }
                else if(Find->get_employee()->get_id()<kod){
                    if(Find->get_right()==NULL){
                        cout<<"ERROR: An invalid ID to delete"<<"\n";
                        return;
                    }
                    parent=Find;
                    Find=Find->get_right();
                    right=1;
                }
                else if(Find->get_employee()->get_id()>kod){
                    if(Find->get_left()==NULL){
                        cout<<"ERROR: An invalid ID to delete"<<"\n";
                        return;
                    }
                    parent=Find;
                    Find=Find->get_left();
                    right=2;
                }
            }
            Node*temp;
            Node*tempP;
            if(Find->get_right()!=NULL){
                temp=Find->get_right();
                if(temp->get_left()==NULL){
                    if(right==0){
                        temp->set_left(root->get_left());
                        delete Find;
                        root=temp;
                    }
                    else if(right==1){
                        parent->set_right(Find->get_right());
                        temp->set_left(Find->get_left());
                        delete Find;
                    }
                    else if(right==2){
                        parent->set_left(Find->get_right());
                        temp->set_left(Find->get_left());
                        delete Find;
                    }
                }
                else if(temp->get_left()!=NULL){
                    while (temp->get_left()!=NULL){
                        tempP=temp;
                        temp=temp->get_left();
                    }
                    if(right==0){
                        tempP->set_left(temp->get_right());
                        temp->set_right(root->get_right());
                        temp->set_left(root->get_left());
                        delete Find;
                        root=temp;
                    }
                    else if(right==1){
                        parent->set_right(tempP->get_left());
                        tempP->set_left(temp->get_right());
                        temp->set_left(Find->get_left());
                        temp->set_right(Find->get_right());
                        delete Find;
                    }
                    else if(right==2){
                        parent->set_left(tempP->get_left());
                        tempP->set_left(temp->get_right());
                        temp->set_left(Find->get_left());
                        temp->set_right(Find->get_right());
                        delete Find;
                    }

                }
            

            }
            if(Find->get_right()==NULL){
                if(right==0){
                    delete Find;
                    root=Find->get_left();
                    //delete Find;
                }
                if(right==1){
                    parent->set_right(Find->get_left());
                    delete Find;
                }
                if(right==2){
                    parent->set_left(Find->get_left());
                    delete Find;
                }
            }

        }
        
        
};
int size=0;
int* vsize=&size;

int main(int argc, char *argv[]){
    //clock_t start =clock();
    vector<BinaryTree> v;
    ifstream file1;
    file1.open(argv[1]);
    string line;
    int o=0;
    //Employee e(1,1,1);
    //BinaryTree agac;
    //v.push_back(agac);
    //cout<<v.size();
    //v.at(11).insert(&e);
    while (getline(file1,line)){
        if(o==0){
            o++;
            continue;
        }
        o++;
        string id;
        int indc=0;
        indc =line.find(";");
        id=line.substr(0,indc);
        //cout<<id<<endl;
        line.erase(0,indc+1);
        //cout<<line<<endl;
        indc=line.find(";");
        string sal=line.substr(0,indc);
        line.erase(0,indc+1);
        string dep=line;
        //cout<<"id:"<<id<<" salary: "<<sal<<" depa "<<dep<<endl;
        Employee *temp=new Employee;
        temp->set_department(stoi(dep));
        temp->set_id(stoi(id));
        temp->set_salary(stoi(sal));
        //cout<<temp.get_id()<<endl;
        int index=stoi(id)/5000;
        int dif=index-((*vsize)-1);
        if(dif>0){
            for(int i=0;i<dif;i++){
                BinaryTree temp;
                v.push_back(temp);
                (*vsize)++;
            }
        }
        v[index].insert(temp);
    }
    ifstream file2;
    file2.open(argv[2]);
    while(getline(file2,line)){
        //cout<<line<<"\n";
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
            tempA->set_id((*for_id)+1);
            tempA->set_department(stoi(depart));
            tempA->set_salary(stoi(salar));
            int sayi=tempA->get_id()/5000;
            if(sayi>(*vsize)-1){
                for(int i=0;i<(sayi-(*(vsize)-1));i++){
                    BinaryTree temp;
                    v.push_back(temp);
                    (*(vsize))++;
                }
            }
            v[sayi].insert(tempA);
        }
        if(actione=="DELETE"){
            int rem=0;
            rem=stoi(line);
            int index2=rem/5000;
            if(index2>(*vsize)-1){
                cout<<"ERROR: An invalid ID to delete"<<"\n";
                continue;
            }
            v[index2].remove(rem);
        }
        if(actione=="UPDATE"){
            nokta=line.find(";");
            int idu=stoi(line.substr(0,nokta));
            int index4=idu/5000;
            if(index4>(*vsize)-1){
                cout<<"ERROR: An invalid ID to update"<<"\n";
                continue;
            }
            
            Employee* tempU= v[index4].search(idu);
            if(tempU==NULL){
                cout<<"ERROR: An invalid ID to update"<<"\n";
                continue;
            }
            tempU->set_id(idu);
            line.erase(0,nokta+1);
            nokta = line.find(";");
            tempU->set_salary(stoi(line.substr(0,nokta)));
            line.erase(0,nokta+1);
            tempU->set_department(stoi(line));


        }



    }
    ofstream file3("output.csv");
    file3<<"Employee_ID;Salary;Department"<<"\n";
    for(int j=0;j<int(v.size());j++){
        v[j].printToFile(file3);
    }
    //clock_t end= clock();
}
/* @Author
StudentN ame :< Onat Budak >
StudentID :< 150210086 >
Date :< 18.12.2023 > */