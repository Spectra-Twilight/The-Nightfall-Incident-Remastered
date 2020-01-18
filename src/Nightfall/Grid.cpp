////////////////////////////////////////////////////////////////////////////////
/// Nightfall Includes
////////////////////////////////////////////////////////////////////////////////
#include <Nightfall/Grid.hpp>

namespace nightfall
{
    ////////////////////////////////////////////////////////////////////////////
    void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (const auto& row : _sectors)
        {
            for (const Sector& sector : row)
                target.draw(sector);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    const sf::Vector2f& Grid::position() const
    {
        return _sectors[0][0].position();
    }

    ////////////////////////////////////////////////////////////////////////////
    void Grid::position(sf::Vector2f pos)
    {
        const uint8_t offset_increment(Sector::side_length() + _sector_gap);
        sf::Vector2f offset(pos);

        // Reposition all Sectors of the Grid to respect the new offset position.
        for (auto& row : _sectors)
        {
            offset.x = pos.x;

            for (Sector& sector : row)
            {
                sector.position(offset);
                offset.x += offset_increment;
            }

            offset.y += offset_increment;
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    void Grid::position(float x, float y)
    {
        position(sf::Vector2f(x, y));
    }
} // namespace nightfall