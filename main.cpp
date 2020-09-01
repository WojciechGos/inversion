#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>

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
int tree[TREE_SIZE];
int leaf[LEAF_SPACE];
map<int,vector<int>> position;
int a[LEAF_SPACE];
int level_size[LEVELS];

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

int query(int where, int start, int end, int x, int y){
    if(x <= start && y >= end){
        return tree[where];
    }
    int mid = (start + end)/ 2, result = 0;

    if(x <= mid) result += query(2*where, start, mid, x, y);
    if(y > mid) result += query(2*where, mid+1, end, x, y);

    return result;
}

void fill_tree(){
    sort(leaf+1, leaf + m + 1);
    

    for(int i=1; i<=m; ++i){
       position[leaf[i]].push_back(i);
        // cout << a[i] << "    " <<  i << endl;
    }
    int R = (r+1) * 2 - 1, x, result = 0;
    
    for(int i=1; i<=m; ++i){
        x = position[a[i]].front();
        if(position[a[i]].size() > 1){
            position[a[i]].erase(position[a[i]].begin());
        }
        
        result += query(1, 1, R, x+r+1, m+r);
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
