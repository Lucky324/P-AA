#include <iostream>

using namespace std;

int check_sq(int size, int* arr, int place, int tmp_size, int tmp_count){
    if(((place+1)%size + tmp_size) > size)
        return 0;
    if((place/size+1 + tmp_size) > size)
        return 0;
    for(int i = 0; i <= tmp_size; i++)
        for(int j = 0; j <= tmp_size; j++)
            if(*(arr+place+i*size+j) != 0)
                return 0;
    for(int i = 0; i <= tmp_size; i++)
        for(int j = 0; j <= tmp_size; j++)
            *(arr+place+i*size+j) = tmp_count; 
    return 1;
}

void full_ans(int size, int* arr, int* ans, int* score, int coef){
    int flag = 0;
    int N = 0;
    int k;
    int i = 1;
    while(i <= *(score)){
        for(k = 0; k < size*size; k++){
            if(*(arr+k) == i){
                if(!flag)
                    flag = 1;
                N++;
            }else if(flag)
                    break;
        }
        *(ans+(i-1)*3) = (k-N)/size*coef+1;
        *(ans+(i-1)*3+1) = (k-N)%size*coef+1;
        *(ans+(i-1)*3+2) = N*coef;
        flag = 0;
        N = 0;
        i++;
    }

}

int find_ans(int size, int* arr, int count, int* ans, int* score, int coef){
    int tmp_arr[size][size];
    for(int j = 0; j < size; j++)
        for(int k = 0; k < size; k++)
            tmp_arr[j][k] = *(arr+j*size+k);
    int size_for_adding = size/2;
    int tmp_count = 0;
    int end_flag = 0;
    int flag = 0;
    int place = 0;
    while(*(arr+place)){
        if(place >= size*size-1){
            end_flag = 1;
            break;
        }
        place++;
    }
    if(!end_flag)
        for(int i = size/2; i > -1; i--){
            for(int j = 0; j < size; j++)
                for(int k = 0; k < size; k++)
                    tmp_arr[j][k] = *(arr+j*size+k);
            if(check_sq(size, &tmp_arr[0][0], place, i, count) == 0){
            } else 
                if(count < *(score))
                    flag = find_ans(size, &tmp_arr[0][0], count+1, ans, score, coef);
                else{
                    return -1;
                }
                
        } 
    
    if(end_flag){
        *(score) = count-1;
        full_ans(size, &tmp_arr[0][0], ans, score, coef);
    }
    return 0;
}

int start(int size, int* arr, int tmp, int count, int* ans, int* score, int coef){
    count++;
    for(int j = 0; j < tmp; j++)
        for(int k = 0; k < tmp; k++)
            *(arr+size*j+k) = count;
    count++;
    for(int j = 0; j < (size-tmp); j++)
        for(int k = tmp; k < size; k++)
            *(arr+size*j+k) = count;
    count++;
    for(int j = tmp; j < size; j++)
        for(int k = 0; k < (size-tmp); k++)
            *(arr+size*j+k) = count;

    int new_arr[size][size];
    for(int j = 0; j < size; j++)
        for(int k = 0; k < size; k++)
            new_arr[j][k] = *(arr+j*size+k);
    
    int tmp_arr[size][size];
    for(int j = 0; j < size; j++)
        for(int k = 0; k < size; k++)
            tmp_arr[j][k] = *(arr+j*size+k);
    count++;
    int max = size*size;
    int new_max = max;

    for(int f = (size-tmp); f > 0; f--){
        if(f > 8)
            continue;
        for(int j = 0; j < size; j++)
            for(int k = 0; k < size; k++)
                new_arr[j][k] = *(arr+j*size+k);

        for(int j = size-f; j < size; j++)
            for(int k = size-f; k < size; k++)
                new_arr[j][k] = count;

        new_max = find_ans(size, &new_arr[0][0], count+1, ans, score, coef);
        if(new_max < max){
            max = new_max;
            for(int j = 0; j < size; j++)
                for(int k = 0; k < size; k++)
                    tmp_arr[j][k] = new_arr[j][k];
        }
    }
    for(int j = 0; j < size; j++)
        for(int k = 0; k < size; k++)
            *(arr+j*size+k) = tmp_arr[j][k];
    return max;
}

int main(){
    int size = 0;
    cin >> size;
    int coef = 1;
    if(size%2 == 0){
        coef = size/2;
        size = size/coef;
    }else if(size%3 == 0){
        coef = size/3;
        size = size/coef;
    }else if(size%5 == 0){
        coef = size/5;
        size = size/coef;
    }
    int ans[22][3];
    int score = 25;
    int arr[size][size];
    int new_arr[size][size];
    if(size == 2){
        cout << 4 << endl;
        cout << "1 1 " << coef << endl;
        cout << "1 " << coef+1 << " " << coef << endl;
        cout << coef+1 << " 1 " << coef << endl;
        cout << coef+1 << " " << coef+1 << " " << coef << endl;
        return 0; 
    }
    for(int i = size/2+1; i <= 15; i++){
        for(int j = 0; j < size; j++)
            for(int k = 0; k < size; k++)
                arr[j][k] = 0;
        start(size, &arr[0][0], i, 0, &ans[0][0], &score, coef);
    }
    cout << score << endl;
    for(int i = 0; i < score; i++){
        cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << endl;
    }
}