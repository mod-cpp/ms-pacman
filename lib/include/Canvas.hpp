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
  void renderWindow();
  void renderMaze();
  void render(const Ghosts & ghosts);
  void render(const MsPacMan & pac_man);
  void render(const Score & score);
  void renderGameOver();
  void renderReady();

  template<typename Ghost>
  void renderGhost(const Ghost & ghost) {
    Sprite sprite = getSprite(ghost.currentSprite());
    const auto & pos = ghost.position();
    render(sprite, pos);
  }

  void renderPellets(const DefaultBoard & board);

  void render(const GenericFruit & fruit, std::span<const GenericFruit> eatenFruits);

  void renderScore(int score);
  void renderLives(int lives);

  template<typename Object>
  void render(Object sprite, Position pos) {
    pos.x = LEFT_MARGIN + (pos.x * SPRITE_WIDTH);
    pos.y = TOP_MARGIN + (pos.y * SPRITE_HEIGHT);
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
