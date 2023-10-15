#include <bits/stdc++.h>

using namespace std;

struct edge{
    int from, to;
    char sym;
};

bool compare(const struct edge& f, const struct edge& s) {
        if (f.sym != s.sym) return (f.sym < s.sym);
        else return (f.to < s.to);
}

bool operator != (const edge& f, const edge& s) {
    return f.from != s.from || f.sym != s.sym || f.to != s.to;
}

void print_edge(edge x){
    printf("%d %c %d\n", x.from, x.sym, x.to);
}

void delete_edges(int n, vector<edge> edges[], int color[]){
    for (int i = 0; i < n; ++i){

        vector <edge> unique_edges;

        sort(edges[i].begin(), edges[i].end(), compare);

        if (!edges[i].empty() && color[edges[i][0].from] != -1 && color[edges[i][0].to] != -1){
            unique_edges.push_back(edges[i][0]);
        }

        for (int j = 1; j < edges[i].size(); ++j){
            if (edges[i][j] != edges[i][j - 1] && color[edges[i][j].from] != -1 && color[edges[i][j].to] != -1)
                unique_edges.push_back(edges[i][j]);
        }

        edges[i] = unique_edges;

    }
}

bool compare_nodes(vector<edge> f, vector<edge> s, int color[]){
    // compare nodes based on outgoing edges
    vector <pair<char, int>> x, y, newx, newy;

    for (int i = 0; i < f.size(); ++i){
        x.push_back({f[i].sym, color[f[i].to]});
    }

    for (int i = 0; i < s.size(); ++i) {
        y.push_back({s[i].sym, color[s[i].to]});
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    if (!x.empty()) newx.push_back(x[0]);
    if (!y.empty()) newy.push_back(y[0]);

    for (int i = 1; i < x.size(); ++i) if (x[i] != x[i - 1]) newx.push_back(x[i]);
    for (int i = 1; i < y.size(); ++i) if (y[i] != y[i - 1]) newy.push_back(y[i]);

    if (newx.size() != newy.size()) return false;

    for (int i = 0; i < newx.size(); ++i) if (newx[i] != newy[i]) return false;

    return true;
}

void dfs(int x, int prev, vector<edge> v[], bool used[]){
    cout << x << ' ' << prev << '\n';
    used[x] = 1;

    for (int i = 0; i < v[x].size(); ++i){
        int to = v[x][i].to;
        if (!used[to]) dfs(to, x, v, used);
    }

    return;
}

int main()
{
    FILE *file = fopen("in.txt", "r");

    if (file == NULL) {
        printf("Failed to open the file.");
        return -1;
    }

    int An, Sn, s0, Fn;
    fscanf(file, "%d\n%d\n%d\n", &An, &Sn, &s0);

    bool finalstates[Sn] = {};

    bool used[Sn] = {};

    vector <edge> edges[Sn];
    vector <int> groups[Sn];

    int color[Sn] = {};

    fscanf(file, "%d", &Fn);
    for (int i = 0; i < Fn; ++i){
        int f;
        fscanf(file, "%d", &f);
        color[f] = 1;
        finalstates[f] = 1;
    }
    edge temp;
    while (fscanf(file, "%d %c %d", &temp.from, &temp.sym, &temp.to) != EOF){
        edges[temp.from].push_back(temp);
    }
    dfs(s0, -1, edges, used); // find reachable nodes from start state
    for (int i = 0; i < Sn; ++i){
        int c = color[i];
        if (!used[i]) color[i] = -1; // unreachable nodes have color equal to -1
        else groups[c].push_back(i); // sets of nodes based on their color
    }

    int cntg = 2, prevcntg = -1;

    delete_edges(Sn, edges, color); // delete multiple edges and edges from unreachable nodes

    while (true){

    prevcntg = cntg;
    int new_color = -1;
    for (int c = 0; c < cntg; ++c){
        for (int i = 0; i < groups[c].size(); ++i){
            for (int j = i + 1; j < groups[c].size(); ++j){

                if (!compare_nodes(edges[groups[c][i]], edges[groups[c][j]], color)){
                    new_color = j; cntg++; // create new set of nodes for minimization
                    break;
                }

            }

            if (new_color == -1) continue;

            vector <int> old_group, new_group;

            for (int k = 0; k < groups[c].size(); ++k){

                if (compare_nodes(edges[groups[c][new_color]], edges[groups[c][k]], color)){
                    new_group.push_back(groups[c][k]);
                } // divide of a set that does not fit the minimization condition

                else {
                    old_group.push_back(groups[c][k]);
                }

            }

            for (int k = 0; k < new_group.size(); ++k){
                color[new_group[k]] = cntg - 1; // repaint nodes from new set
            }

            groups[c] = old_group;
            groups[cntg] = new_group;

            if (prevcntg != cntg) break;
        }

        if (prevcntg != cntg) break;

    }

    if (cntg == prevcntg) break;

    }
    printf("After minimization:\n");
    printf("%d\n", cntg);
    vector <int> new_final;
    for (int i = 0; i < Sn; ++i) printf("%d ", i);
    printf("\n");
    for (int i = 0; i < Sn; ++i){
        if (finalstates[i]){
            new_final.push_back(color[i]); // build final states for minimization
        }
        printf("%d ", color[i]);
    }
    printf("\n");
    sort(new_final.begin(), new_final.end());
    printf("%d ", new_final[0]);
    for (int i = 1; i < new_final.size(); ++i){
        if (new_final[i] != new_final[i - 1]) printf("%d ", new_final[i]);
    }
    printf("\n");
    for (int i = 0; i < Sn; ++i){
        for (int j = 0; j < edges[i].size(); ++j){
            edges[i][j].from = color[edges[i][j].from]; // update edges after minimization
            edges[i][j].to = color[edges[i][j].to];
        }
    }
    vector <edge> new_edges[cntg];
    for (int i = 0; i < Sn; ++i){
        for (int j = 0; j < edges[i].size(); ++j){
           new_edges[edges[i][j].from].push_back(edges[i][j]);
        }
    }
    for (int i = 0; i < cntg; ++i) color[i] = i;
    delete_edges(cntg, new_edges, color); // delete multiple edges
    for (int i = 0; i < cntg; ++i){
        for (int j = 0; j < new_edges[i].size(); ++j){
            print_edge(new_edges[i][j]);
        }
    }
    fclose(file);
    return 0;
}
