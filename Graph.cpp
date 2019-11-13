#include "Graph.hpp"

//Inserts the name of the vertex into the overall edges
void Vertex::addVertex(std::string input, Vertex* temp) 
{ 
    connectingEdges.insert(make_pair(input, temp)); 
} 

//removes a given vertex from the map of connecting edges
void Vertex::removeVertex(std::string label) 
{ 
    connectingEdges.erase(label); 
}

//returns the map of all connecting edges. 
std::map<std::string, Vertex*> Vertex::adjacents() 
{ 
    return connectingEdges; 
}

//Returns bool based off if one of the two paramters is the source of the edge. Searches of the edge
bool Edge::isStart(std::string label1, std::string label2) 
{
    if(start == label1 || start == label2)
        return true;
    else
        return false;
}

//Return the bool based on if the parameter is the source of the edge.
bool Edge::isStart(std::string label1)
{
    if(start == label1)
        return true;
    else   
        return false;
} 

//The exact same as the isStart(). But it looks for the destination of the edge instead
bool Edge::isEnd(std::string label1, std::string label2)
{
    if(end == label1 || end == label2)
        return true;
    else
        return false;    
}

bool Edge::isEnd(std::string label1)
{
    if(end == label1)
        return true;
    else
        return false;
}

//Adds the vertex to the map with all the verticesy
void Graph::addVertex(std::string label) 
{
    vertex.insert(make_pair(label, Vertex(label)));
}

//Removes the edge and the vertex from the edge map and the vertex map. 
void Graph::removeVertex(std::string label) 
{
    for (std::map<int, Edge>::iterator it = edge.begin(); it != edge.end(); it++)
        removeEdge(label);

    for (std::map<std::string, Vertex>::iterator it = vertex.begin(); it != vertex.end(); it++)
        it->second.removeVertex(label);

    vertex.erase(label);
}

//Add the edge to the maps. Has to do it twice for each because it switches the source and destination
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
    //Edge key is an int and it tests to see if the edge already exists or not. 
    if(getEdgeKey(label1, label2) == 0) 
    {
        //The parameters are switched for both.
        edge.insert(std::make_pair(++name, Edge(label1, label2, weight)));

        vertex.insert(make_pair(label1, Vertex(label1)));
        vertex.insert(make_pair(label2, Vertex(label2)));

        vertex.at(label1).addVertex(label2, &(vertex.at(label2)));
        vertex.at(label2).addVertex(label1, &(vertex.at(label1)));
    }
}

//Removes the edge if it exists. 
void Graph::removeEdge(std::string label) 
{
    //if the key is not 0, then that means it exists.
    int temp = getEdgeKey(label);
    if (temp != 0)
        edge.erase(temp);
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) 
{
    //Create two maps. One with the visited vertecies. One with the vertex that not visited yet
    std::map<std::string, unsigned long> vertexQueue;    
    std::map<std::string, std::string> visited;  

    //Defaults to 0 to start with     
    unsigned long shortest = 0;                

    //for loop creates the unvisited map first and gives it inifinity as the default distance. Visited is also made and given "default" values as well
    for(std::map<std::string, Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
    {
        //The starting vertex as a distance of zero. else it is infinity since distance is unknown. 
        if(it->first == startLabel)
            vertexQueue.insert(make_pair(it->first, 0));
        else 
            vertexQueue.insert(make_pair(it->first, LONG_MAX));
        
        //default values
        visited.insert(make_pair(it->first, it->first));
    }

    //As long as you have verticies to see keep doing this
    while (!vertexQueue.empty()) 
    {
        //Finds the vertex that is closest to you
        std::string currentLabel = minDistance(vertexQueue);
        
        //Finds the distance to the nearest vertex
        unsigned long currentDistance = vertexQueue.at(currentLabel);

        //CANNOT GET TO WORK WITH ITERATOR
        //for(std::map<std::string, Vertex*>::iterator it = vertex.at(currentLabel).adjacents().begin(); it != vertex.at(currentLabel).adjacents().end(); ++it)
       // {
       // }
        //This for loop goes through all of the connecting edges
        for (auto it : vertex.at(currentLabel).adjacents()) 
        {             
            //Check if the parameters were not visited
            if (unvisited(it.first, vertexQueue)) 
            {                      
                //temporary variable to store the distance   
                unsigned long oldDistance = vertexQueue.at(it.first);

                //get the new distance
                vertexQueue.at(it.first) = comparator(currentLabel, it.first, currentDistance, oldDistance);

                //add the vertex to the visited map 
                if (oldDistance != vertexQueue.at(it.first)) 
                    visited.at(it.first) = currentLabel;
            }
        } 
        //removes the vertex from unvisited
        vertexQueue.erase(currentLabel);         // remove vertex from "unvisited" list
    }

    //this creates the path that is then returned and adds up the distance based on the path created. 
    path.emplace(path.begin(), endLabel);
    while(endLabel != startLabel)
    {
        path.emplace(path.begin(), visited.at(endLabel));
        shortest = shortest + getWeight(endLabel, visited.at(endLabel));

        //This changes the endLabel so that it eventually breaks out of the while loop
        endLabel = visited.at(endLabel);
    }

    return shortest;
}

//compares the distance between the old and new distances. Returns the smaller one
unsigned long Graph::comparator(std:: string key, std::string edge, unsigned long currentDistance, unsigned long previousDistance) 
{
    unsigned long newDistance = currentDistance + getWeight(key, edge);
    if (newDistance < previousDistance)
        return newDistance;
    else
        return previousDistance;
}

//The two functions mainly test to see if the vertex exists based on the integer "Assigned" to them. 
int Graph::getEdgeKey(std::string label1, std::string label2) 
{
    for(std::map<int,Edge>::iterator it = edge.begin(); it != edge.end(); ++it)
    {
        if(it->second.isStart(label1, label2) && (it->second.isEnd(label1, label2)))
            return it->first;
    }
    return 0;
}

int Graph::getEdgeKey(std::string label1) 
{
    for (std::map<int, Edge>::iterator it = edge.begin(); it != edge.end(); ++it)
    {
        if (it->second.isStart(label1) || it->second.isEnd(label1))
            return it->first;
    }
    return 0;
}

//A comparator helper function that tests the distance of the edge
std::string Graph::minDistance(std::map<std::string, unsigned long> input) 
{
    std::string result;
    unsigned long min = LONG_MAX;

    for(std::map<std::string, unsigned long>::iterator it =input.begin(); it != input.end(); ++it)
    {
        if(it->second < min)
        {
            result = it->first;
            min = it->second;
        }
    }

    return result;
}

//Simple get function. 
unsigned long Graph::getWeight(std::string curr, std::string adj) 
{
    return edge.at(getEdgeKey(curr, adj)).weight;
} 

//Tests to see if a vertex exists in the unvisited map
bool Graph::unvisited(std::string label, std::map<std::string, unsigned long> vertexQueue) 
{
    if(vertexQueue.find(label) != vertexQueue.end())
        return true;
    else
        return false;
}