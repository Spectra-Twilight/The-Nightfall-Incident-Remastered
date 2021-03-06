#ifndef NIGHTFALL_GAME_HPP
#define NIGHTFALL_GAME_HPP

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Nightfall/Command.hpp>
#include <Nightfall/Level.hpp>
#include <Nightfall/Program_Factory.hpp>

#include <Trie/trie.hpp>

namespace nf
{
    class Game: public sf::Drawable
    {   //============================================================================================================================================
        private:

        // Loaded data, retrievable via the use of IDs.
        trie<std::unique_ptr<Command> > commands;
        trie<std::unique_ptr<Program::Factory> > programs;

        enum class State
        {
            level
        };
        State state; // The state of the Game, determining what members to apply logical input to.

        Level level;

        //============================================================================================================================================
        public:

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Default constructor.
        */
        inline Game(): state(State::level) {}

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Draw the object to the render target.

            Inherited from sf::Drawable

            Parameters:
            *   target: Render target to draw to.
            *   states: Current render states.
        */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Notifies the Game of a mouse button press, which it then parses and 
            potentially acts upon.

            Parameter:
            *   event: The mouse button event data.
        */
        void onMouseButtonPressed(const sf::Event& event);

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Notifies the object of a mouse button release, which it then parses 
            and potentially acts upon.

            Parameter:
            *   event: The mouse button event data.
        */
        void onMouseButtonReleased(const sf::Event& event);
        
    };  //============================================================================================================================================
}

#endif // NIGHTFALL_GAME_HPP