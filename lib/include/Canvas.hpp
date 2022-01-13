#pragma once

#include <SFML/Graphics.hpp>

#include "GameState.hpp"
#include "Position.hpp"
#include <optional>
#include <span>

namespace ms_pacman {

using Rect = sf::Rect<int>;
using Sprite = sf::Sprite;

class Canvas {
public:
  Canvas();
  void loadMaze(std::string_view path);
  void render(const GameState & gameState);
  std::optional<sf::Event> pollEvent();

private:
  static constexpr uint16_t LEFT_MARGIN = 40 * 2;
  static constexpr uint16_t TOP_MARGIN = 40 * 2;
  static constexpr uint16_t BOTTOM_MARGIN = 40 * 2;
  static constexpr uint16_t MAZE_WIDTH = 448;
  static constexpr uint16_t MAZE_HEIGHT = 496;
  static constexpr uint16_t MAZE_SCALE_UP = 2;
  static constexpr uint16_t TARGET_MAZE_WIDTH = 448 * MAZE_SCALE_UP;
  static constexpr uint16_t TARGET_MAZE_HEIGHT = 496 * MAZE_SCALE_UP;
  static constexpr uint16_t SCORE_WIDTH = 200 * 2;
  static constexpr uint16_t SPRITE_WIDTH = 32;
  static constexpr uint16_t SPRITE_HEIGHT = 32;

  void clear();
  void render();
  void renderMaze();
  void renderGhosts(const Ghosts & ghosts);
  void renderPacMan(const MsPacMan & pac_man);
  void renderGhost(const Ghost & ghost);
  void renderPellets(const DefaultBoard & board);

  void renderFruits(const GenericFruit & fruit, std::span<const GenericFruit> eatenFruits) {
    Sprite sprite = getSprite(Fruits::sprite(fruit));
    if (Fruits::isVisible(fruit)) {
      const auto & pos = Fruits::position(fruit);
      renderObject(sprite, pos);
    }

    auto render_fruit = [this](int position, Sprite fruit_sprite) {
      const auto x = static_cast<size_t>(LEFT_MARGIN + TARGET_MAZE_WIDTH + LEFT_MARGIN);
      const auto y = static_cast<size_t>((TARGET_MAZE_HEIGHT / 3.0) * 2);
      const auto sprite_position = float(position) * SPRITE_WIDTH * 1.5f;
      const sf::Vector2f pos{ x + sprite_position, y };
      fruit_sprite.setPosition(pos.x, pos.y);
      window.draw(fruit_sprite);
    };

    int position = 0;
    for (const auto & eatenFruit : eatenFruits) {
      GridPosition current_sprite = std::visit([](auto && fruit) { return fruit.sprite(); }, eatenFruit);
      Sprite eaten_sprite = getSprite(current_sprite);
      render_fruit(position, eaten_sprite);
      position++;
    }

    render_fruit(position, sprite);
  }

  void renderScore(int score);
  void renderLives(int lives);

  template<typename Object>
  void renderObject(Object sprite, Position pos) {
    pos.x = 12 + LEFT_MARGIN + (pos.x * SPRITE_WIDTH);
    pos.y = 12 + TOP_MARGIN + (pos.y * SPRITE_HEIGHT);
    sprite.setPosition(float(pos.x), float(pos.y));
    window.draw(sprite);
  }

  static Rect viewDimensions();
  static sf::Texture loadTexture(std::string_view path);
  static sf::Font loadFont(std::string_view path);

  Sprite getSprite(GridPosition rect) const;

  sf::RenderWindow window;
  sf::View view;
  sf::Texture maze_texture;
  sf::Texture sprites_texture;
  sf::Font game_font;
};

} // namespace ms_pacman
