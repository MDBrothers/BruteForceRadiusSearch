#include <main.hpp>
#include <utility.hpp>
#include <simulation.hpp>
#include <player.hpp>

int main(int argc, char* argv[])
{
	const int WINDOW_X_SIZE = 800;
	const int WINDOW_Y_SIZE = 600;

	const double x_center = WINDOW_X_SIZE/2;
	const double y_center = WINDOW_Y_SIZE/2;
	sf::Vector2f center(x_center, y_center);
	const double PI = 3.141;
    const float HORIZON = 20.0;

	// create the window
	sf::RenderWindow window(sf::VideoMode(WINDOW_X_SIZE, WINDOW_Y_SIZE), "Unfinished junk :'(");
    sf::Clock clock;
    sf::Font font;
    font.loadFromFile("./dat/FreeSansBold.ttf");
    sf::Text framerate(std::to_string(1.21), font, 20);
    framerate.setPosition(sf::Vector2f(400.0,50.0));
    framerate.setColor(sf::Color::Black);


	//Colors
    //
    // uraninite
	const sf::Color GREEN(55,255,55);

    // Granite 
    const sf::Color ORANGE(200,75,75);

    // Basalt
	const sf::Color BLUE(55,55,255);

    // Anthracite
    const sf::Color BLACK(12,12,12);

    //Materials
    int numberOfMaterialNodes = 4800;
	std::vector<sf::Vertex> nodes(numberOfMaterialNodes);

    //RNG
    std::default_random_engine generator1;
    std::default_random_engine generator2;
    std::default_random_engine generator3;
    std::default_random_engine generator4;
    std::default_random_engine generator5;
    std::default_random_engine generator6;
    std::default_random_engine generator7;
    std::default_random_engine generator8;

    generator1.seed(1337);
    generator2.seed(42);
    generator3.seed(137);
    generator4.seed(4);
    generator5.seed(337);
    generator6.seed(2);
    generator7.seed(13);
    generator8.seed(0);


    std::uniform_real_distribution<float> basaltXDist(0.0,800.0);
    std::uniform_real_distribution<float> basaltYDist(550.0,600.0);

    std::uniform_real_distribution<float> graniteXDist(0.0,800.0);
    std::uniform_real_distribution<float> graniteYDist(160.0,300.0);

    std::uniform_real_distribution<float> uraniniteXDist(0.0,800.0);
    std::uniform_real_distribution<float> uraniniteYDist(400.0,550.0);

    std::uniform_real_distribution<float> anthraciteXDist(0.0,800.0);
    std::uniform_real_distribution<float> anthraciteYDist(300.0,400.0);

    auto basaltX = std::bind(basaltXDist, generator1);
    auto basaltY = std::bind(basaltYDist, generator2);

    auto graniteX = std::bind(graniteXDist, generator3);
    auto graniteY = std::bind(graniteYDist, generator4);

    auto uraniniteX = std::bind(uraniniteXDist, generator5);
    auto uraniniteY = std::bind(uraniniteYDist, generator6);

    auto anthraciteX = std::bind(anthraciteXDist, generator7);
    auto anthraciteY = std::bind(anthraciteYDist, generator8);

	for(int i = 0; i < nodes.size(); i+=4)
	{
		nodes[i].position = sf::Vector2f(basaltX(), basaltY());
		nodes[i+1].position = sf::Vector2f(graniteX(), graniteY());
		nodes[i+2].position = sf::Vector2f(uraniniteX(), uraniniteY());
		nodes[i+3].position = sf::Vector2f(anthraciteX(), anthraciteY());

		nodes[i].color = BLUE;
		nodes[i+1].color = ORANGE;
		nodes[i+2].color = GREEN;
		nodes[i+3].color = BLACK;
	}

    // build the neighborhoods
    std::vector< Neighborhood > myNeighborhoods;
   /* 
        int numThreads = 4;
        int intervals = nodes.size()/numThreads;
        int lastInterval = intervals+1;
        std::vector< std::vector< Neighborhood > > neighborhoodFracturedLists(numThreads);
        std::vector< std::thread > threads;

        for(int threadIndex = 0; threadIndex < numThreads-1; threadIndex++){
            threads.emplace_back(std::thread( &nGenerator::generateNeighborhoods, &maker, neighborhoodFracturedLists[threadIndex], HORIZON, nodes, threadIndex*intervals, threadIndex*intervals+intervals) );
        }
*/
        generateNeighborhoods(myNeighborhoods, HORIZON, nodes, 0, nodes.size());
/*
        for(int threadIndex = 0; threadIndex < numThreads-1; threadIndex++){
            threads[threadIndex].join();
        }

        for(int threadIndex = 0; threadIndex < numThreads; threadIndex++){
            for(int neighborhood = 0; neighborhood < neighborhoodFracturedLists[threadIndex].size(); neighborhood++){
                myNeighborhoods.emplace_back(neighborhoodFracturedLists[threadIndex][neighborhood]);
            }
        }
  */  

	// run the program as long as the window is open
	window.setFramerateLimit(1);
    int wiggleCandidate = 0;
    sf::CircleShape circle(8.0,5);

	while (window.isOpen())
	{
        if (wiggleCandidate == myNeighborhoods.size())
            wiggleCandidate = 0;
        else
            wiggleCandidate++;

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();	
		}

        int neighborhood = wiggleCandidate;
		window.clear(sf::Color::White);
        for (int node = 0; node < myNeighborhoods[neighborhood].myNeighbors.size(); node++){
            framerate.setPosition(myNeighborhoods[neighborhood].myNeighbors[node].position);
            framerate.setColor(myNeighborhoods[neighborhood].myNeighbors[node].color);
            framerate.setString(std::to_string(neighborhood));
            window.draw(framerate);
        }

        framerate.setPosition(400.0, 50.0);
        framerate.setString(std::to_string(std::pow(clock.restart().asSeconds(), -1.0)));
        window.draw(framerate);
		window.display();	
	}

	return 0;
}
