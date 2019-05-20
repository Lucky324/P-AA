#include <iostream>
#include <cmath>

using namespace std;
#define ARR_SIZE 27

class vertex{
    public:
        int length;
        char last;
        int painted;
    vertex(){
        length = -1;
        painted = 0;
        last = '0';
    }

};

template <typename T>
void full_elem( T* a, T b)
{
    *(a) = b;
    return;
}

int evr_f(char a, char b){
    return abs(a-b);
}

int main(){
    vertex arr[ARR_SIZE][ARR_SIZE];
    for(int i = 0; i < ARR_SIZE; i++)
        for(int j = 0; j < ARR_SIZE; j++){
            if(i == j)
                arr[i][j].length = 0;
            arr[i][j].last = '0';
        }
    vertex start;
    cin >> start.last;
    vertex end;
    cin >> end.last;
    char tmp1;
    char tmp2;
    int tmp_length = 0;
    double tmp_buf = 0;
    cin >> tmp1;
    cin >> tmp2;
    cin >> tmp_buf;
    tmp_length = tmp_buf;
    full_elem(&arr[1][0].last, tmp1);
    full_elem(&arr[1][0].length, 0);
    full_elem(&arr[0][1].last, tmp1);
    full_elem(&arr[0][1].length, 0);
    full_elem(&arr[2][0].last, tmp2);
    full_elem(&arr[2][0].length, 0);
    full_elem(&arr[0][2].last, tmp2);
    full_elem(&arr[0][2].length, 0);
    full_elem(&arr[1][2].length, tmp_length);
    int i = 1;
    int j = 1;
    int count = 1;
    while(cin >> tmp1){
        cin >> tmp2;
        cin >> tmp_buf;
        tmp_length = tmp_buf;
        count++;
        for(i; arr[i][0].last != tmp1; i++){
            if(arr[i][0].length == -1){
                arr[i][0].last = tmp1;
                arr[i][0].length = 0;
                arr[0][i].last = tmp1;
                arr[0][i].length = 0;
                break;
            }
        }
        for(j; arr[0][j].last != tmp2; j++){
            if(arr[0][j].length == -1){
                arr[0][j].last = tmp2;
                arr[0][j].length = 0;
                arr[j][0].last = tmp2;
                arr[j][0].length = 0;
                break;
            }
        }
        arr[i][j].length = tmp_length;
        i = 1;
        j = 1;
    }
    for(i = 1; arr[i][0].length != -1; i++)
        if(arr[i][0].last == start.last){
            start.length = i;
            arr[i][0].painted = 1;
            arr[0][i].painted = 1;
        }
    for(i = 1; arr[i][0].length != -1; i++)
        if(arr[i][0].last == end.last){
            end.length = i;
        }
    if(start.last == end.last){
        cout << start.last;
        return 0;
    }
    int min = 0;
    vertex tmp_ver;
    vertex need_to_add;
    int add_min = 0;
    for(i = 1; i <= count; i++){
        if(arr[start.length][i].length > 0)
            arr[i][i].length = start.length;
    }
    // for(int i = 0; i <=  count; i++){
    //     for(int j = 0; j <= count; j++){
    //         if(i == 0 || j == 0)
    //             cout << " (" << arr[i][j].last << "):" << arr[i][j].painted << " ";
    //         else{
    //             if(arr[i][j].length == -1)
    //                 cout << "  f    ";
    //             else
    //                 if(arr[i][j].length < 10)
    //                     cout << " (" << arr[i][j].length << ")   ";
    //                 else{
    //                     cout << "(" << arr[i][j].length << ")   ";
    //                 }
    //         }
    //     }
    //     cout << endl;
    // }
    //while(arr[start.length][end.length].length < 1){
    while(arr[end.length][0].painted != 1){
        for(i = 1; i <= count; i++){
            if(arr[i][0].painted == 1)
                continue;
            if(arr[start.length][i].length < 1)
                continue;
            if(!min && arr[start.length][i].length > 0){
                min = arr[start.length][i].length;
                tmp_ver.painted = i;
                tmp_ver.length = evr_f(end.last, arr[i][0].last);
                tmp_ver.last = arr[i][0].last;
                continue;
            }
            if(min && arr[start.length][i].length > 0){
                if((min + tmp_ver.length) >= (arr[start.length][i].length + evr_f(end.last, arr[i][0].last))){
                    if(tmp_ver.last - arr[i][0].last < 0){
                        // add_min = min;
                        // need_to_add.painted = tmp_ver.painted;
                        // need_to_add.length = tmp_ver.length;
                        // need_to_add.last = tmp_ver.last;
                        min = arr[start.length][i].length;
                        tmp_ver.painted = i;
                        tmp_ver.length = evr_f(end.last, arr[i][0].last);
                        tmp_ver.last = arr[i][0].last;
                        continue;
                    }
                }
            }
        }
        for(j = 1; j <= count; j++){
            if(arr[tmp_ver.painted][j].length > -1 && tmp_ver.painted!=j){
                if(arr[start.length][j].length < 0 || arr[start.length][j].length >= (arr[tmp_ver.painted][j].length + min)){
                    arr[start.length][j].length = arr[tmp_ver.painted][j].length + min;
                    arr[j][j].length = tmp_ver.painted;
                }
            }
        }
        arr[tmp_ver.painted][0].painted = 1;
        arr[0][tmp_ver.painted].painted = 1;
        tmp_ver.painted = 0;
        tmp_ver.length = 0;
        min = 0;

        // for(int i = 0; i <=  count; i++){
        //     for(int j = 0; j <= count; j++){
        //         if(i == 0 || j == 0)
        //             cout << " (" << arr[i][j].last << "):" << arr[i][j].painted << " ";
        //         else{
        //             if(arr[i][j].length == -1)
        //                 cout << "  f    ";
        //             else
        //                 if(arr[i][j].length < 10)
        //                     cout << " (" << arr[i][j].length << ")   ";
        //                 else{
        //                     cout << "(" << arr[i][j].length << ")   ";
        //                 }
        //         }
        //     }
        //     cout << endl;
        // }

    }

    char list[count];
    i = 0;
    int tmp_int = end.length;
    char tmp_char = '-';
    while(tmp_char != start.last){
        tmp_char = arr[tmp_int][0].last;
        list[i] = tmp_char;
        tmp_int = arr[tmp_int][tmp_int].length;
        i++;
    }
    i--;
    while(i > -1){
        cout << list[i];
        i--;
    }
    //cout << endl;

    // for(int i = 0; i <=  count; i++){
    //     for(int j = 0; j <= count; j++){
    //         if(i == 0 || j == 0)
    //             cout << " (" << arr[i][j].last << "):" << arr[i][j].painted << " ";
    //         else{
    //             if(arr[i][j].length == -1)
    //                 cout << "  f    ";
    //             else
    //                 if(arr[i][j].length < 10)
    //                     cout << " (" << arr[i][j].length << ")   ";
    //                 else{
    //                     cout << "(" << arr[i][j].length << ")   ";
    //                 }
    //         }
    //     }
    //     cout << endl;
    // }
    return 0;
}