#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <fstream>
#include <string>
#include <map>
using namespace std;

const long long INF = 1e18;
struct vert {
	int x;
	int y;
	int i;
};
struct edge {
	int u;
	int v;

	edge(int u, int v) : u(u), v(v) {}
};

int n;
vector < vector < pair < int, int > > > g;
vector < vector < int > > g1;
vector< pair < int, edge > > e;
vector<vert> v;


vector<pair<int, int>> star_e_rec;
vector<pair<int, int>> star_e;
int recL = INF;

set<int> not_connected;
set<int> connected;

vector<int> p;
vector<int> d;

vector<int> triangles(int u, int v) {
	vector<int> res;
	for (int j = 0; j < n; ++j) {
		if (g1[j][u] && g1[j][v]) {
			res.push_back(j);
		}
	}
	return res;
}

vector<pair<int, pair<int, int>>> E;
vector<pair<int, int>> resE;
long long res = 0;
long long maxRes = 0;

map<int, int> M;
map<int, int> S;

void solve1() {
	p.resize(n);
	d.resize(n);
	
	for (int i = 0; i < n; ++i)
		p[i] = i, d[i] = 0;
	
	
	vector<int> used(n * n);
	
	for (int i = 0; i < n; ++i) {
		vert vr = v[i];

		for (int j = 0; j < i; ++j) {
			int dist = abs(v[j].x - vr.x) + abs(v[j].y - vr.y);
			g[i].push_back({ j, dist });
			g[j].push_back({ i, dist });
			g1[i][j] = 0;
			g1[j][i] = 0;
			
			E.push_back({ -dist, {i, j} });
		}
	}

	


	while (1) {
		resE.clear();
		//cout << RP(0.5) << endl;
		sort(E.begin(), E.end());

		int k = E.size();
		int step = 0;
		while(!step)
			step = rand() % M[n];
		for (int i = 0; i < k / 2; ++i) {
			int j = rand() % M[n];
			int add = rand() % step;

			swap(E[j], E[(j + add) % k]);
		}

		//cout << E[0].first;

		for (int i = 0; i < n; ++i) {
			used[i] = 0;
			for (int j = 0; j < i; ++j) {
				g1[i][j] = 0;
				g1[j][i] = 0;
			}
		}

		res = 0;
		int cnt = 0;
		int mx = -100000000;
		pair<int, int> del;

		for (int i = 0; i < k; ++i) {
			auto e = E[i];
			int a = e.second.first, b = e.second.second, l = e.first;

			bool f = false;
			auto tr = triangles(a, b);

			if (tr.size() == 0) f = true;
			/*else if (tr.size() == 1) {
				auto tr1 = triangles(a, tr[0]);
				auto tr2 = triangles(b, tr[0]);
				if (tr1.size() == 0 && tr2.size() == 0) f = true;
			}*/

			if (f) {
				if (l > mx) {
					mx = l;
					del = e.second;
				}
				res -= l;
				resE.push_back(e.second);
				g1[a][b] = g1[b][a] = 1;
				used[i] = 1;
				cnt++;
			}
		}
		for (int i = 0; i < k; ++i) {
			if (used[i]) continue;
			auto e = E[i];
			int a = e.second.first, b = e.second.second, l = e.first;

			bool f = false;
			auto tr = triangles(a, b);

			if (tr.size() == 0) f = true;
			else if (tr.size() == 1) {
				auto tr1 = triangles(a, tr[0]);
				auto tr2 = triangles(b, tr[0]);
				if (tr1.size() == 0 && tr2.size() == 0) f = true;
			}

			if (f) {
				if (l > mx) {
					mx = l;
					del = e.second;
				}
				res -= l;
				resE.push_back(e.second);
				g1[a][b] = g1[b][a] = 1;
				used[i] = 1;
				cnt++;
			}
		}

		res += mx;

		//cout << res << " " << cnt << endl;
		if (res > maxRes) {
			cout << res << " " << cnt << endl;
			maxRes = res;

			ofstream myfile("solution" + to_string(n) + ".txt");
			myfile << "c Вес подграфа = " << res << endl;
			myfile << "p edge " << n << " " << resE.size() - 1 << endl;
			for (auto e : resE)
				if (e != del)
					myfile << "e " << v[e.first].i + 1 << " " << v[e.second].i + 1 << endl;
		}
	}
}




void gen() {
	
	freopen("INPUT.TXT", "r", stdin);
	string _; cin >> _; cin >> _;

	cin >> n;
	int x, y;
	srand(time(0));
	g.resize(n, vector < pair < int, int > >());
	g1.resize(n, vector<int>(n));


	for (int i = 0; i < n; ++i) {
		vert vr;
		cin >> vr.x >> vr.y;
		vr.i = i;
		v.push_back(vr);
	}

	//while (1)
		//solve();
	
	solve1();
}


int main(){
	srand(time(0));
	
	M[64] = 2011;
	M[128] = 8111;
	M[512] = 130021;
	M[2048] = 2096123;
	M[4096] = 8325113;


	S[64] = 19;
	S[128] = 811;
	S[512] = 599;
	S[2048] = 20959;
	S[4096] = 83249;

	gen();
}

