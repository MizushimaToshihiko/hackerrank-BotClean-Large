#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template<typename T>
void print_vector(vector<T> &v){
    for(auto const& a:v){
        cout << a << " ";
    }
    cout << "\n";
}
vector<vector<int>> bfs(int height,int width,vector<string>grid,pair<int,int> s){ //no goal
    // distance list
    vector<vector<int>> visited(height);
    for(int i=0;i<height;i++)visited[i]=vector<int>(width,-1);
    // for(int i=0;i<n;i++)print_vector(visited[i]);
    visited[s.first][s.second]=0;
    
    const int white=-1;
    const int gray=0;
    const int black=1;
    // visited or not
    vector<vector<int>> color(height);
    for(int i=0;i<height;i++)color[i]=vector<int>(width,white);

    queue<pair<int,int>> Q;
    Q.push(s);

    // move to four directions.
    int dx[]={1, 0, -1, 0}; // {1, 0, -1, 0, 1, -1, 1, -1}
    int dy[]={0, 1, 0, -1}; // [0, 1,  0, -1, 1, -1, -1,  1]

    while(!Q.empty()){
        auto u=Q.front();Q.pop();
        for(int i=0;i<4;i++){
            if(u.first+dx[i]>=0 && u.first+dx[i]<height 
                && u.second+dy[i]>=0 && u.second+dy[i]<width
                && color[u.first+dx[i]][u.second+dy[i]]==white){
                color[u.first+dx[i]][u.second+dy[i]]=gray;
                visited[u.first+dx[i]][u.second+dy[i]]=visited[u.first][u.second]+1;
                // cout << visited[u.first+dx[i]][u.second+dy[i]] << endl;
                Q.push(make_pair(u.first+dx[i],u.second+dy[i]));
            }
        }
        color[u.first][u.second]=black;
    }
    // for(int i=0;i<n;i++)print_vector(visited[i]);
    return visited;
    // cout << visited[t.first][t.second] << "\n";
}

void next_move(int posr, int posc, int dimh, int dimw, vector <string> board) {
    // add logic here
    // for(int i=0;i<5;i++)cout << board[i] << endl;
    vector<vector<int>> d=bfs(dimh,dimw,board,make_pair(posr,posc));
    // cout << "distance:\n";
    // for(int i=0;i<5;i++)print_vector(d[i]);
    int min_=1000;
    pair<int,int> min_pos;
    for(int i=0;i<dimh;i++){
        for(int j=0;j<dimw;j++){
            if(board[i][j]=='d'){
                if(min_>d[i][j]){
                    min_pos=make_pair(i,j);
                    min_=d[i][j];
                }
            }
        }
    }
    // cout << "i:" << min_pos.first << " j:" << min_pos.second << "\n";
    if(min_pos.second<posc)cout << "LEFT\n";
    else if(min_pos.second>posc)cout << "RIGHT\n";
    else if(min_pos.first<posr)cout << "UP\n";
    else if(min_pos.first>posr)cout << "DOWN\n";
    else cout << "CLEAN\n";
}

int main(void) {
    int pos[2];
    int dim[2];
    vector <string> board;
    cin>>pos[0]>>pos[1];
    cin>>dim[0]>>dim[1];
    for(int i=0;i<dim[0];i++) {
        string s;cin >> s;
        board.push_back(s);
    }
    next_move(pos[0], pos[1], dim[0], dim[1], board);
    return 0;
}
