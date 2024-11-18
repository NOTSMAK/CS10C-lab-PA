#include <list>
#include <string>

using std::list;
using std::string;

class WordLadder {

  private:
  list<string> dict;      

  public:
    WordLadder(const string& filename);
    void outputLadder(const string &start, const string &end, const string &outputFile);
};
