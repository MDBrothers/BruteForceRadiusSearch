#include <main.hpp>
#include <simulation.hpp>
#include <player.hpp>

struct neighborhood{
    sf::Vertex me;
    std::vector< sf::Vertex > myNeighbors;
    std::vector< float > consByVolFrac;
    float mass;
};
typedef struct neighborhood Neighborhood;


float computeVertexDistance(const sf::Vertex first, const sf::Vertex second);

struct comparator{        
        public:
            sf::Vertex myCenter;

             bool operator () (const sf::Vertex first, 
                              const sf::Vertex second){
                if (computeVertexDistance(first, myCenter) <= computeVertexDistance(second, myCenter))
                    return true;
                else
                    return false;
            }

        void changeMyCenter(const sf::Vertex& center){
            myCenter = center;
        }
};

       void generateNeighborhoods(std::vector< Neighborhood >& neighborhoodList, 
                                const float horizon, 
                                const std::vector< sf::Vertex >& myNodes,
                                const int startIndex,
                                const int stopIndex);

