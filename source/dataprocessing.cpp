#include "../header/dataprocessing.h"
using namespace std;

vector<vector<int>> getCommunityResult(string filename){
  ifstream infile;
  string line;
  const char dilem1 = ' ';
  const char dilem2 = '\t';
  map<int,vector<int>> communities;

  //按行读取TXT文件，并解析
  infile.open(filename, ios::in);
  if(!infile){
    cout<< "read community file error in " << filename <<endl;
    exit(0);
  }

  while(!infile.eof()){
    getline(infile, line);
    int linePos = 0;
    int lineSize = 0;
    string cache;
    vector<int> array;

    for(int i = 0 ; i < line.size(); i++){
      if(line[i] == dilem1 || line[i] == dilem2){
        lineSize = i - linePos;
        cache = line.substr(linePos, lineSize);
        array.push_back(stoi(cache));
        linePos = i+1;
      }
    }
    cache = line.substr(linePos, line.size() - linePos);
    if(cache.size()>0){ array.push_back(stoi(cache)); }

    //记录两人种类型节点数量并将解析的内容写入边对象缓存
    if(array.size() > 1){
      int id = array[0];
      int tag = array[1];
      if(communities.find(tag) == communities.end()){
        vector<int> nodes = {id};
        communities.insert(pair<int,vector<int>> (tag, nodes));
      } else {
        communities[tag].push_back(id);
      }
    }
  }
  infile.close();

  vector<vector<int>> result;
  for(map<int,vector<int>>::iterator iter = communities.begin(); iter!= communities.end(); iter++){
    result.push_back(iter->second);
  }

  return result;
} 
