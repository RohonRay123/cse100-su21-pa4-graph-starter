/**
 * TODO: add file header
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <vector>
#include<set>
#include<iterator>
#include<tr1/unordered_map>
#include<queue>
using namespace std;

/**
 * TODO: add class header
 */


class node
{
   public: 
   string path;
   string name;
   int distance;
   node* prev;
   vector<node*> neighbors;
   bool isVisited;
   public:
    node(){
      this->name="";
      this->distance=-1;
      this->prev=NULL;
      isVisited=false;
    } 

    node(string name1,int distance, node* prev, bool isVisited,string path)
    {
      this->name=name1;
      this->distance=distance;
      this->prev=prev;
      this->isVisited=isVisited;
      this->path=path;
    }

    void setDistance(int distance2)
    {
       this->distance=distance2;
    }

    bool operator<(node& other)
    {
        if(this->distance != other.distance)
        {
          return this->distance > other.distance;
        }
        int a=this->name.compare(other.name);
        if(a<0)
        {
          return true;
        }
        return false;

    }


};

class edge
{
   public:
   string movietitle;
   int year;
   int weight;

   edge()
   {
     movietitle="";
     year=2050;
     weight=2050;
   }

   edge(string movetitle, int year)
   {
     this->movietitle=movetitle;
     this->year=year;
    // this->weight=1+(2019-year);
    this->weight=1+(2019-year);
    //cout<<"Parameters1"<<endl;
    //cout<<this->movietitle <<endl;
   }

   void setWeight()
   {
     this->weight=1+(2019-year);
   }



};

/*class edgeCompare
{
  bool operator()(edge* a, edge*b)
  {
    return *a<*b;
  }
};*/
class nodeCompare
{
  public:
   bool operator()(node* &a, node* &b) const 
   {
       return *a<*b;
   }
};

class ActorGraph {
  private: 
    int findIndexActor(string name, vector<node*> actorNames);
    vector<edge*> commonMovies(int index1, 
    int index2,vector<string> names, tr1::unordered_map<string,vector<edge*> > map);
    edge* leastWeight(vector<edge*> moviesCommon);
  protected:
    // TODO: add data structures used in actor graph
    vector<node*>actorNames;
    vector<string>actorNamesString;
 //   vector<vector<edge*> > record1;
//    vector<vector<vector<edge*> > > adjacentMatrix;
  //  vector<vector<edge*> > adjacentMatrix1;
    vector<string> readActor;
    vector<string> readMovie;
    vector<int> readYear;
    set<string> actorRead;
    vector<string> actor1;
    tr1::unordered_map <string, vector<string> > ActorMovie;
    tr1::unordered_map<string,vector<int> > ActorYear;
    tr1::unordered_map<string,vector<edge*> > mapping;//nodetoedge
    //tr1::unordered_map<string,vector<edge*> > totalMapping;
    tr1::unordered_map<node*,vector<edge*> > nodetoedge;
    tr1::unordered_map<edge*,vector<node*> >edgetonode;
    tr1::unordered_map<string,edge*> edgeRecord;
    tr1::unordered_map<string, node*> nodeRecord;
    tr1::unordered_map<string,vector<node*> >nodeRecordvector; //edgetonode
    queue<node*> recordNode;
    vector<node*> node1;
    vector<edge*> edge1;
    //priority_queue<node*,vector<node*>,nodeCompare> nodePrior; 
    vector<string> edgeInfo;
  public:
  
    /* TODO */
    ActorGraph();

    /* TODO */
    bool buildGraphFromFile(const char* filename);

    /* TODO */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

   /* TODO */
    void Dijkstra(const string& fromActor, const string& toActor,
                  string& shortestPath);

    /* TODO */
    ~ActorGraph();
};
#endif  // ACTORGRAPH_HP





