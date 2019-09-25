#ifndef SPYBOT_LEVEL_HPP
#define SPYBOT_LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Spybot/Grid.hpp>

namespace Spybot
{
    class Level: public sf::Drawable
    {   //=====================================================================================================================================================
        private:

        Grid grid;

        //=====================================================================================================================================================
        public:

        /*------------------------------------------------------------------------------------------------------------------------------------------
            Draw the object to the render target.

            Inherited from sf::Drawable

            Parameters:
            *   target: Render target to draw to.
            *   states: Current render states.
        */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        /*-----------------------------------------------------------------------------------------------------------------------------------------------------
            Notifies the object of a mouse button press, which it then parses to 
            determine the appropriate response.

            Parameter:
            *   event: The mouse button event.
        */
        void onMouseButtonPressed(const sf::Event& event);

        /*-----------------------------------------------------------------------------------------------------------------------------------------------------
            Notifies the object of a mouse button release, which it then reacts to 
            appropriately.

            Parameter:
            *   event: The mouse button event.
        */
        void onMouseButtonReleased(const sf::Event& event);

    };  //=====================================================================================================================================================
}

#endif // SPYBOT_LEVEL_HPP