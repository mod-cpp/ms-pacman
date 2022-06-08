#pragma once

#include "GameState.hpp"
#include "Position.hpp"

#include <concepts>
#include <optional>
#include <span>

#include <SFML/Graphics.hpp>

namespace ms_pacman {

using Rect = sf::Rect<int>;
using Sprite = sf::Sprite;

template<typename T>
concept has_position =
  requires(const T & const_object) {
    { const_object.position() } -> std::same_as<Position>;
  };

template<typename T>
concept is_sprite =
  requires(const T & const_object) {
    { const_object.currentSprite() };
  };

template<typename T>
concept positioned_sprite = has_position<T> && is_sprite<T>;

template<typename T>
concept has_set_position =
  requires(T & object, float f) {
  { object.setPosition(f, f) };
};

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
  static constexpr uint16_t SCORE_WIDTH = 700;
  static constexpr uint16_t SPRITE_WIDTH = 32;
  static constexpr uint16_t SPRITE_HEIGHT = 32;

  void clear();
  void renderWindow();
  void renderMaze();
  void renderGameOver();
  void renderReady();

  void render(const Ghosts & ghosts);
  void render(const Score & score);

  template<positioned_sprite T>
  void render(const T & object) {
    Sprite sprite = getSprite(object.currentSprite());
    const auto & pos = object.position();
    render(sprite, pos);
  }

  void render(const DefaultBoard & board);

  void render(const GenericFruit & fruit, std::span<const GenericFruit> eatenFruits);

  void renderScore(int score);
  void renderHighScore(std::optional<player> score);
  void renderLives(uint16_t lives);

  template<has_set_position Object>
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

  static consteval uint16_t panelLeft() {
    return LEFT_MARGIN + TARGET_MAZE_WIDTH + LEFT_MARGIN;
  }

  static consteval float spritePaddedWidth() {
    return SPRITE_WIDTH * 1.5f;
  }

  static constexpr BasicPosition<float>
  calculatePanelSpritePosition(BasicPosition<uint16_t> grid_pos) {
    float x = panelLeft();
    float y = grid_pos.y;
    float sprite_position = float(grid_pos.x) * spritePaddedWidth();
    return { x + sprite_position, y };
  }

  sf::RenderWindow window;
  sf::View view;
  sf::Texture maze_texture;
  sf::Texture sprites_texture;
  sf::Font game_font;
};

} // namespace ms_pacman
