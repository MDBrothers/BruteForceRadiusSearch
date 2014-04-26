#include <utility.hpp>

float computeVertexDistance(const sf::Vertex first, 
                       const sf::Vertex second){
 return std::sqrt( std::pow(first.position.x - second.position.x, 2.0) +
          std::pow(first.position.y - second.position.y, 2.0) );
}

void generateNeighborhoods(std::vector< Neighborhood >& neighborhoodList, 
                                const float horizon, 
                                const std::vector< sf::Vertex >& myNodes,
                                const int startIndex,
                                const int stopIndex){
        std::vector< sf::Vertex > nodesCopy1(myNodes);
        comparator compy;
        for(int focusNode = startIndex; focusNode < stopIndex; ++focusNode){
            compy.changeMyCenter(myNodes[focusNode]);
            std::sort(nodesCopy1.begin(), nodesCopy1.end(), compy);

            int sortedNode = 0;
            for(; sortedNode < nodesCopy1.size(); ++ sortedNode){
                if (computeVertexDistance(nodesCopy1[sortedNode], compy.myCenter) > horizon)
                    break;
            }

            neighborhoodList.emplace_back();
            neighborhoodList[neighborhoodList.size()-1].me = myNodes[focusNode];
            neighborhoodList[neighborhoodList.size()-1].myNeighbors = std::vector< sf::Vertex >(nodesCopy1.begin(),
                                                                                                nodesCopy1.begin()+sortedNode);
        }
    }


