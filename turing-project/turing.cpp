#include<iostream>
#include<fstream>
#include<cstring>
#include<set>

using namespace std;
class Delta{
public:
    string old_states;
    string old_signs;
    string new_signs;
    string directions;
    string new_states;
    void Print() const {
        cout<<"\""<<old_states <<"/"<<old_signs <<"/"<<new_signs <<"/"<<directions <<"/"<<new_states <<"\""<<endl;
    }
    bool operator < (const Delta &b) const{
        if(this->old_states != b.old_states){
            return this->old_states < b.old_states;
        }
        if(this->old_signs != b.old_signs){
            return this->old_signs < b.old_signs;
        }
        if(this->new_signs != b.new_signs){
            return this->new_signs < b.new_signs;
        }
        if(this->directions != b.directions){
            return this->directions < b.directions;
        }
        if(this->new_states != b.new_states){
            return this->new_states < b.new_states;
        }
        return false;
    }
};
class TuringMachine{
private:
    set<string> Q;
    set<char> S;
    set<char> G;
    string q0;
    char B;
    set<string> F;
    int N;
    set<Delta> D;
    bool CheckinQ(string s){
        set<string>::iterator iter = Q.find(s);
        if(iter==Q.end()){
            return false;
        }
        return true;
    }
    bool CheckinS(char s){
        set<char>::iterator iter = S.find(s);
        if(iter==S.end()){
            return false;
        }
        return true;
    }
    bool CheckinG(char s){
        set<char>::iterator iter = G.find(s);
        if(iter==G.end()){
            return false;
        }
        return true;
    }
    bool CheckinF(string s){
        set<string>::iterator iter = F.find(s);
        if(iter==F.end()){
            return false;
        }
        return true;
    }
    void PrintParser(){
        set<string>::iterator iter1 = Q.begin();
        while (iter1!=Q.end()){
            cout<<"\""<<*iter1<<"\",";
            iter1++;
        }
        cout<<endl;

        set<char>::iterator iter2 = S.begin();
        while (iter2!=S.end()){
            cout<<"\""<<*iter2<<"\",";
            iter2++;
        }
        cout<<endl;

        set<char>::iterator iter3 = G.begin();
        while (iter3!=G.end()){
            cout<<"\""<<*iter3<<"\",";
            iter3++;
        }
        cout<<endl;

        cout<<"\""<<q0<<"\""<<endl;

        cout<<"\""<<B<<"\""<<endl;

        set<string>::iterator iter4 = F.begin();
        while (iter4!=F.end()){
            cout<<"\""<<*iter4<<"\",";
            iter4++;
        }
        cout<<endl;

        cout<<"\""<<N<<"\""<<endl;

        set<Delta>::iterator iter5 = D.begin();
        while (iter5!=D.end()){
            (*iter5).Print();
            iter5++;
        }
        cout<<endl;
    }
public:
    TuringMachine(char *tm_filename){
        ifstream infile;
        infile.open(tm_filename, ios::in);
        if(!infile.is_open()){
            fprintf(stderr, "no file %s\n", tm_filename);
            exit(-1);
        }
        while(!infile.eof()){
            string str;
            getline(infile,str);
            int cutpoint = -1;
            for(int i=0; i< str.length();i++){
                if(str[i]==';'){
                    cutpoint = i;
                    break;
                }
            }
            if(cutpoint != -1){
                str = str.substr(0,cutpoint);
            }
            string tmp_str = str;
            for(string::iterator it=tmp_str.begin();it!=tmp_str.end();it++){
                if(*it==' '){
                    tmp_str.erase(it);
                    it--;
                }
            }
            if(str.length() == 0 || tmp_str.length() == 0){
                continue;
            }
            if(str[0]=='#' && str[1] == 'Q'){
                int p1 = -1, p2 = -1;
                for(int i=0; i< str.length();i++){
                    if(str[i] == '{' || str[i] == '}' || str[i] == ','){
                        p1 = p2;
                        p2 = i;
                        if(p1!=-1 && p2!=-1){
                            string tmp_q = str.substr(p1+1,p2-p1-1);
                            // cout<<tmp_q<<endl;
                            Q.insert(tmp_q);
                        }
                    }
                }
            }
            else if(str[0]=='#' && str[1] == 'S'){
                int flag = 0;
                for(int i=0; i< str.length();i++){
                    if(str[i] == '{' || str[i] == ','){
                        flag = 1;
                    }
                    else if (str[i]!=' '){
                        if(flag == 1){
                            char tmp_s = str[i];
                            // cout<<tmp_s<<endl;
                            S.insert(tmp_s);
                            flag = 0;
                        }
                    }
                }
            }
            else if(str[0]=='#' && str[1] == 'G'){
                int flag = 0;
                for(int i=0; i< str.length();i++){
                    if(str[i] == '{' || str[i] == ','){
                        flag = 1;
                    }
                    else{
                        if(flag == 1){
                            char tmp_g = str[i];
                            // cout<<tmp_g<<endl;
                            G.insert(tmp_g);
                            flag = 0;
                        }
                    }
                }
            }
            else if(str[0]=='#' && str[1] == 'q' && str[2] == '0'){
                string tmp = str.substr(3,str.length()-3);
                for(string::iterator it=tmp.begin();it!=tmp.end();it++){
                    if(*it==' '||*it=='='){
                        tmp.erase(it);
                        it--;
                    }
                }
                q0 = tmp;
                // cout<<tmp<<endl;
            }
            else if(str[0]=='#' && str[1] == 'B'){
                string tmp = str.substr(2,str.length()-2);
                for(string::iterator it=tmp.begin();it!=tmp.end();it++){
                    if(*it==' '||*it=='='){
                        tmp.erase(it);
                        it--;
                    }
                }
                B = tmp[0];
                // cout<<tmp<<endl;
            }
            else if(str[0]=='#' && str[1] == 'F'){
                int p1 = -1, p2 = -1;
                for(int i=0; i< str.length();i++){
                    if(str[i] == '{' || str[i] == '}' || str[i] == ','){
                        p1 = p2;
                        p2 = i;
                        if(p1!=-1 && p2!=-1){
                            string tmp_f = str.substr(p1+1,p2-p1-1);
                            // cout<<tmp_f<<endl;
                            F.insert(tmp_f);
                        }
                    }
                }
            }
            else if(str[0]=='#' && str[1] == 'N'){
                string tmp = str.substr(2,str.length()-2);
                for(string::iterator it=tmp.begin();it!=tmp.end();it++){
                    if(*it==' '||*it=='='){
                        tmp.erase(it);
                        it--;
                    }
                }
                N = atoi(tmp.c_str());
            }
            else{
                // cout<<str<<endl;
                int flag = -1;
                int p1,p2;
                int cnt = 0;
                Delta d;
                for(int i=0; i< str.length();i++){
                    if (str[i] != ' ' && flag == -1){
                        p1 = i;
                        flag = 1;
                    }
                    else if((str[i] == ' ' || i == str.length()-1) && flag == 1){
                        if(i == str.length()-1 && str[i] != ' ') i ++;
                        p2 = i;
                        string tmp_d = str.substr(p1,p2-p1);

                        switch (cnt){
                            case 0:
                                d.old_states = tmp_d;
                                break;
                            case 1:
                                d.old_signs = tmp_d;
                                break;
                            case 2:
                                d.new_signs = tmp_d;
                                break;
                            case 3:
                                d.directions = tmp_d;
                                break;
                            case 4:
                                d.new_states = tmp_d;
                                break;
                            default:
                                break;
                        }
                        cnt++;
                        flag = -1;
                    }
                }
                D.insert(d);
            }

        }
        infile.close();
    }
    
    void CheckParser(){
        // PrintParser();
        if(!CheckinQ(q0)){
            fprintf(stderr, "syntax error q0\n");
            exit(0);
        }

        if(!CheckinG(B)){
            fprintf(stderr, "syntax error B\n");
            exit(0);
        }
        set<string>::iterator iter1 = F.begin();
        while (iter1!=F.end()){
            if(!CheckinQ(*iter1)){
                fprintf(stderr, "syntax error F\n");
                exit(0);
            }
            iter1++;
        }
        set<Delta>::iterator iter2 = D.begin();
        while (iter2!=D.end()){
            if(!CheckinQ((*iter2).old_states) || !CheckinQ((*iter2).new_states)){
                cout<<(*iter2).old_states<<endl;
                cout<<!CheckinQ((*iter2).old_states)<<endl;
                cout<<(*iter2).new_states<<";"<<endl;
                cout<<!CheckinQ((*iter2).new_states)<<endl;
                fprintf(stderr, "syntax error D_states\n");
                exit(0);
            }
            for (int i = 0; i < (*iter2).old_signs.length();i++){
                if(!CheckinG((*iter2).old_signs[i])){
                    fprintf(stderr, "syntax error D_old_signs\n");
                    exit(0);
                }
            }
            for (int i = 0; i < (*iter2).new_signs.length();i++){
                if(!CheckinG((*iter2).new_signs[i])){
                    fprintf(stderr, "syntax error D_new_signs\n");
                    exit(0);
                }
            }
            for (int i = 0; i < (*iter2).directions.length();i++){
                if((*iter2).directions[i]!='l' && (*iter2).directions[i]!='r' && (*iter2).directions[i]!='*'){
                    cout<<(*iter2).directions[i]<<endl;
                    fprintf(stderr, "syntax error D_direction\n");
                    exit(0);
                }
            }
            iter2++;
        }
    }
};
int main(int argc, char **argv){
    TuringMachine tm = TuringMachine(argv[1]);
    tm.CheckParser();
    return 0;
}