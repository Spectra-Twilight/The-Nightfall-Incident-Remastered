#ifndef NIGHTFALL_SECTOR_HPP
#define NIGHTFALL_SECTOR_HPP

#include <cstdint>
#include <string>

#include <SFML/Graphics.hpp>

#include <Nightfall/Program.hpp>

namespace nightfall
{
	class Sector: public sf::Drawable
	{
	public:
		////////////////////////////////////////////////////////////////////////
		/// \brief Constructs a Sector with the default sector texture.
		///
		/// \param active Whether or not this Sector is active, and therefore 
		///		visible and enterable by Programs. Defaults to true.
		////////////////////////////////////////////////////////////////////////
		Sector(bool active = true): Sector(_default_sector_texture, active) {}

		////////////////////////////////////////////////////////////////////////
		/// \brief Constructs a Sector using the provided texture.
		///
		/// \param texture The texture to be used for the sector's main sprite.
		/// \param active Whether or not this Sector is active, and therefore 
		///		visible and enterable by Programs. Defaults to true.
		////////////////////////////////////////////////////////////////////////
		Sector(const sf::Texture& texture, bool active = true);

		////////////////////////////////////////////////////////////////////////
		/// \brief Returns whether or not this Sector is currently active.
		///
		/// An active sector has its sector graphic drawn (if unoccupied), and 
		/// can contain an occupant Program. Conversely, an inactive sector is 
		/// not drawn and cannot be entered by Programs.
		///
		/// \return True if this Sector is active, or false otherwise.
		////////////////////////////////////////////////////////////////////////
		bool active() const;

		////////////////////////////////////////////////////////////////////////
		/// \brief Sets the active state of the Sector.
		///
		/// An active Sector will have its graphic drawn (if unoccupied),
		/// and can be occupied by a Program. Conversely, an inactive Sector 
		/// is not drawn and cannot be entered by Programs.
		///
		/// \param active The new active state of the Sector.
		///		True indicates being active. False indicates being inactive.
		////////////////////////////////////////////////////////////////////////
		void active(bool active);

		////////////////////////////////////////////////////////////////////////
		/// \brief Draws the Sector to the specified RenderTarget.
		///
		///	\param target Render target to draw to.
		/// \param states Current render states.
		////////////////////////////////////////////////////////////////////////
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		////////////////////////////////////////////////////////////////////////
		/// \brief Sets whether a link from this Sector to the Sector below is drawn.
		///
		/// A Sector lacks knowledge of adjacent Sectors, so the owner of the 
		/// Sector may set this value to specify how the Sector appears when 
		/// it is drawn.
		///
		/// \param link_down True if the downward link should be drawn, false otherwise.
		////////////////////////////////////////////////////////////////////////
		void link_down(bool link_down);

		////////////////////////////////////////////////////////////////////////
		/// \brief Sets whether a link from this Sector to the Sector to the right is drawn.
		///
		/// A Sector lacks knowledge of adjacent Sectors, so the owner of the 
		/// Sector may set this value to specify how the Sector appears when 
		/// it is drawn.
		///
		/// \param link_right True if the rightward link should be drawn, false otherwise.
		////////////////////////////////////////////////////////////////////////
		void link_right(bool link_right);

		////////////////////////////////////////////////////////////////////////
		/// \brief Loads the default sector texture into memory.
		///
		/// The path of the graphic is hard-coded. This function exists to 
		/// provide control of when that graphic is loaded into memory.
		///
		/// This function should be called before any Sectors are created.
		///
		/// \return True if the texture was successfully loaded, or false otherwise.
		////////////////////////////////////////////////////////////////////////
		static bool load_default_sector_gfx();

		////////////////////////////////////////////////////////////////////////
		/// \brief Returns a pointer to the program occupying this Sector, if any.
		///
		/// If no Program is occupying this Sector when this function is called, 
		/// then this function will return a nullptr.
		///
		/// \return The Program occupying this Sector, or nullptr.
		////////////////////////////////////////////////////////////////////////
		const Program* occupant() const;

		////////////////////////////////////////////////////////////////////////
		/// \brief Assigns a new occupant Program to this Sector.
		///
		/// An argument of nullptr will clear any occupant from the Sector.
		///
		/// \param occupant The new Program occupying the Sector, or nullptr.
		////////////////////////////////////////////////////////////////////////
		void occupant(const Program* occupant);

		////////////////////////////////////////////////////////////////////////
		/// \brief Returns the position of this Sector.
		///
		/// The returned position is representative of the offset of the 
		/// top-leftmost pixel of this Sector from the top-leftmost pixel of 
		/// a RenderTarget.
		///
		/// \return The position of this Sector.
		////////////////////////////////////////////////////////////////////////
		const sf::Vector2f& position() const;

		////////////////////////////////////////////////////////////////////////
		/// \brief Moves the Sector to the new position.
		///
		/// The provided coordinates represent the offset of the top-leftmost 
		/// pixel of the Sector from the top-leftmost pixel of the RenderTarget.
		///
		/// \param pos The offset, in pixels, from the top-leftmost corner of the RenderTarget.
		////////////////////////////////////////////////////////////////////////
		void position(const sf::Vector2f& pos);

		////////////////////////////////////////////////////////////////////////
		/// \brief Moves the Sector to the new position.
		///
		/// The provided coordinates represent the offset of the top-leftmost 
		/// pixel of the Sector from the top-leftmost pixel of the RenderTarget.
		///
		/// \param x The offset, in pixels, from the left edge of the RenderTarget.
		/// \param y The offset, in pixels, from the top edge of the RenderTarget.
		////////////////////////////////////////////////////////////////////////
		void position(float x, float y);

		////////////////////////////////////////////////////////////////////////
		/// \brief Returns the length of one side of a Sector, in pixels.
		///
		/// All sectors share the same base size value, and all sectors are 
		/// squares. Therefore, the value returned by a call to this method 
		/// will accurately reflect the length of any Sector side.
		///
		/// \return The length of one side of a Sector, to which all Sectors adhere to, in pixels.
		////////////////////////////////////////////////////////////////////////
		static uint8_t side_length();

		////////////////////////////////////////////////////////////////////////
		/// \brief Returns the size of this Sector, in pixels.
		///
		/// \return The size of this Sector, in pixels.
		////////////////////////////////////////////////////////////////////////
		sf::Vector2u size() const;
	
	private:
		////////////////////////////////////////////////////////////////////////
		/// Constant Data
		////////////////////////////////////////////////////////////////////////
		static constexpr int8_t _link_offset = -6; ///< Offset, in pixels, to shift the link sprite into its parent's sprite to 
		static constexpr float _link_scale = 1.0f / 3.0f; ///< Size of a link sprite relative to standard sector sprite size.
		static constexpr int8_t _program_pos_offset = -1; ///< Offset, in pixels, for the x and y coordinates of the graphics of a program occupying this Sector.
		static constexpr uint8_t _side_length = 28; ///< Length of one side of a Sector, measured in pixels.
		static const sf::Color _color; ///< Color of a sector.

		////////////////////////////////////////////////////////////////////////
		/// Static Data
		////////////////////////////////////////////////////////////////////////
		static sf::Texture _default_sector_texture; ///< Default sector texture if none is specified.
		static sf::Texture _program_texture; ///< Texture used for all Programs.

		////////////////////////////////////////////////////////////////////////
		/// Member State Data
		////////////////////////////////////////////////////////////////////////
		const Program* _occupant; ///< The Program currently occupying this Sector.
		bool _active; ///< Sector is invisible and not enterable if inactive.
		bool _link_down; ///< Should link_down_gfx be drawn?
		bool _link_right; ///< Should link_right_gfx be drawn?

		////////////////////////////////////////////////////////////////////////
		/// Member Sprites
		////////////////////////////////////////////////////////////////////////
		sf::Sprite _sector_gfx; ///< Sector sprite when unoccupied.
		sf::Sprite _program_gfx; ///< Sector sprite when occupied.
		sf::Sprite _link_right_gfx; ///< Sprite of the link to the sector immediately right of this one. Visible if the sectors share the same program.
		sf::Sprite _link_down_gfx; ///< Sprite of the link to the sector immediately below this one. Visible if the sectors share the same program.
	}; // class Sector
} // namespace nightfall

#endif // NIGHTFALL_SECTOR_HPP