#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

bool comparison (const pair<int,int>& a, const pair<int,int>& b){
    return a.first > b.first;
}

const int TREE_SIZE = 524288 + 2;
const int LEVELS = 20;
const int MAX = 1e7+2;
const int LEAF_SPACE = 2e5+2;
const int INF = MAX;

int n, m, r, k;
int tree[100];
int leaf[LEAF_SPACE];
map<int,vector<int>> position;
int a[LEAF_SPACE];
int level_size[LEVELS];

int find_lowest_power(int p, int n){
    for(int i=p; i>=1; --i){
        if(level_size[i] < n){
            return i+1;
        }
    }
}

void clear_tree(int start, int last_position){
    if(start >= last_position){
        return;
    }
    clear_tree(2*start, last_position);
    clear_tree(2*start+1, last_position);
    tree[start] = 0;
}

void insert_and_update(int where){
    tree[where] = 1;
    for(int i=1; i<=k; ++i){
        where /= 2;
        tree[where] = tree[where*2] + tree[where*2+1]; 
    }
}

int query(int source, int start_range, int end_range, int l, int r ){
    if(l <= start_range && r >= end_range){
        return tree[source];
    }
    if(r < start_range || end_range < l){
        return 0;
    }
    int mid =(end_range + start_range) /2;
    return query(2*source, start_range, mid, l, r) + query(2*source+1, mid + 1, end_range, l, r);
}

void fill_tree(){
    sort(leaf+1, leaf + m + 1);
    

    for(int i=1; i<=m; ++i){
       position[leaf[i]].push_back(i);
        // cout << a[i] << "    " <<  i << endl;
    }
    int R = find_lowest_power(k, m), x, result = 0;
    
    for(int i=1; i<=m; ++i){
        x = position[a[i]].front();
        if(position[a[i]].size() > 1){
            position[a[i]].erase(position[a[i]].begin());
        }
        
        result += query(1, 1, R, x+1, m);
        cout << " a: " << a[i] <<  " position: " << x + r << " "  << " result ";
        insert_and_update(x+r);
        cout << result << endl;
    }
    for(int i=1; i<=r+m+2; ++i){
        cout << i << ": " << tree[i] << endl;
    }
    clear_tree(1,R-1);

    cout << endl;
}

void solve(){
    level_size[0] = 1;
    for(int i=1; i<20; ++i){
        level_size[i] = level_size[i-1] * 2;
    }
    int tmp;
    cin >> n;
    for(int i=0; i<n; ++i){
        cin >> m;
        k = ceil(log2(m));
        r = level_size[k] - 1;
        for(int j=1; j<=m; ++j){
            cin >> leaf[j];
            a[j] = leaf[j];
        }
        fill_tree();   
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie();
    solve();
    return 0;
}
