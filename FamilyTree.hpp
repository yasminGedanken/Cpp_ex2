#include <string>
#include <vector>

using namespace std;

namespace family
{
class Tree
{
private:
    string name;
    Tree *mother;
    Tree *father;
    Tree *sun;
    string sex;
    int rank;

public:
    Tree(string n)
    {
        name = n;
        mother = nullptr;
        father = nullptr;
        sun= nullptr;
        sex= "";
        rank =0;

    }

  //  ~Tree();

    Tree &addFather(string, string);
    Tree &addMother(string, string);
    string relation(string);
    string find(string);
    void display();
    void remove(string);
    Tree *findName(Tree *t,string name1);
    std::vector<std::string> split (const string &s, char delim);
    std::string nameF(Tree *t,int size,string sex);
    void removeF(Tree *name);
    void print2DUtil(Tree *root, int space);
};

} // namespace family