#include<bits/stdc++.h>
using namespace std;
unordered_map<int,int> ma;
typedef struct hashset
{
  int id;
  float value;
  string name;
};
class data
{
public:
  int ownerid;
  float value;
  string ownername;
  hashset hashval;
public:
  data()
  {
    ownerid = -1;
    value = 0;
  }
  data(int id,float val,string name)
  {
    ownerid = id;
    val = value;
    ownername = name;
    hashval.id = id;
    hashval.value = val;
    hashval.name = name;
  }
  float getvalue()
  {
    return this->value;
  }
};

class mytree
{
private:
  static int nodeNumber;
  string nodeId;
  data da;
  vector<mytree*> childnodes;

public:
  mytree()
  {
    da.value = -1;
  }
  mytree(data d)
  {

    da = d;
  }
  int getsum(mytree *node)
  {
    int sum = 0;
    for(int i=0;i<node->childnodes.size();i++)
    {
      sum = sum + node->childnodes[i]->da.value;
    }
    return sum;
  }
  ////////////creating node/////////////
  void create(int id,int d,string name,string nodeid)
  {
    ////////It's checking whether another owner id exists or not//////////
    if(ma.find(id)!=ma.end())
    {
      ///////If owner id is already there////////
      cout << "ID ALREADY EXISTS" << endl;
      return ;
    }
    else
    {
      ma[id]=1;
    }
    if(this->da.value == -1)
    {
      ///////If it is the first node////////////
      cout << "GENESIS NODE CREATED" << endl;
      this->da.value = d;
      this->da.ownerid = id;
      this->da.ownername = name;
      this->nodeId = nodeid;
    /*  cou++;
      this->nodeNumber = cou;*/
      this->nodeNumber++;
      return ;
    }
    else
    {
      //////////////To check if we can insert as the child of genesis node/////////////////////
        if(getsum(this)+d < this->da.value)
        {
          mytree *node = new mytree();
          node->da.value = d;
          node->da.ownerid = id;
          node->da.ownername = name;
        /*  cou++;*/
          node->nodeNumber++;
          node->nodeId = nodeid;
          this->childnodes.push_back(node);
          return ;
        }
        else
        {
                //////////////To check if we can insert as the child of child genesis node/////////////////////
          for(int i=0;i<this->childnodes.size();i++)
          {
            ///////////checking values of each child node//////////////////////
            if(getsum(this->childnodes[i])+d < this->childnodes[i]->da.value)
              {
                mytree *node = new mytree();
                node->da.value = d;
                node->da.ownerid = id;
                node->da.ownername = name;
                //cou++;
                node->nodeNumber++;
                node->nodeId = nodeid;
                this->childnodes[i]->childnodes.push_back(node);
                return ;
              }
          }
        }
          cout << "INSERTION NOT POSSIBLE" << endl;
          return ;
    }
  }
///////////////LEVEL ORDER TRAVERSAL///////////////////////////////////////
  void display()
  {
  //  cout << "YES2" << endl;
      vector<vector<data>> ans;
      queue<mytree*> q;
      q.push(this);
      int depth = 0;
//cout << "YES3" << endl;
ans.resize(depth+1);
      while(!q.empty())
      {
        int size = q.size();
      //  cout << "YES4" << endl;
        while(size--)
        {
          //cout << "YES5" << endl;
          mytree *n =   q.front();
          //cout << "YES6" << endl;
          q.pop();
          ans[depth].push_back(n->da);
        //  cout << n->data << endl;
        //  cout << "YES7" << endl;
          for(auto mytree :n->childnodes)
          q.push(mytree);
        }
        depth++;
        ans.resize(depth+1);
      }
      for(int i=0;i<ans.size();i++)
      {
        for(int j=0;j<ans[i].size();j++)
        {
          cout <<"NodeNumber :" << nodeNumber << "|||NodeId :" << nodeId  << "|||OwnerId :" <<ans[i][j].ownerid << "|||OwnerName : " << ans[i][j].ownername << "|||Value: " << ans[i][j].value ;
        }
        cout << endl;
      }
  }
};
int mytree::nodeNumber = 0;
int main()
{
  ///////////first is ownerid,value,ownername,nodeid/////////////
  mytree obj;
  obj.create(45,60,"yogesh","Firstnode");
  obj.display();
  obj.create(41,50,"Rahul","SecondNode");
  obj.display();
  obj.create(20,40,"Himanshu","ThirdNode");
  obj.display();
obj.create(10,2,"Aditya","FourthNode");
obj.display();
obj.create(12,3,"Utkarsh","FifthNode");
obj.display();
obj.create(12,3,"Kapoor","SixthNode");
obj.display();

}
