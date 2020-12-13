#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<set>
#include<map>
#include<vector>

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
        return false;
    }
};
class Tape{
public:
    map<int,char> tape;
    int left,right,pointer;
    char B;
    Tape(char b){
        left = right = pointer = 0;
        B = b;
    }
    void Left(int l){
        if(l < left) left = l;
    }
    void Right(int r){
        if(r > right) right = r;
    }
    void PrintText(){
        map<int,char>::iterator iter;
        int l=left, r=right;
        int flag = 0;
        for(int i=left;i<right;i++){
            iter = tape.find(i);
            if(iter != tape.end() && (*iter).second != B){
                l = i;
                flag = 1;
                break;
            }
        }
        for(int i= right-1; i>=l; i--){
            iter = tape.find(i);
            if(iter != tape.end() && (*iter).second != B){
                r = i+1;
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            l = r = pointer;
        }
        for(int i = l; i < r; i++){
            iter = tape.find(i);
            char ch = B;
            if(iter!=tape.end()){
                ch = (*iter).second;
            }
            printf("%c", ch);
        }
        if(l==r){
            printf("%c",B);
        }
        printf("\n");
    }
    void Print(int index){
        map<int,char>::iterator iter;
        int l=left, r=right;
        int flag = 0;
        for(int i=left;i<right;i++){
            iter = tape.find(i);
            if(iter != tape.end() && (*iter).second != B){
                l = i;
                flag = 1;
                break;
            }
        }
        for(int i= right-1; i>=l; i--){
            iter = tape.find(i);
            if(iter != tape.end() && (*iter).second != B){
                r = i+1;
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            l = r = pointer;
        }
        if(pointer < l){
            l = pointer;
        }
        if(pointer > r-1){
            r = pointer+1;
        }
        // left = l;
        // right = r;
        printf("Index%d :", index);
        for(int i = l; i < r; i++){
            printf(" %d", i);
        }
        if(l==r){
            printf(" %d", pointer);
        }
        printf("\n");

        printf("Tape%d  :", index);
        for(int i = l; i < r; i++){
            char str[10]={0};
            sprintf(str,"%d",i);
            for(int j = 1; j < strlen(str); j++){
                printf(" ");
            }
            iter = tape.find(i);
            char ch = B;
            if(iter!=tape.end()){
                ch = (*iter).second;
            }
            printf(" %c", ch);
        }
        if(l==r){
            char str[10]={0};
            sprintf(str,"%d",pointer);
            for(int j = 1; j < strlen(str); j++){
                printf(" ");
            }
            printf(" %c",B);
        }
        printf("\n");
        
        printf("Head%d  :", index);
        for(int i = l; i < r; i++){
            char str[10]={0};
            sprintf(str,"%d",i);
            for(int j = 1; j < strlen(str); j++){
                printf(" ");
            }
            char ch = ' ';
            if(i == pointer){
                ch = '^';
            }
            printf(" %c", ch);
        }
        if(l==r){
            char str[10]={0};
            sprintf(str,"%d",pointer);
            for(int j = 1; j < strlen(str); j++){
                printf(" ");
            }
            printf(" ^");
        }
        printf("\n");
    }
};
class TuringMachine{
private:
    bool verbose;
    set<string> Q;
    set<char> S;
    set<char> G;
    string q0;
    char B;
    set<string> F;
    int N;
    set<Delta> D;
    //---------//
    vector<Tape> Tapes;
    string State;

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
    void PrintTapes(int step, string state){
        printf("Step   : %d\n", step);
        for(int i = 0; i < N; i++){
            Tapes.at(i).Print(i);
        }
        printf("State  :%s\n", state.c_str());
        printf("---------------------------------------------\n");
    }
    int Run(){
        int step = 0;
        while(true){
            string old_states = State;
            string old_signs="";
            for(int i = 0; i < N; i++){
                int p = Tapes.at(i).pointer;
                map<int,char>::iterator iter;
                iter = Tapes.at(i).tape.find(p);
                char ch = B;
                if(iter!=Tapes.at(i).tape.end()){
                    ch = (*iter).second;
                }
                old_signs += ch;
            }
            Delta tmp;
            tmp.old_states =State;
            tmp.old_signs = old_signs;
            set<Delta>::iterator iter = D.find(tmp);

            if (iter == D.end()){
                return 1;
            }

            for(int i = 0; i < N; i++){
                int p = Tapes.at(i).pointer;
                Tapes.at(i).tape[p]=(*iter).new_signs[i];
            }
            for(int i = 0; i < N; i++){
                int p = Tapes.at(i).pointer;
                if((*iter).directions[i] =='l'){
                    Tapes.at(i).pointer =p - 1;
                }
                if((*iter).directions[i] =='r'){
                    Tapes.at(i).pointer =p + 1;
                }
                if((*iter).directions[i] =='*'){
                    Tapes.at(i).pointer =p;
                }
                Tapes.at(i).Left(Tapes.at(i).pointer);
                Tapes.at(i).Right(Tapes.at(i).pointer+1);
            }
            State = (*iter).new_states;
            step++;
            if(verbose == true){
                PrintTapes(step,State);
            }
            if(CheckinF(State)){
                return 0;
            }
        }
    }
public:
    TuringMachine(char *tm_filename, bool v){
        verbose = v;
        ifstream infile;
        infile.open(tm_filename, ios::in);
        if(!infile.is_open()){
            fprintf(stderr, "syntax error\n");
            if(verbose == true){
                fprintf(stderr, "Open .tm file Error\n");
            }
            exit(1);
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
                            if(Q.find(tmp_q) != Q.end()){
                                fprintf(stderr, "syntax error\n");
                                if(verbose == true){
                                    fprintf(stderr, "Repeat in Q\n");
                                }
                                exit(1);
                            }
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
                            if(S.find(tmp_s) != S.end()){
                                fprintf(stderr, "syntax error\n");
                                if(verbose == true){
                                    fprintf(stderr, "Repeat in S\n");
                                }
                                exit(1);
                            }
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
                            if(G.find(tmp_g) != G.end()){
                                fprintf(stderr, "syntax error\n");
                                if(verbose == true){
                                    fprintf(stderr, "Repeat in G\n");
                                }
                                exit(1);
                            }
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
                            if(F.find(tmp_f) != F.end()){
                                fprintf(stderr, "syntax error\n");
                                if(verbose == true){
                                    fprintf(stderr, "Repeat in F\n");
                                }
                                exit(1);
                            }
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
                if(D.find(d) != D.end()){
                    fprintf(stderr, "syntax error\n");
                    if(verbose == true){
                        fprintf(stderr, "Repeat in D\n");
                    }
                    exit(1);
                }
                D.insert(d);
            }

        }
        infile.close();
    }
    void CheckParser(){
        // PrintParser();
        if(!CheckinQ(q0)){
            fprintf(stderr, "syntax error\n");
            if(verbose == true){
                fprintf(stderr, "q0 not in Q\n");
            }
            exit(1);
        }

        if(!CheckinG(B)){
            fprintf(stderr, "syntax error\n");
            if(verbose == true){
                fprintf(stderr, "B not in G\n");
            }
            exit(1);
        }
        set<string>::iterator iter1 = F.begin();
        while (iter1!=F.end()){
            if(!CheckinQ(*iter1)){
                fprintf(stderr, "syntax error\n");
                if(verbose == true){
                    fprintf(stderr, "some of F not in Q\n");
                }
                exit(1);
            }
            iter1++;
        }
        
        set<Delta>::iterator iter2 = D.begin();
        while (iter2!=D.end()){
            if(!CheckinQ((*iter2).old_states) || !CheckinQ((*iter2).new_states)){
                // cout<<(*iter2).old_states<<endl;
                // cout<<!CheckinQ((*iter2).old_states)<<endl;
                // cout<<(*iter2).new_states<<";"<<endl;
                // cout<<!CheckinQ((*iter2).new_states)<<endl;
                fprintf(stderr, "syntax error\n");
                if(verbose == true){
                    fprintf(stderr, "some of Delta states not in Q\n");
                }
                exit(1);
            }
            if((*iter2).old_signs.length()!=N){
                fprintf(stderr, "syntax error\n");
                if(verbose == true){
                    fprintf(stderr, "some of Delta old_signs length is not N\n");
                }
                exit(1);
            }
            for (int i = 0; i < (*iter2).old_signs.length();i++){
                if(!CheckinG((*iter2).old_signs[i])){
                    fprintf(stderr, "syntax error\n");
                    if(verbose == true){
                        fprintf(stderr, "some of Delta old_signs not in Q\n");
                    }   
                    // cout<<(*iter2).old_signs[i]<<endl;
                    exit(1);
                }
            }
            if((*iter2).new_signs.length()!=N){
                fprintf(stderr, "syntax error\n");
                if(verbose == true){
                    fprintf(stderr, "some of Delta new_signs length is not N\n");
                }
                exit(1);
            }
            for (int i = 0; i < (*iter2).new_signs.length();i++){
                if(!CheckinG((*iter2).new_signs[i])){
                    fprintf(stderr, "syntax error\n");
                    if(verbose == true){
                        fprintf(stderr, "some of Delta new_signs not in Q\n");
                    } 
                    exit(1);
                }
            }
            if((*iter2).directions.length()!=N){
                fprintf(stderr, "syntax error\n");
                if(verbose == true){
                    fprintf(stderr, "some of Delta directions length is not N\n");
                }
                exit(1);
            }
            for (int i = 0; i < (*iter2).directions.length();i++){
                if((*iter2).directions[i]!='l' && (*iter2).directions[i]!='r' && (*iter2).directions[i]!='*'){
                    fprintf(stderr, "syntax error\n");
                    if(verbose == true){
                        fprintf(stderr, "some of Delta directions not in Q\n");
                    } 
                    exit(1);
                }
            }
            iter2++;
        }
        set<char>::iterator iter3 = S.begin();
        while (iter3!=S.end()){
            if(!CheckinG(*iter3)){
                fprintf(stderr, "syntax error\n");
                if(verbose == true){
                    fprintf(stderr, "some of S not in G\n");
                } 
                exit(1);
            }
            iter3++;
        }
    }
    void CheckInput(char *input){
        int pointer = -1;
        for(int i = 0;i < strlen(input); i++){
            if(!CheckinS(input[i])){
                pointer = i;
                break;
            }
        }
        if(verbose == true){
            if(pointer != -1){
                fprintf(stderr, "Input: %s\n", input);
                fprintf(stderr, "==================== ERR ====================\n");
                fprintf(stderr, "error: '%c' was not declared in the set of input symbols\n", input[pointer]);
                fprintf(stderr, "Input: %s\n", input);
                fprintf(stderr, "       ");
                for(int i = 0; i < pointer; i++){
                    fprintf(stderr, " ");
                }
                fprintf(stderr, "^\n");
                fprintf(stderr, "==================== END ====================\n");
                exit(1);
            }
            else{
                cout<<"Input: "<<input<<endl;
                cout<<"==================== RUN ===================="<<endl;
            }
        }
        else{
            if(pointer != -1){
                fprintf(stderr, "illegal input\n");
                exit(1);
            }
        }
    }
    void Input(char *input){
        for(int i = 0; i < N; i++){
            Tape t = Tape(B);
            Tapes.push_back(t);
        }

        for(int i = 0; i < strlen(input); i++){
            Tapes.at(0).tape[i]=input[i];
            Tapes.at(0).Right(i+1);
        }
        State = q0;
        if(verbose == true){
            PrintTapes(0,State);
        }
        int ExitType = Run();
        if(verbose == true){
            printf("Result: ");
            Tapes.at(0).PrintText();
            printf("==================== END ====================\n");
        }
        else{
            Tapes.at(0).PrintText();
        }
    }
};
int main(int argc, char **argv){
    bool help = false;
    bool verbose = false;
    bool toomanypara = false;
    int tmfile = -1;
    int inputstr = -1;
    // if(argc == 1){
    //     fprintf(stderr, "Missing parameters\n");
    //     exit(1);
    // }
    for (int i = 1; i < argc; i++){
        if(strcmp(argv[i],"-h") == 0||strcmp(argv[i],"--help") == 0){
            help = true;
        }
        else if(strcmp(argv[i],"-v") == 0||strcmp(argv[i],"--verbose")==0){
            verbose = true;
        }
        else{

            if(tmfile == -1){
                tmfile = i;
            }
            else if(inputstr == -1){
                inputstr = i;
            }
            else{
                toomanypara = true;
            }
        }
    }
    if(help == true){
        cout<<"usage: turing [-v|--verbose] [-h|--help] <tm> <input>"<<endl;
        exit(0);
    }
    if(tmfile == -1){
        fprintf(stderr, "Missing parameters\n");
        exit(1);
    }
    if(toomanypara == true){
        fprintf(stderr, "Too many parameters\n");
        exit(1);
    }
    TuringMachine tm = TuringMachine(argv[tmfile],verbose);
    tm.CheckParser();
    if(inputstr == -1){
        char empty[10] = "";
        tm.CheckInput(empty);
        tm.Input(empty);
    }
    else{
        tm.CheckInput(argv[inputstr]);
        tm.Input(argv[inputstr]);
    }
    
    return 0;
}