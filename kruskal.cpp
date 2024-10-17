#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<pair<int, vector<int>>> gr_struct(vector<vector<int>> &arr, const size_t &size){
  vector<pair<int, vector<int>>> weigths(size + 50);
  int c = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (arr[i][j] != 0) {
        weigths[c].first = arr[i][j];
        weigths[c].second.push_back(i);
        weigths[c].second.push_back(j);
        arr[i][j] = 0;
        arr[j][i] = 0;
        c++;
      }
    }
  }
  for (int i = 0; i < weigths.size(); i++) {
    if (weigths[i].first == 0) {
      weigths.erase(weigths.begin() + i);
      i -= 1;
    }
  }
  for (int i = 0; i < weigths.size(); i++) {
    for (int j = 0; j < weigths.size(); j++) {
      if (weigths[i].second.at(0) == weigths[j].second.at(1) &&
          weigths[i].second.at(1) == weigths[j].second.at(0)) {
        weigths.erase(weigths.begin() + j);
      }
    }
  }
  for (int i = 0; i < weigths.size(); i++) {
    for (int j = 0; j < weigths.size(); j++) {
      if (weigths[i].first < weigths[j].first) {
        weigths[i].swap(weigths[j]);
      }
    }
  }
  return weigths;
}

void kruskall(vector<pair<int, vector<int>>>&& weigths, const size_t& size) {
  cout << "\nАлгоритм Краскала выполняется...\nМинимальное остовное дерево:\n";
  set<int> s;
  s.emplace(weigths[0].second[0]); s.emplace(weigths[0].second[1]);
  int sum(0);
  sum += weigths[0].first;
  int i = 0;
  bool visited[size];
  visited[weigths[0].second[0]] = true; visited[weigths[0].second[1]] = true;
  cout << "V" << weigths[i].second[0]+1 << " - V" << weigths[i].second[1]+1 << " : вес " <<
      weigths[i].first << '\n';
  while(s.size() < size){
    if ((s.find(weigths[i].second[0]) != s.end()) && !visited[weigths[i].second[1]]){
      s.emplace(weigths[i].second[1]);
      visited[weigths[i].second[1]] = true;
      cout << "V" << weigths[i].second[0]+1 << " - V" << weigths[i].second[1]+1 << " : вес " <<
      weigths[i].first << '\n';
      sum += weigths[i].first;
      i = 0;
    } else if ((s.find(weigths[i].second[1]) != s.end()) && !visited[weigths[i].second[0]]){
      s.emplace(weigths[i].second[0]);
      visited[weigths[i].second[0]] = true;
      cout << "V" << weigths[i].second[1]+1 << " - V" << weigths[i].second[0]+1 << " : вес " <<
      weigths[i].first <<'\n';
      sum += weigths[i].first;
      i = 0;
    } else {
      i++;
    }
  }
  cout << "\nСумма дерева: " << sum << "\n";
};

int main() {
  const size_t size = 7;
  vector<vector<int>> graph{
         {0, 4, 12, 0, 0, 16, 5},
         {4, 0, 2, 0, 0, 0, 1},
         {12, 2, 0, 10, 4, 1, 2},
         {0, 0, 10, 0, 9, 7, 5},
         {0, 0, 4, 9, 0, 10, 3},
         {16, 0, 1, 7, 10, 0, 12},
         {5, 1, 2, 5, 3, 12, 0}};
  cout << "Матрица смежности графа:\n";
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      cout << graph[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "\n";
  kruskall(gr_struct(graph, size), size);
}
