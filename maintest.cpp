#include <iostream>
#include <cstdlib>
#include "header/dataprocessing.h"
#include "header/nmi.h"
#include <fstream>
using namespace std;

int main(){
  int nodenum = 800;
  int edgenum = 800;
  int setmin = 30;
  int setmax = 50;
  int probability = 10;

  cout << "please input nodenum edgenum setmin setmax and probability:" << endl;
  cin >> nodenum >> edgenum >> setmin >> setmax >> probability;

  const string split = "_";
  const string str = to_string(nodenum) + split + to_string(edgenum) + split + to_string(setmin) +split + to_string(setmax) + split + to_string(probability);
  const string resultpath = "dataset/labeldata/Walktrap_Fakedata_" + str + "_E10000.txt";
  const string tagpath = "dataset/tagdata/Fakedata_tag_" + str + ".txt";

  vector<vector<int>> x = getCommunityResult(resultpath);
	vector<vector<int>> y = getCommunityResult(tagpath);

  double res = calculationNMI(x,y);

  cout<< "NMI index :" << res << endl;

  return 0;
}