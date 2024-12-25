#include <bits/stdc++.h>

using namespace std;

int n, m; // número de vértices, número de arestas
vector<vector<int>> adj; // representação do grafo utilizando lista de adjacência
vector<vector<int>> maximalCliques; // armazena todos os cliques maximais
map<string, int> id;
map<int, string> volta;

int iterationsWithoutPivoting = 0, iterationsWithPivoting = 0; // número de iterações sem e com pivotamento, respectivamente

// calcula o coeficiente de aglomeração do grafo
double clusteringCoefficient() {
    double sum = 0;

    for (int node = 1; node <= n; node++) {
        // calcula o coeficiente de aglomeração do nó atual

        int neighbors = (int)adj[node].size(); // quantidade de vizinhos do nó node
        
        vector<bool> is_neighbor(n+1, false); // indica se o nó i é vizinho de node
        for (auto neighbor : adj[node])
            is_neighbor[neighbor] = true;
        
        int triangles = 0; // quantidade de triangulos (duplicada pois o grafo é não direcionado)
        for (auto neighbor : adj[node]) { // percorre os vizinhos no nó atual
            for (auto edge : adj[neighbor]) { // verifica as arestas desse vizinho
                if (is_neighbor[edge])
                    triangles++;
            }
        }

        triangles /= 2;

        if (neighbors > 1) // evitar divisão por zero
            sum += (2.0*triangles)/(neighbors*(neighbors-1));
    }

    return (1.0/n)*sum;
}

// união de dois conjuntos
vector<int> setUnion(vector<int> a, vector<int> b) {
    vector<int> ans((int)a.size() + (int)b.size()); // inicializa com tamanho igual a soma dos dois conjuntos (pior caso)

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    auto it = set_union(a.begin(), a.end(), b.begin(), b.end(), ans.begin());

    ans.resize(it-ans.begin()); // altera o tamanho para a quantidade de elementos do conjunto

    return ans;
}

// interseção de dois conjuntos
vector<int> setIntersection(vector<int> a, vector<int> b) {
    vector<int> ans((int)a.size() + (int)b.size()); // inicializa com tamanho igual a soma dos dois conjuntos (pior caso)

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    auto it = set_intersection(a.begin(), a.end(), b.begin(), b.end(), ans.begin());

    ans.resize(it-ans.begin()); // altera o tamanho para a quantidade de elementos do conjunto

    return ans;
}

// diferença de dois conjuntos
vector<int> setDifference(vector<int> a, vector<int> b) {
    vector<int> ans((int)a.size()); // inicializa com tamanho igual ao de A

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    auto it = set_difference(a.begin(), a.end(), b.begin(), b.end(), ans.begin());

    ans.resize(it-ans.begin()); // altera o tamanho para a quantidade de elementos do conjunto

    return ans;
}

// algoritmo de Born-Kerbosch sem pivotamento
void BornKerbosch(vector<int> r, vector<int> p, vector<int> x) {
    if (p.empty() && x.empty()) // é um clique maximal
        maximalCliques.push_back(r); // adiciona o conjunto à resposta
    
    auto vertex = p.begin();
    while (vertex != p.end()) { // percorre o conjunto P
        BornKerbosch(setUnion(r, {*vertex}), setIntersection(p, adj[*vertex]), setIntersection(x, adj[*vertex]));
        
        x.push_back(*vertex);
        vertex = p.erase(vertex);
    }

    iterationsWithoutPivoting++;
}

// algoritmo de Born-Kerbosch com pivotamento
void BornKerboschWithPivoting(vector<int> r, vector<int> p, vector<int> x) {
    if (p.empty() && x.empty()) // é um clique maximal
        maximalCliques.push_back(r); // adiciona o conjunto à resposta
    
    int pivot = 0; // escolhe um pivô com o maior grau em P união X
    for (auto vertex : p) {
        if ((int)adj[vertex].size() >= (int)adj[pivot].size())
            pivot = vertex;
    }
    for (auto vertex : x) {
        if ((int)adj[vertex].size() >= (int)adj[pivot].size())
            pivot = vertex;
    }
    
    vector<int> newP = setDifference(p, adj[pivot]); // P \ N(pivot)

    for (auto vertex : newP) { // percorre o conjunto P \ N(pivot)
        BornKerboschWithPivoting(setUnion(r, {vertex}), setIntersection(p, adj[vertex]), setIntersection(x, adj[vertex]));
        
        x.push_back(vertex);
        p.erase(find(p.begin(), p.end(), vertex));
    }

    iterationsWithPivoting++;
}

// imprime os cliques maximais
void printMaximalCliques() {
    cout << " (" <<  (int)maximalCliques.size() << " cliques maximais):\n";
    for (auto maximalClique : maximalCliques) {
        cout << "Tamanho " << (int)maximalClique.size() << ": ";
        for (auto vertex : maximalClique)
            cout << vertex << ' ';
        cout << '\n';
    }
}

int main() {
    // freopen("soc-dolphins.mtx", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int it = 1;

    auto get_id = [&](string s) -> int {
        if (id.find(s) == id.end()) {
            id[s] = it;
            volta[it] = s;
            it++;
        }

        return id[s];
    };

    n = 540;
    m = 3380;
    adj.resize(n + 7); // ajusta tamanho da lista de adjacência que representa o grafo
    for (int i = 0; i < m; i++) {
        string u, v; cin >> u >> v;

        adj[get_id(u)].push_back(get_id(v));
        adj[get_id(v)].push_back(get_id(u));
    }
    
    vector<int> r, p, x;
    for (int i = 1; i <= n; i++) p.push_back(i); // começa com elementos de 1 até n
    
    BornKerbosch(r, p, x);
    cout << "\nBorn-Kerbosch sem pivotamento\n";
    //printMaximalCliques();

    for (auto maximalClique : maximalCliques) {
        if ((int)maximalClique.size() >= 13) {
            vector<string> aux;

            for (auto vertex : maximalClique) {
                aux.push_back(volta[vertex]);
            }

            sort(aux.begin(), aux.end());

            cout << aux[0];

            for (auto e : aux) {
                cout << "," << e;
            }
            cout << '\n';
        }
    }
    
    maximalCliques.clear(); // limpa as respostas anteriores

    
    BornKerboschWithPivoting(r, p, x);
    cout << "\nBorn-Kerbosch com pivotamento";
    printMaximalCliques();

    cout << "\nCoeficiente de aglomeração: " << fixed << setprecision(8) << clusteringCoefficient() << '\n';

    cout << "\nNúmero de iterações sem pivotamento: " << iterationsWithoutPivoting << '\n';
    cout << "Número de iterações com pivotamento: " << iterationsWithPivoting << '\n';

    

    return 0;
}