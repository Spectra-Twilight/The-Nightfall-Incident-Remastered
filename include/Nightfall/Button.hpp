#ifndef NIGHTFALL_BUTTON_HPP
#define NIGHTFALL_BUTTON_HPP

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace nightfall
{
    class Button
    {   //================================================================================================================================================
        protected:

        sf::Vector2f topLeft; // Position of the top-leftmost pixel.
        sf::Vector2f bottomRight; // Position one-pixel beyond the bottom-rightmost pixel in both dimensions.

        bool pressed; // Button is currently being pressed by mouse1, but mouse1 has yet to be released.
        bool clicked; // The button was pressed then subsequently released by mouse1.

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Determines whether or not the mouse cursor is within this object.

            Parameter:
            *   event: A mouse button event (press or release).
            
            Returns: True if the mouse cursor was within this object at the time of the event, or false otherwise.
        */
        bool hasMouseCursor(const sf::Event& event);

        //================================================================================================================================================
        public:

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Default constructor.
        */
        inline Button(): topLeft(0, 0), bottomRight(1, 1), pressed(false), clicked(false) {}

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Returns the position of the top-leftmost pixel of this object.

            Returns: The position of this object.
        */
        inline sf::Vector2f getPosition() { return topLeft; }

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Returns the size, in pixels, of this object.

            Returns: The size of this object.
        */
        inline sf::Vector2f getSize() { return (bottomRight - topLeft); }

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Returns whether or not this object is marked as having been clicked.

            Returns: The clicked status of this object.
        */
        inline bool isClicked() { return clicked; }

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Returns the pressed status of this object.

            Returns: The pressed status of this object.
        */
        inline bool isPressed() { return pressed; }

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Takes a mouse button press event, determines if it is intended for this object, 
            appropriately updates its internal state if necessary, then returns true if the 
            mouse button press took place within this object's bounds, or false otherwise.

            If the argument event data is not that of a mouse button press, then the behavior 
            of this function is undefined.

            Parameter:
            *   event: The mouse button press event data.
            
            Returns: True if the mouse button press was on this object, or false otherwise.
        */
        bool onMouseButtonPressed(const sf::Event& event);

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Takes a mouse button release event, determines if it was intended for this object, 
            appropriately updates its internal state if necessary, then returns true if the 
            mouse button release took place within this object's bounds, or false otherwise.

            If the argument event data is not that of a mouse button release, then the behavior 
            of this function is undefined.

            Parameter:
            *   event: The mouse button release event data.
            
            Returns: True if the mouse button release was on this object, or false otherwise.
        */
        bool onMouseButtonReleased(const sf::Event& event);

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Sets a new position on the render target for this object, with the 
            argument position becoming the new position of the top-leftmost pixel of 
            this object.

            Parameter:
            *   newPos: The new position for this object.
        */
        void setPosition(const sf::Vector2f& newPos);

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Sets the size of the object, which determines the area in which it will claim 
            ownership of mouse button events.

            Parameter:
            *   newSize: The new size for this object.
        */
        inline void setSize(const sf::Vector2f newSize) { bottomRight = topLeft + newSize; }

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Removes clicked status from this object.
        */
        inline void unclick() { clicked = false; }

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Removes pressed status from this object.
        */
        inline void unpress() { pressed = false; }

    };  //================================================================================================================================================
}

#endif // NIGHTFALL_BUTTON_HPP