#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include<queue>

using namespace std;
int main(int arg, char *argv[])
{ 
    
  ActorGraph* graph=new ActorGraph();
  if(arg!=5)
  {
      cout<<"You have entered invalid number of inputs" << endl;
      return 1;
  }

  ifstream inputFile;
  ofstream outputFile;
  char character=*argv[2];
  string file=argv[1];
  if(character!='w')
  {
    if(character!='u')
    {
        cout<<"The input for weighted or unweighted is wrong" << endl;
        return 1;
    }
  }
  //cout<<"jgdjlgd"<<endl;
  

  bool a=graph->buildGraphFromFile(argv[1]);
  ifstream infile(argv[3]);
    bool Header = false;
    vector<string> actor1;
    vector<string> actor2;
    //cout << argv[2] << endl;
    while (infile) 
    {
        string str;
        if (!getline(infile, str)) break;

        // skip the header of the file
        if (!Header) {
            Header = true;
            continue;
        }

        // read each line of the dataset to get the movie actor relation
        istringstream ss(str);
        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        // if format is wrong, skip current line
        if (record.size() != 2) {
            continue;
        }

        // extract the information
        actor1.push_back(record[0]);
        actor2.push_back(record[1]);
    }
    //for(int x=0;x<actor1.size();x++)
    //{
       // cout<<actor1[x]<<endl;
      //  cout << actor2[x]<<endl;
    //}

    infile.close();
    //cout<<"Hello threr"<< endl;
  //  cout<<actor1.size()<<endl;
    /*for(int a=0;a<actor1.size();a++)
    {
        cout<<actor1[a]+" "+actor2[a]<<endl;
    }*/
   //return 0;
   outputFile.open(argv[4]);
   outputFile<<"(actor)--[movie#@year]-->(actor)--..."<<endl;
    vector<string> pathways(actor1.size(),"");
    for(unsigned int index=0;index<actor1.size();index++)
    {
        if(character=='u')
        {
            graph->BFS(actor1[index],actor2[index],pathways[index]);
            cout<<index<<endl;
            outputFile<<pathways[index]<<endl;
        }
        if(character=='w')
        {
           graph->Dijkstra(actor1[index],actor2[index],pathways[index]); 
           cout<<index<<endl;
           outputFile<<pathways[index]<<endl;
        }
    }
    
    outputFile.close();







    //delete graph;
    return 0;
}
