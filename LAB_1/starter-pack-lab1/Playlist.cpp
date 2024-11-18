#include "Playlist.h"
#include <iostream>
using namespace std;



void Playlist::PrintMenu(const string& title) const {
  cout << title << " PLAYLIST MENU" << endl;
  cout << "a - Add song" << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist" << endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit" << endl << endl;
  char newPick;
  cout  << "Choose an option:" << endl;
}
  //Takes in a string id,a string song, a string artist and int length parameters that used to create a newNode and add it to the back of the playlist
void Playlist::AddSong(const string& id, const std::string& song, const std::string& artist, int length) {
PlaylistNode *newNode = new PlaylistNode(id,song,artist,length); // creates the new song or new Playlist node.
//The if statement checks if the list is empty, if so then it adds the new song as the first song and assigning head and tail to it
 if(head == nullptr){
      head = newNode; 
      tail = head;
    }
    //This is the only other case where the node is added to the end of the list
    else {
      tail->nextNodePtr = newNode;// tail next node is newNode
      tail= newNode; //tail becomes the newNode
      tail->nextNodePtr = nullptr;// tails next node becomes nullptr beause its the last node of the lsit
    }
}
    // Removese a song according the unique ID provided from input
void Playlist::RemoveSong() {
  cout << "Enter song's unique ID:" << endl;
  string removeID;
  cin >> removeID;

  int counter = 0;
    //case: if list is empty then it returns nothing
  if(head == nullptr){
    cout << "Empty PlayList" << endl;
    return;
  }
  
  PlaylistNode*curr =head;
  PlaylistNode*prev = nullptr;

  while(curr != nullptr){
    if(curr->GetID() == removeID){
      if (curr == head) {
        head = curr->nextNodePtr;
      }
      if (curr == tail) {
        tail = prev;
      }
      if (prev != nullptr) {
        prev->nextNodePtr = curr->nextNodePtr;
      }
    cout << "\"" <<  curr->GetSongName() <<"\""<< " removed." << endl << endl;
    delete curr;
    counter++;
    }
    //Traversing by changing values of prev and curr
    prev = curr; 
    curr = curr->nextNodePtr;
  }
  //This if statement lets us know if a invalid ID was provided
  if(counter == 0){
    cout << "ID not found" << endl;
    return;
  } 
}

void Playlist::ChangePositionSong() {
  //checks if the list is empty
  if(head == nullptr|| head->nextNodePtr == nullptr){
    cout << "no position to change " << endl;
    return;
  }
  int length = 0; 
  // The counterNode is used to traverse through the list and length keeps track of the amount
  //nodes are in the playlist
  PlaylistNode* CounterNode = head;
    while (CounterNode!= nullptr) {
      length++;
      CounterNode = CounterNode->nextNodePtr;
    }
  //User input for current Position a node 
  cout << "Enter song's current position:" << endl;
  int currPosition;
  cin >> currPosition;
  // User input for the position to change the current position to
  cout << "Enter new position for song:" << endl;
  int newPosition;
  cin >> newPosition;
  
  // if newPosition and currentPosition are the same then no changes need to be made
  if(newPosition == currPosition){
    return;
  }
    //finds the previous node of current Position Node and new PositionNode
    //currPosPrev = previous Node of currentPosition
    //newPosPrev  = previous Node of newPosition 
    //The loop goes up until the end of the playlist
    //while it iterates it check if counter less then the currentPosition-1 which if true then the currPosPrev will stop changing 
    //And make currPosPrev equal to previous node of currentPosition Node. Same thing happens to newPosition
    int counter = 1;
    PlaylistNode*currPosPrev =head;
    PlaylistNode*newPosPrev = head;
    while(counter<= length){
      if(counter < (currPosition-1)){
        currPosPrev = currPosPrev->nextNodePtr;
      }
      if(counter < (newPosition-1)){
        newPosPrev = newPosPrev->nextNodePtr;
      }
      counter++;
   }
  
    // Case1 : moving head somewhere else
    // Makes sure to change head to the appropriate node
    //
    if (currPosition == 1) {
    PlaylistNode*holdHeadNext = head->nextNodePtr; // holds heads next Node as it will get detach when changing heads Position
    PlaylistNode *newPosNode = newPosPrev->nextNodePtr; // newPosNode is the newPosition Node 
    PlaylistNode *currPosNode = head; // currPosNode is head because currPosition is 1 which is head
    currPosNode->nextNodePtr = newPosNode->nextNodePtr; // currentPosition next Node points to newPositions next node
    newPosNode->nextNodePtr = currPosNode; // newPositions next pointer points to current Position
    head = holdHeadNext; // head changes to heads nextNodePtr
      //Example list {1,2,3,4,5} C:1,4
      // 1 points to 5 
      // 4 points to 1
      // head becomes 2 
      //2->3->4->1->5
    }
    // Case 2 if newPosition is head or less then 1 
    //
    else if (newPosition == 1|| newPosition < 1) {
      PlaylistNode*currPosNode = currPosPrev->nextNodePtr;
      PlaylistNode*headPointerNode= head; // headPointerNode holds headNode
      PlaylistNode *holdNode = currPosNode->nextNodePtr; // holdNode holds currentPositions next node
      head = currPosNode; // head changes to currPositions Node
      currPosNode->nextNodePtr = headPointerNode; // currPosNode next points to the old head
      currPosPrev->nextNodePtr = holdNode; // previous of currPosNode points to currPosNodes nextNode
      //Example{1,2,3,4,5} C:3,1
      // head = 3;
      //3->1
      //2->4
      //3->1->2->4->5

    }
    // Case 3 if currPosition is greater than 4
    else if(newPosition < currPosition){
      PlaylistNode*newPosNode = newPosPrev->nextNodePtr;
      PlaylistNode*currPosNode = currPosPrev->nextNodePtr;
      // if statement checks if currPosition Node is tail if so then tail is changed to the node before current Position
      // so when tail moves somewhere in the front it updates the tail to the one before it as the new tail
      if (currPosNode == tail) {
        tail = currPosPrev;
      } 
      cout << currPosPrev->GetID() << endl;
      newPosPrev->nextNodePtr = currPosNode;// NewPositions previous's next pointer points to current Position 
      currPosPrev->nextNodePtr = currPosNode->nextNodePtr; // CurrentPositions previous's next pointer points to current Position next
      currPosNode->nextNodePtr = newPosNode;// currentPositions next pointer points to new Position
      // Example: {1,2,3,4,5} C:4,2
      //1->4
      //3->5
      //4->2
      //{1,4,2,3,5}
    }
    else {
      // checks if newPosition > currPosition
      PlaylistNode*newPosNode = newPosPrev->nextNodePtr; 
      PlaylistNode*currPosNode = currPosPrev->nextNodePtr;
      PlaylistNode *holdNode = newPosNode->nextNodePtr; // holds the newPosNodes next node to keep track of it if it gets detached
      currPosPrev->nextNodePtr = currPosNode->nextNodePtr; // currentPositions previous points to currentPositions next Node
      newPosNode->nextNodePtr = currPosNode; // newpositions next points to currentPosition Node
      currPosNode->nextNodePtr = holdNode; // current Position nodes next node points to the old new positions next Node
    }
    // Example: {1,2,3,4,5} C: 2,4
    //1->3
    //4->2
    //2->5
    //{1,3,4,2,5}
    cout << "\"" << currPosPrev->GetSongName() << "\""<< " moved to position " << newPosition << endl << endl;
    return;
}
 
  

    //OutPuts song by specfic playList 
    // asks user input for artist name

void Playlist::OutputSongsByArtist() const {
  string artistName;
  cout << "Enter artist's name:" << endl << endl;
  cin.ignore();
  getline(cin, artistName);
  //checks if the playlist is empty
  if(head == nullptr){
    cout << "Error" << endl;
  }
  // checks if there is only 1 artist name and if so then it checks if the artist name of that
  // that song matches with the user input
  if(head->nextNodePtr == nullptr && head->GetArtistName() == artistName){
    head->PrintPlaylistNode();
  }
  // Traverses through the list and checks if artist name of each song matches with the 
  // user input and if so then it prints out the song
  else{
    PlaylistNode*curr =head;
    int counter = 1;
    while(curr != nullptr){  
      if(curr->GetArtistName() == artistName){
        cout << counter << ".";
        curr->PrintPlaylistNode(); 
      }
      curr = curr->nextNodePtr;
      counter++;
    }
  }
}



    //Outputs the total time of the whole playlist
void Playlist::OutputTotalTime() const {
  // checks if the playlist is empty
  if(head == nullptr){
    cout << "0 total time" << endl;
  }
  // checks if the playlist has only one song
  if(head->nextNodePtr == nullptr){
    cout << "Total Time:"<< head->GetSongLength() << " seconds" << endl << endl;
  }
  //final case
  else{
    int totalSeconds = 0; 
    // the loop traverses through the playlists and adds the time of each song to the totalSeconds
    for( const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
      totalSeconds = totalSeconds+curr->GetSongLength();
    }
    cout << "Total time: " << totalSeconds << " seconds" << endl << endl; // outputs the total time
  }
}
 //Outputs all songs of the playlist
void Playlist::OutputFullPlaylist() const {
  // checks if the song is empty
  if(head == nullptr) { 
    cout << endl << "Playlist is empty" << endl << endl;
    return;
  }
  //Checks if there is only one song 
  if(head->nextNodePtr == nullptr){
    cout << endl << "1." ;
    head->PrintPlaylistNode();
  }
  // final case: where if the loop traverse through the playlists and outputs each song 
  else {
    int positionNum = 1;
    PlaylistNode*curr = head;
   cout << endl;
   while(curr != nullptr){
    cout  << positionNum << ".";
    curr->PrintPlaylistNode();
    curr= curr->nextNodePtr;
    positionNum++;
   }
  }
}


