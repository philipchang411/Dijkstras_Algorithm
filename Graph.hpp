#include "GraphBase.hpp"

#include <algorithm>
#include <climits>
#include <map>

class Vertex 
{
    private:
        std::string label;      //name of each vertex
        std::map<std::string, Vertex*> connectingEdges; //Each vertex has the connected edges

    public:
        void addVertex(std::string label, Vertex* v);       //adds the vertex to the connectingEdge map
        void removeVertex(std::string label);               //removes the vertex
        std::map<std::string, Vertex*> adjacents();         //returns the connecting edges

        //Overloaded constructor
        Vertex(std::string input)
        {
            this->label = input;
        }
};

class Edge 
{
    private:
        //You sort them based off of the vertex that they are connected to
        std::string start;
        std::string end;

    public:
        unsigned long weight; //By making it public, I do not need a getWeight() function in the Graph getWeight().

        //overloaded functions that return that aids in searching
        bool isStart(std::string label1, std::string label2);       
        bool isStart(std::string label1);
        bool isEnd(std::string label1, std::string label2);
        bool isEnd(std::string label1);

        //overloaded constructor
        Edge(std::string s, std::string e, unsigned long w)
        {
            start = s;
            end = e;
            weight = w;
        } 
};

class Graph
{
    private:
        std::map<std::string, Vertex> vertex;   //Map contains all of the existing vertex   
        std::map<int, Edge> edge;               //Contains all of the existing edges
        //Each edge has it's own number instead of the string as a name
        int name = 0;                       

    public:
        //Required functions
        void addVertex(std::string label);
        void removeVertex(std::string label);
        void addEdge(std::string label1, std::string label2, unsigned long weight);
        void removeEdge(std::string label1);
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
    
        //A simple comparator that determines which distance is shorter
        unsigned long comparator(std:: string curr, std::string adj, unsigned long currDistance, unsigned long oldDistance);

        //returns the edge ID. This is necessary to switch the std::string key to an int. 
        int getEdgeKey(std::string label1, std::string label2);                          
        int getEdgeKey(std::string label1);                                              

        //Finds the shortest distance from a given vertex.  Returns the label of the closest vertex to the given point.
        std::string minDistance(std::map<std::string, unsigned long> input);    

        //returns the distance from two vertexes. 
        unsigned long getWeight(std::string curr, std::string adj);          

        //determines if you have or have not already been to a node.            
        bool unvisited(std::string label,std:: map<std::string, unsigned long> unvisited);
};