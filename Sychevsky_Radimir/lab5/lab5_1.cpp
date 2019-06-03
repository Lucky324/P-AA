#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
const int k = 60;

struct bohr_vrtx{
    int next_vrtx[k];
    int pat_num;
    int suff_link;
    int auto_move[k];
    int par;
    int suff_flink;
    bool flag;
    char symb;
    int count_arc;
};

class Bohr{
    vector<bohr_vrtx> bohr;
    vector<string> pattern;

    bohr_vrtx make_bohr_vrtx(int p, char c){
        bohr_vrtx v;
        memset(v.next_vrtx, -1, sizeof(v.next_vrtx));
        memset(v.auto_move, -1, sizeof(v.auto_move));
        v.flag = false;
        v.suff_link = -1;
        v.par = p;
        v.symb = c;
        v.suff_flink = -1;
        v.count_arc = 0;
        return v;
    }

    
public:
    Bohr(){
        bohr.push_back(make_bohr_vrtx(0, '$'));
    }

    void add_string_to_bohr(const string &s){
        int num = 0;
        for (int i = 0; i < s.length(); i++){
            int ch = s[i] - 'A';
            if (bohr[num].next_vrtx[ch] == -1){
                bohr[num].count_arc++;
                bohr.push_back(make_bohr_vrtx(num, ch));
                bohr[num].next_vrtx[ch] = bohr.size() - 1;
            }
            num = bohr[num].next_vrtx[ch];
        }
        bohr[num].flag = true;
        pattern.push_back(s);
        bohr[num].pat_num = pattern.size() - 1;
    }
private:

    int get_suff_link(int v){
        if (bohr[v].suff_link == -1)
            if (v == 0 || bohr[v].par == 0)
                bohr[v].suff_link = 0;
            else
                bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
        return bohr[v].suff_link;
    }
    int get_auto_move(int v, char ch){
        if (bohr[v].auto_move[ch] == -1)
            if (bohr[v].next_vrtx[ch] != -1)
                bohr[v].auto_move[ch] = bohr[v].next_vrtx[ch];
            else if (v == 0)
                bohr[v].auto_move[ch] = 0;
            else
                bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
        return bohr[v].auto_move[ch];
    }

    int get_suff_flink(int v){
        if (bohr[v].suff_flink == -1){
            int u = get_suff_link(v);
            if (u == 0)
                bohr[v].suff_flink = 0;
            else
                bohr[v].suff_flink = (bohr[u].flag) ? u : get_suff_flink(u);
        }
        return bohr[v].suff_flink;
    }

    void check(int v, int i){
        for (int u = v; u != 0; u = get_suff_flink(u)){
            if (bohr[u].flag){
                cout << i - pattern[bohr[u].pat_num].length() + 1 << " " << bohr[u].pat_num + 1 << endl;
            }
        }
    }
public:
    void find_all_pos(const string &s){
        int u = 0;
        for (int i = 0; i < s.length(); i++){
            u = get_auto_move(u, s[i] - 'A');
            check(u, i + 1);
        }
    }    
};

int main(){
    string T, pattern;
    int n;
    cin >> T >> n;
    Bohr bohr;
    for (int i = 0; i < n; i++){
        cin >> pattern;
        bohr.add_string_to_bohr(pattern);
    }
    bohr.find_all_pos(T);
}