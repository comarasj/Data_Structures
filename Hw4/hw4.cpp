#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Digraph
{
   public:

       vector<bool> divisited;
       vector<string> ditasks;
       vector<vector<int> > diprecede, dipostcede;
       vector<int> diorder;
       int numtasks, priority, dinumtw;
  
   //reset the visited node
   void dirstVisited()
   {
       for(int dlp=0; dlp<divisited.size(); dlp++)
       {
           divisited[dlp]=false;
       }
   }
  
  //acyclic check
   bool dicheck(vector<vector<int> > dichk, int dipos1)
   {
       if(divisited[dipos1])
       {
           dirstVisited();
           return false;
       }
       divisited[dipos1]=true;
       bool diflag=true;
       if(dichk[dipos1][0]==-1)
       {
           dirstVisited();
           return true;
       }
       for(int dlp=0; dlp<dichk[dipos1].size(); dlp++)
       {
           if(!dicheck(dichk, dichk[dipos1][dlp]-1))
           {
               diflag= false;
           }
       }
       dirstVisited();
       return diflag;
   }
  
   //add the edge
   void addEdge(int dlnumB, int dlnumA)
   {
       if(diprecede[dlnumA-1][0]==-1)
       {
           diprecede[dlnumA-1][0]=dlnumB;
       }else
       {
           diprecede[dlnumA-1].push_back(dlnumB);
       }
       if(dipostcede[dlnumB-1][0]==-1)
       {
           dipostcede[dlnumB-1][0]=dlnumA;
       }else
       {
           dipostcede[dlnumB-1].push_back(dlnumA);
       }
       if(!dicheck(diprecede, dlnumA-1))
       {
           cout << "Infinite Preceding Loop! directed graph is not cyclic." << endl;
           exit(1);
       }
   }
  
   //delete the edge
   void deleteEdge(int dlnumA, int dlnumB)
   {
       for(int dlp=0; dlp<diprecede[dlnumA-1].size(); dlp++)
       {
           if(diprecede[dlnumA-1][dlp]==dlnumB)
           {
               diprecede[dlnumA-1].erase(diprecede[dlnumA-1].begin()+dlp);
           }
       }
       for(int dlp=0; dlp<dipostcede[dlnumB-1].size(); dlp++)
       {
           if(dipostcede[dlnumB-1][dlp]==dlnumA)
           {
               dipostcede[dlnumB-1].erase(dipostcede[dlnumB-1].begin()+dlp);
           }
       }
   }
  

   Digraph()
   {
       string diinp="?";
       cout << "Enter number of tasks?" << endl;
       cin >> numtasks;
       ditasks.resize(numtasks);
       diprecede.resize(numtasks);
       dipostcede.resize(numtasks);
       divisited.resize(numtasks);
       dirstVisited();
       for(int dlp=0; dlp<numtasks; dlp++)
       {
           diprecede[dlp].resize(1);
           dipostcede[dlp].resize(1);
           diprecede[dlp][0]=-1;
           dipostcede[dlp][0]=-1;
       }
       getline(cin, diinp);
       for(int dlp=1;dlp<=numtasks;dlp++)
       {
           cout << dlp << ". ";
           getline(cin, ditasks[dlp-1]);
       }
       cout << "Enter what precedes what (0 terminates):" << endl;
       while(cin >> priority && priority)

       {
           string difrst, discnd;
           int dlp=0;
           
           if(priority!=0)
           {
               cin >> dinumtw;
               addEdge(priority,dinumtw);
           }
           else
           {
               break;
           }
       }
   }
  
  
   ~Digraph()
   {
       divisited.~vector();
       ditasks.~vector();
       diprecede.~vector();
   }

   //topological sorting
   void topSort()
   {
       bool tsflag;
       vector<int> tsstack;
       for(int dlp=0; dlp<numtasks; dlp++)
       {
           if(diprecede[dlp][0]==-1)
           {
               tsstack.push_back(dlp);
               divisited[dlp]=true;
           }
       }
       while(!tsstack.empty())
       {
           cout << "work" << endl;
           tsflag=true;
           for(int jlp=0; jlp<dipostcede[tsstack[tsstack.size()-1]].size(); jlp++)
           {
               if(dipostcede[tsstack[tsstack.size()-1]][0]!=-1&&!divisited[dipostcede[tsstack[tsstack.size()-1]][jlp]])
               {
                   tsflag=false;
               }
           }
           if(tsflag)
           {
               cout << tsstack[tsstack.size()-1] << endl;
               diorder.push_back(tsstack[tsstack.size()-1]);
               tsstack.pop_back();
           }
           else
           {
               for(int jlp=0; jlp<dipostcede[tsstack[tsstack.size()-1]].size(); jlp++)
               {
                   if(!divisited[dipostcede[tsstack[tsstack.size()-1]][jlp]])
                   {
                       divisited[dipostcede[tsstack[tsstack.size()-1]][jlp]]=true;
                       tsstack.push_back(dipostcede[tsstack[tsstack.size()-1]][jlp]);
                       break;
                   }
               }
           }
       }
   }

  
   void resultdisplay()
   {
       cout << endl << endl;
       for(int dlp=0; dlp<numtasks; dlp++)
       {
           cout << diorder[diorder.size()-dlp-1] << endl;
       }
   }
};


int main()
{
   Digraph graph;
   graph.topSort();
   graph.resultdisplay();
   exit(1);
}
