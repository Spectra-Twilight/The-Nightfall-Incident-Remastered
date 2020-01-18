#include <Nightfall/Sector.hpp>

#include <stdexcept>

#include <Log.hpp>

using namespace std;

namespace nightfall 
{
    ////////////////////////////////////////////////////////////////////////////
    /// Static Member Initialization
    ////////////////////////////////////////////////////////////////////////////
    const sf::Color Sector::_color = sf::Color(255, 255, 255, 64);
    const string Sector::_default_gfx_dir = "data/gfx/sectors/default.png";
    sf::Texture Sector::_default_gfx;
    uint16_t Sector::_side_length(_base_side_length);

    ////////////////////////////////////////////////////////////////////////////
    Sector::Sector(const sf::Texture& texture, bool active):
        _occupant(nullptr),
        _active(active),
        _link_right(false),
        _link_down(false)
    {
        _sector_gfx.setTexture(texture);
        _sector_gfx.setColor(_color);

        const sf::Texture& program_texture = Program::getBaseGfx();
        _program_gfx.setTexture(program_texture);

        _link_right_gfx.setTexture(program_texture);
        _link_right_gfx.setScale(_link_scale, _link_scale);

        _link_down_gfx.setTexture(program_texture);
        _link_down_gfx.setScale(_link_scale, _link_scale);
    }

    ////////////////////////////////////////////////////////////////////////////
    bool Sector::active() const
    {
        return _active;
    }

    ////////////////////////////////////////////////////////////////////////////
    void Sector::active(bool active)
    {
        _active = active;
    }

    ////////////////////////////////////////////////////////////////////////////
    void Sector::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (_active)
        {
            if (_occupant)
            {
                target.draw(_program_gfx);

                if (_link_right)
                    target.draw(_link_right_gfx);
                if (_link_down)
                    target.draw(_link_down_gfx);
            }
            else
                target.draw(_sector_gfx);
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    void Sector::link_down(bool link_down)
    {
        _link_down = link_down;
    }

    ////////////////////////////////////////////////////////////////////////////
    void Sector::link_right(bool link_right)
    {
        _link_right = link_right;
    }

    ////////////////////////////////////////////////////////////////////////////
    bool Sector::load_default_sector_gfx()
    {
        return _default_gfx.loadFromFile(_default_gfx_dir);
    }

    ////////////////////////////////////////////////////////////////////////////
    const Program* Sector::occupant() const
    {
        return _occupant;
    }

    ////////////////////////////////////////////////////////////////////////////
    void Sector::occupant(const Program* occupant)
    {
        _occupant = occupant;

        const sf::Color& occupant_color = occupant->getColor();
        _program_gfx.setColor(occupant_color);
        _link_down_gfx.setColor(occupant_color);
        _link_right_gfx.setColor(occupant_color);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    const sf::Vector2f& Sector::position() const
    {
        if (!_occupant)
            return _sector_gfx.getPosition();
        else
            return _program_gfx.getPosition();
    }

    ////////////////////////////////////////////////////////////////////////////
    void Sector::position(const sf::Vector2f& pos)
    {
        _sector_gfx.setPosition(pos);

        // Establish position of occupant program.
        sf::Vector2f offset_pos(pos);
        offset_pos.x += _program_pos_offset;
        offset_pos.y += _program_pos_offset;
        _program_gfx.setPosition(pos);

        const sf::Vector2u gfx_size(_program_gfx.getTexture()->getSize());

        // Establish position of down link.
        offset_pos = pos;
        offset_pos.y += gfx_size.y - Program::baseGfxEdge;
        offset_pos.x += gfx_size.x * _link_scale;
        _link_down_gfx.setPosition(offset_pos);

        // Establish position of right link.
        offset_pos = pos;
        offset_pos.x += gfx_size.x - Program::baseGfxEdge;
        offset_pos.y += gfx_size.y * _link_scale;
        _link_right_gfx.setPosition(offset_pos);
    }

    ////////////////////////////////////////////////////////////////////////////
    void Sector::position(float x, float y)
    {
        position(sf::Vector2f(x, y));
    }

    ////////////////////////////////////////////////////////////////////////////
    sf::Vector2u Sector::size() const
    {
        sf::Vector2u size;
        sf::Vector2f scale;

        if (!_occupant)
        {
            size = _sector_gfx.getTexture()->getSize();
            scale = _sector_gfx.getScale();
        }
        else
        {
            size = _program_gfx.getTexture()->getSize();
            scale = _program_gfx.getScale();
        }

        size.x *= scale.x;
        size.y *= scale.y;
        return size;
    }

} // namespace nightfall