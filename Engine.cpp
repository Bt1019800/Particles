#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace sf;
using namespace std;

Engine::Engine()
{
    width = VideoMode::getDesktopMode().width;
    height = VideoMode::getDesktopMode().height;
    VideoMode vm(width, height);
    m_Window.create(vm, "Particles.exe", Style::Default);
}

void Engine::run()
{
    Clock clock;
    Time time1 = clock.getElapsedTime();

    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    while (m_Window.isOpen())
    {
        Time time2 = clock.restart();
        float seconds = time2.asSeconds();
        m_Window.input();
        m_Window.update(seconds);
        m_Window.draw();
    }
}

void Input()
{
    srand(time(0));
    Event event;
    while(m_Window.pollEvent(event))
    {
        if(event.type == Event::Closed)
        {
            m_Window.close();
        }
            
        if(event.type == Event::MouseButtonPressed)
        {
            Vector2i location = {event.mouseButton.x, event.mouseButton.y};
            if(event.mouseButton.button == Mouse::Left)
            {
                for (size_t i = 0; i < 5; i++)
                {
                    int numPoints = (rand() % 51) + 25;
                    Particle particle(m_Window, numPoints, location);  
                }
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    for (size_t i = 0; i < m_particles.size())
    {
        if (m_particles[i].getTTL() == 0)
        {
            m_particles.erase(m_particles.begin() + i);
        }

        if (m_particles[i].getTTL() > 0)
        {
            m_particles[i].update(dtAsSeconds);
            i++;
        }

        else
        {
           size_t = temp;
           temp = m_particles.erase(m_particles.begin() + i);
           i = temp;
        }
    }    
}

void Engine::draw()
{
    m_Window.clear();

    for (size_t i = 0; i < m_particles.size(); i++)
    {
        m_Window.draw(m_particles[i]);
    }

    m_Window.display();
}

