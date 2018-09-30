#include<iostream>
#include<vector>
#include<ctime>
#include<map>

using namespace std;

static int autoValue;

class NodeData{ // class that stores data field of a node
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

class Genesis{ // class that store full data od a node
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
    genesisReferenceNodeId = this;
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
  void addChildReference(Genesis* data){
    childReferenceId.push_back(data);
  }

  void setParentReference(Genesis* parentNode){
    referenceNodeId = parentNode;
  }

};

class MainApplication{
  map<int, Genesis*> nodeIdMap; //store address of each node
  map<int,Genesis*> genesisMap; //store genesis Node id of each node
public:
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

  void createGenesisNode(){ //function creates genesis node
    Genesis* genesisNodeData = createNode();
    nodeIdMap[genesisNodeData->getNodeNumber()] = genesisNodeData;
    genesisMap[genesisNodeData->getNodeNumber()] = NULL;
  }

  void displayGenesisNodes(){ // display all the genesis node
    map<int,Genesis*>::iterator it;
    for (it=genesisMap.begin(); it!=genesisMap.end(); ++it){
      if(it->second==NULL){
        Genesis* genData = nodeIdMap[it->first];
        genData->printData();
      }
    }
  }

  void createChildNode(){// creates a child node which requires input of parent id
    int parentId;
    cout<<"\nEnter Parent Node ID : ";
    cin>>parentId;
    if(nodeIdMap.find(parentId)!=nodeIdMap.end()){
      Genesis* parentNode = nodeIdMap[parentId];
      Genesis* genesisNodeData = createNode();

      genesisNodeData->setParentReference(parentNode);
      parentNode->addChildReference(genesisNodeData);

      nodeIdMap[genesisNodeData->getNodeNumber()] = genesisNodeData;

      if(genesisMap[genesisNodeData->getNodeNumber()]==NULL)
        genesisMap[genesisNodeData->getNodeNumber()] = parentNode;
      else
        genesisMap[genesisNodeData->getNodeNumber()] = genesisMap[parentId];
    }else{
      cout<<"\nParent does not exist\n\n";
    }
  }
};

int main(){ //a menu driven application
  char more;
  map<int, Genesis*> nodeIdMap; //store address of each node
  map<int,Genesis*> genesisMap; //store genesis Node id of each node
  MainApplication mainApp;
  do{
  int ch;
  cout<<"\nMenu\n1. Create Genesis Node\n2. Display Genesis Nodes\n3. Create Child Node\n4. Create Multiple Child Node\n";
  cout<<"5. Edit a node\n6. Transfer ownership\n\n";
  cout<<"Enter your choice : ";
  cin>>ch;
  switch (ch) {
    case 1:
      mainApp.createGenesisNode();
      break;
    case 2:
      mainApp.displayGenesisNodes();
      break;
    case 3:
      mainApp.createChildNode();
      break;
  }
  cout<<"\nWant to continue?(Y/N)";
  cin>>more;
}while(more=='y'||more=='Y');

  return 0;
}
