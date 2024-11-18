// -*-c++-*-

#pragma once
#include <iostream>
using namespace std;
class PlaylistNode {
public:
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;
  PlaylistNode(): uniqueID("none"), songName("none"),artistName("none"),songLength(0),nextNodePtr(0){
  }

  PlaylistNode(string newID,string newSong, string newArtist, int songSize){
    uniqueID = newID;
    songName = newSong;
    artistName = newArtist;
    songLength = songSize;
    nextNodePtr = 0;
  }
  
  void InsertAfter(PlaylistNode* newNode){
    newNode->nextNodePtr = this->nextNodePtr;
    this->nextNodePtr = newNode;
  }

  void SetNext(PlaylistNode* newNode) {
    newNode->nextNodePtr = this->nextNodePtr;
    this->nextNodePtr = newNode;
  }

  const string& GetID() const { return uniqueID; }
  const string& GetArtistName() const { return artistName; }
  const string& GetSongName() const { return songName; }
  int GetSongLength() const { return songLength; }
  PlaylistNode* GetNext() { return nextNodePtr; }
  const PlaylistNode* GetNext() const { return nextNodePtr; }
  
  const void PrintPlaylistNode() const {
    cout << endl << "Unique ID: " << uniqueID << '\n';
    cout << "Song Name: " << songName << '\n';
    cout << "Artist Name: " << artistName << '\n';
    cout << "Song Length (in seconds): " << songLength  << '\n' << endl;
  }
};

class Playlist {
  PlaylistNode* head;
  PlaylistNode* tail;
public:
  Playlist()
    : head(nullptr),tail(nullptr)
  {}
   ~Playlist() {
    PlaylistNode* curr = head;
    while (curr != nullptr) {
      delete curr;
      curr = curr->nextNodePtr;
    }
  }
  Playlist(const Playlist&) = delete;
   Playlist &operator=(const Playlist&) = delete;
  void PrintMenu(const string& title) const;
  void AddSong(const string& id, const std::string& song, const std::string& artist, int length);
  void RemoveSong();
  void ChangePositionSong();
  void OutputSongsByArtist() const;
  void OutputTotalTime() const;
  void OutputFullPlaylist() const;
  
};

