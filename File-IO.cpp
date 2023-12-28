#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;




int main(int argc, char** argv){
    int size=0;
    int id=0;
    ifstream file;
    //cout<<argv[2]<<endl;
    file.open(argv[2]);
    string line;
    string line2;
    ifstream file3;
    file3.open(argv[1]);
    /*ofstream file2;
    file2.open("hw1_sup.csv");*/
    /*while(getline(file3,line2)){
        size++;
        id++;
        file2<<line2<<endl;
    }
    id--;
    size--;
    ifstream file5;
    file5.open("hw1_sup.csv");*/
    int ey=0;

    while(getline(file,line)){
        ifstream file3;
        file3.open(argv[1]);
        ofstream file2;
        file2.open("hw1_sup.csv");
        while(getline(file3,line2)){
            if(ey==0){
                size++;
                id++;
            }
            file2<<line2<<endl;
        }
        if(ey==0){
            size--;
            id--;
        }
        ey++;
        ifstream file5;
        file5.open("hw1_sup.csv");
        size_t bingo=line.find(";");
        string actione=line.substr(0,bingo);
        int maas=0;
        int konum=0;
        //cout<<actione<<endl;
        if(actione=="ADD"){
            id++;
            size++;
            line.erase(0,bingo+1);
            size_t bingo2=line.find(";");
            maas=stoi(line.substr(0,bingo2));
            konum=stoi(line.substr(bingo2+1,line.length()));
            ofstream file4;
            file4.open(argv[1]);
            while(getline(file5,line2)){
                file4<<line2<<endl;
            }
            file4<<id<<";"<<maas<<";"<<konum<<endl;  
            file4.close(); 
        }
        else if(actione=="UPDATE"){
            line.erase(0,bingo+1);
            size_t bingo2=line.find(";");
            int kisi=stoi(line.substr(0,bingo2));
            line.erase(0,bingo2+1);
            bingo2=line.find(";");
            maas=stoi(line.substr(0,bingo));
            konum=stoi(line.substr(bingo2+1,line.length()));
            ofstream file4;
            file4.open(argv[1]);
            int b=0;
            int s=0;
            while(getline(file5,line2)){
                if(b==kisi){
                    file4<<kisi<<";"<<maas<<";"<<konum<<endl;
                    s++;
                }
                if(!(b==kisi)){
                    file4<<line2<<endl;
                }
                b++;
            }
            if(s==0){
                cout<<"ERROR: There is no Employee"<<endl;
            }
            file4.close();
        }
        else if(actione=="DELETE"){
            if(size==0){
                cout<<"ERROR: There is no Employee"<<endl;
            }
            size--;
            line.erase(0,bingo+1);
            int kisi=stoi(line);
            ofstream file4;
            file4.open(argv[1]);
            int s=0;
            int o=0;
            while(getline(file5,line2)){
                if(o==0){
                    file4<<"Employee_ID;Salary;Department"<<endl;
                }
                if(o>0){
                    size_t en=line2.find(";");
                    int anka=stoi(line2.substr(0,en));
                    if(anka==kisi){
                        s++;
                    }
                    if(!(anka==kisi)){
                        file4<<line2<<endl;
                    }
                }
                o++;
            }
            if(s==0){
                cout<<"ERROR: An invalid ID to delete"<<endl;
            }
            file4.close();

        }
        file5.close();
        file2.close();
        file3.close();
    }
    file.close();
    /* @Author
    StudentName :<Onat_Budak>
    StudentID :<150210086>
    Date :< 22.10.2023 > */
}