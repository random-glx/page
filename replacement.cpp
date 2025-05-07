#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

void fifo(vector<int>& seq, int n, int s) {
    queue<int> q;
    int fault = 0;
    vector<int> map(n, 0); 

    for (int i = 0; i < seq.size(); i++) {
        if (map[seq[i]] != 0) {
            continue;
        }

        fault++;

        if (q.size() == s) {
            int x = q.front();
            q.pop();
            map[x]--;
        }

        q.push(seq[i]);
        map[seq[i]]++;
    }

    cout<<"Total page faults: "<<fault<<endl;
}

void lru(vector<int>& seq, int n, int s){
    vector<int> map(n, 0);
    vector<int> index(n, -1);
    int size = 0;
    int fault = 0;
    for(int i = 0; i<seq.size(); i++){
        if(map[seq[i]]!=0) {
            index[seq[i]] = i;
            continue;
        }

        fault++;

        if(size<s){
            map[seq[i]]++;
            index[seq[i]] = i;
            size++;
        }else{
            int lr = -1; int min_idx = INT_MAX; 
            for(int j = 0; j<index.size(); j++){
                if(map[j]>0 && index[j]<min_idx){
                    lr = j;
                    min_idx = index[j];
                }
            }

            index[lr] = -1;
            map[lr]--;
            map[seq[i]]++;
            index[seq[i]] = i;
        }
    }

    cout<<"Total faults "<<fault<<endl;
}

int find(int x, vector<int>& seq, int idx){
    for(int i = idx; i<seq.size(); i++){
        if(seq[i]==x){
            return i;
        }
    }

    return seq.size();
}

int optimalHelper(vector<int>& seq, vector<int>& map, int idx){
    int min_idx = INT_MIN;
    int proc = -1;
    for(int i = 0; i<map.size(); i++){
        if(map[i]!=0 && i!=seq[idx]){
            int j = find(i, seq, idx);
            if(j==seq.size()){
                return i;
            }

            if(j>min_idx){
                proc = i;
                min_idx = j;
            }
        }
    }

    return proc;
}

void optimal(vector<int>& seq, int n, int s){
    int size = 0, fault = 0;
    vector<int> map(n, 0);

    for(int i = 0; i<seq.size(); i++){
        if(map[seq[i]]!=0){
            continue;
        }

        fault++;
        if(size<s){
            map[seq[i]]++;
            size++;
        }else{
            int pageToRemove = optimalHelper(seq, map, i);

            map[pageToRemove]--;
            map[seq[i]]++;
        }
    }

    cout<<"Total faults "<<fault<<endl; 
}

int main() {
    int n;
    cout << "Enter the number of unique processes: ";
    cin >> n;
    int s;
    cout << "Enter size of the memory: ";
    cin >> s;
    int m;
    cout << "Enter the size of sequence: ";
    cin >> m;
    vector<int> seq(m);
    cout << "Enter the page reference sequence: ";
    for (int i = 0; i < m; i++) {
        cin >> seq[i];
    }

    fifo(seq, n, s);
    lru(seq, n, s);
    optimal(seq, n, s);
    return 0;
}