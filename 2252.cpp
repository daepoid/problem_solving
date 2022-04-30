#include <bits/stdc++.h>
#define MAX 32011
using namespace std;

int N, M;
vector<int> board[MAX];
int cnt[MAX];
vector<int> answer;

void solutions() {
    queue<int> q;

    for(int i = 1; i <= N; i++) {
        if(cnt[i] == 0) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int num = q.front();
        q.pop();
        answer.push_back(num);

        for(int i = 0; i < board[num].size(); i++) {
            int next_num = board[num][i];
            cnt[next_num]--;
            if(cnt[next_num] == 0) {
                q.push(next_num);
            }
        }        
    }

    for(int i = 0; i < answer.size(); i++) {
        if(i != answer.size() - 1) {
            printf("%d ", answer[i]);
        } else {
            printf("%d\n", answer[i]);
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for(int i = 0; i <M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        board[a].push_back(b);
        cnt[b]++;
    }
    solutions();
}