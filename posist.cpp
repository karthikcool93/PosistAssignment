#include<iostream>
#include<vector>
#include<ctime>
#include<map>

using namespace std;

static int autoValue;

class NodeData{
    int ownerId;
    float value;
    string ownerName;
    string HashValue;
  public:
    NodeData(int ownerId,float value,string ownerName){
      this->ownerId = ownerId;
      this->value = value;
      this->ownerName = ownerName;
      this->HashValue = "";
    }
    int getOwnerId(){
      return ownerId;
    }
    float getValue(){
      return value;
    }
    string getOwnerName(){
      return ownerName;
    }
    void printData(){
      cout<<"\nOwner ID : "<<ownerId<<endl;
      cout<<"Value : "<<value<<endl;
      cout<<"Owner Name : "<<ownerName<<endl;
      cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    }
};

class Genesis{
  string timestamp;
  NodeData data;
  int nodeNumber;
  string nodeId;
  Genesis* referenceNodeId;
  vector<Genesis*> childReferenceId;
  Genesis* genesisReferenceNodeId;
  string hashValue;
public:
  Genesis(NodeData data1):data(data1.getOwnerId(),
                          data1.getValue(),data1.getOwnerName()){
    time_t now = time(0);
    string dt(ctime(&now));
    timestamp = dt;
    referenceNodeId = NULL;
    nodeNumber = ++autoValue;
    nodeId = to_string(nodeNumber);
  }
  NodeData getNodeData(){
    return data;
  }
  int getNodeNumber(){
    return nodeNumber;
  }
  void printData(){
    data.printData();
  }

};

Genesis* createNode(){
  int ownerId;
  float value;
  string ownerName;
  cout<<"\nEnter Genesis Owner Id : ";
  cin>>ownerId;
  cout<<"Enter value :";
  cin>>value;
  cout<<"Enter Owner Name : ";
  cin>>ownerName;
  NodeData nd(ownerId,value,ownerName);
  Genesis* genesisNodeData = new Genesis(nd);
  return genesisNodeData;
}

void createGenesisNode(map<int,Genesis*>&nodeIdMap, map<int,Genesis*> &genesisMap){
  Genesis* genesisNodeData = createNode();
  nodeIdMap[genesisNodeData->getNodeNumber()] = genesisNodeData;
  genesisMap[genesisNodeData->getNodeNumber()] = NULL;
}

void displayGenesisNodes(map<int,Genesis*>&nodeIdMap, map<int,Genesis*> &genesisMap){
  map<int,Genesis*>::iterator it;
  for (it=genesisMap.begin(); it!=genesisMap.end(); ++it){
    Genesis* genData = nodeIdMap[it->first];
    genData->printData();
  }
}


int main(){
  char more;
  map<int, Genesis*> nodeIdMap; //store address of each node
  map<int,Genesis*> genesisMap; //store genesis Node id of each node
  do{
  int ch;
  cout<<"\nMenu\n1. Create Genesis Node\n2. Create Child Node\n3. Create Multiple Child Node\n";
  cout<<"4. Edit a node\n5. Transfer ownership\n6. Display Genesis Nodes\n\n";
  cout<<"Enter your choice : ";
  cin>>ch;
  switch (ch) {
    case 1:
      createGenesisNode(nodeIdMap, genesisMap);
      break;
    case 6:
      displayGenesisNodes(nodeIdMap, genesisMap);
      break;
  }
  cout<<"\nWant to continue?(Y/N)";
  cin>>more;
}while(more=='y'||more=='Y');

  return 0;
}
