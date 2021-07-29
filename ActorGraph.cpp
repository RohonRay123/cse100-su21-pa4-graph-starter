

/**
 * TODO: add file header
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include<queue>
#include<set>
//#include<iterator>
//#include<algorithm>
#include<tr1/unordered_map>
#include<algorithm>


using namespace std;

/* TODO */
ActorGraph::ActorGraph() 
{
//   adjacentMatrix1=vector<vector<edge*> >(400000,vector<edge*>(400000,0));
}


/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 */

bool ActorGraph::buildGraphFromFile(const char* filename) {
    
    ifstream infile(filename);

    
    bool readHeader = false;
    int count=0;
    string s;
    getline(infile,s);
    
    while (infile) {
        string s;
      // skip the header of the file
        if (!readHeader) {
            readHeader = true;
            continue;
        }
      
      
      //  cout<<"hehehe"<<endl;
        if (!getline(infile, s)) break;

        

        // read each line of the dataset to get the movie actor relation
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        // if format is wrong, skip current line
        if (record.size() != 3) {
            continue;
        }
       // extract the information
        string actor(record[0]);
        string title(record[1]);
        stringstream number(record[2]);
        int year;
        number >> year;
        readActor.push_back(actor);
        //actorRead.insert(actor);
        readMovie.push_back(title);
        readYear.push_back(year);
        edge* ed=new edge(title,year);
        node* n=new node(actor,-1,NULL,false,"");
        string sk1=record[1]+record[2];
        if(nodeRecord.find(actor)==nodeRecord.end())
        {
            node1.push_back(n);
            vector<string> adderMovie;
            vector<int> adderYear;
            vector<edge*> e;
            e.push_back(ed);
            adderMovie.push_back(title);
            adderYear.push_back(year);
            ActorMovie[actor]=adderMovie;
            ActorYear[actor]=adderYear;
            actor1.push_back(actor);
            mapping[actor]=e;
            if(edgeRecord.find(sk1)==edgeRecord.end())
            {
             edge1.push_back(ed);
              vector<node*>n1;
              n1.push_back(n);
             nodetoedge[n]=e;
              mapping[n->name]=e;
             edgetonode[ed]=n1;
              nodeRecordvector[sk1]=n1;
              edgeRecord[sk1]=ed;
              edgeInfo.push_back(sk1);
           }
           else if(edgeRecord.find(sk1)!=edgeRecord.end())
           {
              edge* ef=edgeRecord[sk1];
              vector<edge*> foundEdge;
              foundEdge.push_back(ef);
              nodetoedge[n]=foundEdge;
              mapping[n->name]=foundEdge;
              vector<node*>n2;
              n2=edgetonode[ef];
              n2.push_back(n);
              edgetonode[ef]=n2;
              nodeRecordvector[sk1]=n2;
              delete ed;
           }
           nodeRecord[actor]=n;
        }
        else if(nodeRecord.find(actor)!=nodeRecord.end())
        {  
             vector<string> Movie;
             vector<int> Year;
             vector<edge*> e4;
             Movie=ActorMovie[actor];
             Year=ActorYear[actor];
             Movie.push_back(title);
             Year.push_back(year);
             ActorMovie[actor]=Movie;
             ActorYear[actor]=Year;
             //delete n->prev;
             delete n; 
             //nodetoedge[n]=e1;
             if(edgeRecord.find(sk1)==edgeRecord.end())
             {
                edge1.push_back(ed);
                e4=mapping[actor];
               //e4=nodetoedge()
              // edge* e3=new edge(title,year);
               e4.push_back(ed);
               mapping[actor]=e4;
               nodetoedge[nodeRecord[actor]]=e4;
               mapping[nodeRecord[actor]->name]=e4;
               vector<node*> noding;
               noding.push_back(nodeRecord[actor]);
               edgetonode[ed]=noding;
               nodeRecordvector[sk1]=noding;
               edgeRecord[sk1]=ed;
               edgeInfo.push_back(sk1);
             }
             else if(edgeRecord.find(sk1)!=edgeRecord.end())
             {
               e4=mapping[actor];
               e4.push_back(edgeRecord[sk1]);
               mapping[actor]=e4;
               nodetoedge[nodeRecord[actor]]=e4;
               mapping[nodeRecord[actor]->name]=e4;
               vector<node*> nodeStuff;
               nodeStuff=edgetonode[edgeRecord[sk1]];
               nodeStuff=nodeRecordvector[sk1];
               nodeStuff.push_back(nodeRecord[actor]);
               edgetonode[edgeRecord[sk1]]=nodeStuff;
               nodeRecordvector[sk1]=nodeStuff;
               delete ed;
             }

             
        }

      //  cout<<count<< " hellow1234 " << endl;
        count++;
        
    }

    if (!infile.eof()) {
       // cout<<count<<endl;
        cerr << "Failed to read " << filename << endl;
        return false;
    }
    infile.close();
    /*vector<edge*> print=nodetoedge[nodeRecord["Will Smith"]];
    //vector<node*> print2=edgetonode[edge1[3]];
    for(int i=0;i<print.size();i++)
    {
        edge* e=print[i];
        cout<<e->movietitle<<endl;
    }*/
    /*for(int i=0;i<print2.size();i++)
    {
        node* np=print2[i];
        cout<<np->name<<endl;
    }*/
    cout<<"Now finished" << endl;
    return true;
}



void ActorGraph::BFS(const string& fromActor, const string& toActor,
             string& shortestPath)
{
     queue<node*> recordNode;
   cout<<"Hello there"<<endl; 
  if(nodeRecord.find(fromActor)==nodeRecord.end() ||
  nodeRecord.find(toActor)==nodeRecord.end())
  {
      cout<<"Still there?" << endl;
      shortestPath="";
      return;
  }
  //cout<<"Hello5"<<endl;
  node* start=nodeRecord[fromActor];
  node* curr=start;
  curr->setDistance(0);
  start->setDistance(0);
  recordNode.push(curr);
  int distance=0;
  int counter=0;
  while(!recordNode.empty())
  {
      //distance++;
      curr=recordNode.front();
      recordNode.pop();
      //cout<<counter<<endl;
      
      if(curr->isVisited==false)
      {
         curr->isVisited=true;
         vector<edge*> edger=nodetoedge[curr]; //come back to that or not 
         //vector<edge*> edger=mapping[curr->name];
        // cout<<curr->name<<endl;
         for(int index=0;index<edger.size();index++)
         {
              edge* rec=edger[index];
             string movie1=rec->movietitle;
             int year1=rec->year;
             stringstream ssYear;
             ssYear << year1;
             string stringYear12=ssYear.str();
             vector<node*>noder;//=edgetonode[rec];
             string info=movie1+stringYear12;
                noder=nodeRecordvector[info];
             for(int index1=0;index1<noder.size();index1++)
             {
                node* a=noder[index1];
                int sameName=a->name.compare(curr->name);
                if(sameName!=0 && a->isVisited==false)
                {
                 //node* a=noder[index1];
                // a->setDistance(distance);
                 string movie=rec->movietitle;
                 int year=rec->year;
                 stringstream ss1;
                 ss1 <<year;
                 string yearString=ss1.str();
                // a->path="["+movie+"#"+"@"+yearString+"]";
                 if(a->prev==NULL)
                 {
                  a->prev=curr;
                  a->setDistance(curr->distance+1);
                  a->path="["+movie+"#"+"@"+yearString+"]";
                  recordNode.push(noder[index1]);
                 }
                 else if(a->prev!=NULL)
                 { 
                     if(a->isVisited==false)
                     {
                         if(curr->distance<a->distance || a->distance==-1)
                         {
                             a->prev=curr;
                             a->setDistance(curr->distance+1);
                             a->path="["+movie+"#"+"@"+yearString+"]";
                             recordNode.push(noder[index1]);
                         }
                     }
                 }
                 
                }
             }

         }
         
      
      }
  }
  cout<<"Traversing Graph Finished" <<endl;
    



  shortestPath="";
  node* end=nodeRecord[toActor];
  //node* start=nodeRecord[fromActor];
  node* traverse=end;
 // node* startNode=start;
 // return;
  vector<string> recordPathway;
 

  while(traverse->name!=fromActor && traverse->prev!=NULL)
  {
   // cout<<"We are in a traverse while loop" << endl;
   //cout<<"Hello454"<<endl;
    if(traverse->prev==start)
    {
        node* a=traverse->prev;
        shortestPath="("+a->name+")"+"--"+traverse->path+"-->" + "(" + traverse->name + ")" + shortestPath;
    } 
    else
    {
        shortestPath="--"+traverse->path+"-->" + "(" + traverse->name + ")"+ shortestPath;
    }
    traverse=traverse->prev;
  //  cout<<traverse->name<<endl;
  }
  //cout<<"Graph REady?"<< endl;
  //cout<<shortestPath<<endl;
  for(unsigned int i=0;i<node1.size();i++)
  {
      node* modify=node1[i];
      modify->prev=NULL;
      modify->distance=-1;
      modify->isVisited=false;
      modify->path="";
  }
  if(traverse->name!=fromActor)
  {
      shortestPath="";
      return;
  }
}
void ActorGraph::Dijkstra(const string& fromActor, const string& toActor,
                  string& shortestPath)
{
  cout<<"Hello there" << endl;
  priority_queue<node*,vector<node*>,nodeCompare> nodePrior;
  if(nodeRecord.find(fromActor)==nodeRecord.end() ||
  nodeRecord.find(toActor)==nodeRecord.end())
  {
      shortestPath="One of the actors doesnt exist\n";
      return;
  }
/*  edge* e5=edgeRecord["Crackheads2013"];
  vector<node*> here=edgetonode[e5];
  for(int i=0;i<here.size();i++)
  {
      cout<<here[i]->name<<endl;
  }
  cout << " "<< endl;
   edge* e6=edgeRecord["The Lunatics' Ball1999"];
   vector<node*> here12=edgetonode[e6];
  for(int i=0;i<here12.size();i++)
  {
      cout<<here12[i]->name<<endl;
  }
  return;*/
  node* start=nodeRecord[fromActor];
  node* curr=start;
  start->setDistance(0);
  start->setDistance(0);
  nodePrior.push(curr);
  int distance=0;
  
  while(!nodePrior.empty())
  {
      //distance++;
      curr=nodePrior.top();
      nodePrior.pop();
      if(curr->isVisited==false)
      {
         curr->isVisited=true;
         vector<edge*> edger=nodetoedge[curr]; //might come back to this 

         //vector<edge*> edger=mapping[curr->name];
         /*for(int a=0;a<edger.size();a++)
         {
            cout<<edger[a]->movietitle<<endl;
            
         }
         return;*/
        //cout<<curr->name<<endl;
         for(int index=0;index<edger.size();index++)
         {
             edge* rec=edger[index];
             string movie1=rec->movietitle;
             int year1=rec->year;
             stringstream ssYear;
             ssYear << year1;
             string stringYear12=ssYear.str();
            // cout<<rec->movietitle<<endl;
             vector<node*>noder;//=edgetonode[rec];//might cme back to this
             string info=movie1+stringYear12;
            // if(rec->movietitle=="Crackheads" && rec->year==2013)
            // {
                noder=nodeRecordvector[info];
            // }
             //cout<<noder.size()<<endl;
             //return;
            // for(int a=0;a<noder.size();a++)
            // {
               //  cout<<noder[a]->name;
            // }
            // return;
             for(int index1=0;index1<noder.size();index1++)
             {
                node* a=noder[index1];
                int sameName=a->name.compare(curr->name);
                if(sameName!=0 && a->isVisited==false && rec->weight>=0)
                {
                 //node* a=noder[index1];
                // a->setDistance(distance);
                 string movie=rec->movietitle;
                 int year=rec->year;
                 stringstream ss1;
                 ss1 <<year;
                 string yearString=ss1.str();
                // a->path="["+movie+"#"+"@"+yearString+"]";
                 if(a->prev==NULL)
                 {
                  if(a->distance==-1)
                  {
                   a->prev=curr;
                   a->setDistance(curr->distance+rec->weight);
                   a->path="["+movie+"#"+"@"+yearString+"]";
                   nodePrior.push(noder[index1]);
                  }
                 }
                 else if(a->prev!=NULL)
                 { 
                     //if(curr->prev!=a)
                    if(a->isVisited==false)
                     {
                         if(curr->distance+rec->weight<a->distance || a->distance==-1)
                         {
                             a->prev=curr;
                             a->setDistance(curr->distance+rec->weight);
                             a->path="["+movie+"#"+"@"+yearString+"]";
                             nodePrior.push(noder[index1]);
                         }
                     }
                 }
                 
                }
             }

         }
         

      }
  }
  cout<<"Traversing Graph Finished" <<endl;
        

  
  shortestPath="";
  node* end=nodeRecord[toActor];
  node* traverse=end;
  //cout<<traverse->name<<endl;
  //vector<edge*> tr=nodetoedge[traverse];
  /*for(int i=0;i<tr.size();i++)
  {
      cout<<tr[i]->movietitle<<endl;
  }*/
  if(traverse->prev==NULL)
  {
      cout<<"No pathway"<<endl;
  }
  
  vector<string> recordPathway;
  while(traverse->name!=fromActor && traverse->prev!=NULL)
  {
   // cout<<"We are in a traverse while loop" << endl;
    if(traverse->prev==start)
    {
        node* a=traverse->prev;
        shortestPath="("+a->name+")"+"--"+traverse->path+"-->" + "(" + traverse->name + ")" + shortestPath;
        //cout<<shortestPath<<endl;
    } 
    else
    {
        shortestPath="--"+traverse->path+"-->" + "(" + traverse->name + ")"+ shortestPath;
        //out<<shortestPath<<endl;
    }
    traverse=traverse->prev;
  //  cout<<traverse->name<<endl;
  }
  //cout<<"Graph REady?"<< endl;
//  cout<<shortestPath<<endl;
  for(unsigned int i=0;i<node1.size();i++)
  {
      node* modify=node1[i];
      modify->prev=NULL;
      modify->distance=-1;
      modify->isVisited=false;
      modify->path="";
  }
  if(traverse->name!=fromActor)
  {
      shortestPath="";
      return;
  }
}
void nodeDelete(node*& deleteStuff)
{
    if(deleteStuff->prev==NULL)
    {
        delete deleteStuff;
    }
    else{
        nodeDelete(deleteStuff->prev);
        delete deleteStuff;
    }
}

ActorGraph::~ActorGraph() {  
   for(int a=0;a<node1.size();a++)
   {
     /* if(node1[a]!=NULL)
      {
           if(node1[a]->prev!=NULL)
           {
               node* k=node1[a]->prev;
               nodeDelete(k);
           }
           //delete node1[a];
      }*/

      if(node1[a]!=NULL)
      {
          delete node1[a];
      } 
   }
   /*for(int a=0;a<actorNames.size();a++)
   {
      if(actorNames[a]!=NULL)
      {
           if(actorNames[a]->prev!=NULL)
           {
               node* k=actorNames[a]->prev;
               delete k;
           }
           delete actorNames[a];
      }
   }*/
   
     for(int a=0;a<edge1.size();a++)
   {
      

       if(edge1[a]!=NULL)
       {
           delete edge1[a];
       }
   }


   
   
   /*for(int index=0;index<node1.size();index++)
   {
     vector<edge*> deleteEdge=mapping[node1[index]->name];
     for(int index1=0;index1<deleteEdge.size();index1++)
     {
         if(deleteEdge[index1]!=NULL)
         {
          delete deleteEdge[index1];
         }
     }
   }*/

  /* for(int a=0;a<actorNames.size();a++)
   {
          if(actorNames[a]!=NULL)
          {          
            vector<edge*> edgeDelete=nodetoedge[actorNames[a]];
            for(int k=0;k<edgeDelete.size();k++)
            {
                if(edgeDelete[k]!=NULL)
                {
                    delete edgeDelete[k];
                }
            }
          }
   } */

   nodetoedge.clear();
   edgetonode.clear();
   mapping.clear();
   edgeRecord.clear();
   nodeRecord.clear();
   nodeRecordvector.clear();
  




}
