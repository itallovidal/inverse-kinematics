#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define HALF_WINDOW_WIDTH WINDOW_WIDTH / 2
#define HALF_WINDOW_HEIGHT WINDOW_HEIGHT / 2
#define PARTICLE_INITIAL_POSITION_X HALF_WINDOW_WIDTH - 18.f
#define PARTICLE_INITIAL_POSITION_Y WINDOW_HEIGHT - (2 * 18.f + 12.f)
std::mt19937 gen(time(NULL));

float getRandomNumber(int min, int max)
{
    std::uniform_real_distribution<float> distrib(min, max);
    float value = distrib(gen);

    // std::cout << "Random Value" << value << "\n";
    return value;
}

class Particle
{
    float x;
    float y;
    float vx = getRandomNumber(-1, 1);
    float vy = getRandomNumber(-5, -3);
    uint8_t alpha = 255u;
    sf::CircleShape shape;
    int isAlive = 1;

    void decreaseOpacity()
    {

        if (this->alpha > 0)
        {
            this->shape.setFillColor({255, 255, 255, this->alpha});
            this->alpha -= 3u;
            return;
        }

        this->isAlive = 0;
    }

public:
    Particle(float radius, float x, float y)
    {
        this->shape.setRadius(radius);
        this->shape.setFillColor({255, 255, 255, this->alpha});
        this->x = x;
        this->y = y;
        this->shape.setPosition({x, y});
    };

    sf::CircleShape show()
    {
        return this->shape;
    }

    void update()
    {
        this->shape.setPosition({
            this->shape.getPosition().x + this->vx,
            this->shape.getPosition().y + this->vy,
        });

        this->decreaseOpacity();
    }

    int getIsAlive()
    {
        return this->isAlive;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Smoke Like Particle System");
    window.setFramerateLimit(144);
    std::vector<Particle> particles;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        Particle p(18.f, PARTICLE_INITIAL_POSITION_X, PARTICLE_INITIAL_POSITION_Y);
        particles.push_back(p);

        for (int i = particles.size() - 1; i >= 0; i--)
        {
            window.draw(particles[i].show());
            particles[i].update();

            if (!particles[i].getIsAlive())
            {
                particles.erase(particles.begin() + i);
            }
        }

        std::cout << "Quantidade de bolinhas:" << particles.size() << "\n";

        window.display();
    }
}