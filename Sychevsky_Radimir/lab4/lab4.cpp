#include <iostream>
#include <vector>

using namespace std;

vector<int> prefix_function (string s, vector<int> &pi) {
	for (int i=1; i<s.length(); ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
		pi.push_back(0);
	}
	return pi;
}

int find_shift(string s, string f){
	int flag = 0;
	for(int i = 0; i < s.length(); i++){
		flag = 1;
		if (s[0] == f[i]){
            for(int j = 0; j < s.length(); j++)
            {
                if (s[j] != f[(i + j) % s.length()])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
                return i;
        }
	}
	return -1;
}

int main(){
	string f;
	cin >> f;
	int size = f.length();	
	string s;
	cin >> s;
    cout << "Выберите задание:" << endl;
    cout << "1 - поиск подстрки в стрке" << endl;
    cout << "2 - поиск сдвига" << endl;
    int task;
    cin >> task;
    vector<int> pi;
    switch(task){
        case 1:{
            f = f + "&";
	        f = f + s;
	        pi.push_back(0);
	        pi.push_back(0);
	        pi = prefix_function(f, pi);
            int flag = 0;
            for(int i = 0; i < f.length(); i++){
		        if(pi[i] == size){
			        if(!flag){
				        cout << i-(2*size);
				        flag++;
			        }else
				        cout << "," << i-(2*size);
        	    }
	        }
            cout << endl;
	        if(!flag)
                cout << -1 << endl;
            break;
        }
        case 2:{
            if(f.length() != s.length()){
		        cout << -1 << endl;
                return 0;
            }
            cout << find_shift(s, f) << endl;
            break;
        }
    }
	

    return 0;
}