#include "Canvas.hpp"
#include "Scaling.hpp"
#include <fmt/format.h>
#include <string>
#include <vector>

namespace ms_pacman {

sf::ContextSettings settings{ 0, 0, 8 };

Canvas::Canvas()
  : window(sf::VideoMode(std::uint32_t(viewDimensions().width / 2), std::uint32_t(viewDimensions().height / 2)),
           "MsPacMan",
           sf::Style::Titlebar | sf::Style::Close,
           settings),
    view(sf::FloatRect(0, 0, float(viewDimensions().width), float(viewDimensions().height))) {

  window.setView(view);
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  // We render the game in view at twice the native resolution,
  // Then project it on a scaled window - on some mac we get the
  // scaling factor of the window to adjust the resolution
  const auto scale = scaling_factor_for_window(window.getSystemHandle());
  const auto width = (viewDimensions().width / 2.0) * scale;
  const auto height = (viewDimensions().height / 2.0) * scale;
  window.setSize(sf::Vector2u(unsigned(width), unsigned(height)));

  sprites_texture = loadTexture("sprites-ms-32.png");
  game_font = loadFont("retro_font.ttf");
}

void Canvas::loadMaze(std::string_view path) {
  maze_texture = loadTexture(path);
}

void Canvas::render(const GameState & gameState) {
  clear();

  renderMaze();
  render(gameState.board);
  render(gameState.ghosts);
  render(gameState.score);
  renderHighScore(gameState.highScore.top());
  render(gameState.fruits[gameState.fruitIndex()], gameState.score.eatenFruits);
  render(gameState.msPacMan);

  if (gameState.score.lives == DEFAULT_LIVES && gameState.msPacMan.currentDirection() == Direction::NONE) {
    renderReady();
  }

  renderWindow();
}

std::optional<sf::Event> Canvas::pollEvent() {
  sf::Event event{};
  if (window.pollEvent(event))
    return event;
  return std::nullopt;
}

void Canvas::clear() {
  window.clear(sf::Color::Black);
}

void Canvas::renderWindow() {
  window.display();
}

void Canvas::renderMaze() {
  Sprite maze;
  maze.setTexture(maze_texture);
  maze.setTextureRect(sf::IntRect{
    0,
    0,
    MAZE_WIDTH,
    MAZE_HEIGHT });
  maze.setScale(MAZE_SCALE_UP, MAZE_SCALE_UP);
  maze.setPosition(LEFT_MARGIN, TOP_MARGIN);
  window.draw(maze);
}

void Canvas::renderGameOver() {
  const int x = (LEFT_MARGIN + TARGET_MAZE_WIDTH / 2);
  const int y = (TOP_MARGIN + TARGET_MAZE_HEIGHT / 2 + 50);

  sf::Text text;
  text.setPosition(x, y);
  text.setFont(game_font);
  text.setString(fmt::format("GAME OVER!"));
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::Red);
  text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
  window.draw(text);
}

void Canvas::renderReady() {
  const int x = (LEFT_MARGIN + TARGET_MAZE_WIDTH / 2);
  const int y = (TOP_MARGIN + TARGET_MAZE_HEIGHT / 2 + 50);

  sf::Text text;
  text.setPosition(x, y);
  text.setFont(game_font);
  text.setString(fmt::format("Ready!"));
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::Yellow);
  text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
  window.draw(text);
}

void Canvas::render(const Ghosts & ghosts) {
  auto render_ghosts = [this](const auto &... ghost) { (render(ghost), ...); };
  std::apply(render_ghosts, ghosts);
}

void Canvas::render(const DefaultBoard & board) {
  for (std::size_t x = 0; x < COLUMNS; x++) {
    for (std::size_t y = 0; y < ROWS; y++) {
      const BoardCell & cell = board[y][x];
      const Position renderPos = { double(x) + 0.5, double(y) + 0.5 };
      std::visit(overloaded{
                   [&](const Pellet &) {
                     sf::CircleShape shape(4);
                     shape.setFillColor(sf::Color(230, 230, 230));
                     shape.setOrigin(shape.getRadius(), shape.getRadius());
                     render(shape, renderPos);
                   },
                   [&](const SuperPellet &) {
                     sf::CircleShape shape(8);
                     shape.setFillColor(sf::Color(250, 250, 250));
                     shape.setOrigin(shape.getRadius(), shape.getRadius());
                     render(shape, renderPos);
                   },
                   [&](const auto &) {
                   } },
                 cell);
    }
  }
}

void Canvas::render(const GenericFruit & fruit, std::span<const GenericFruit> eatenFruits) {
  Sprite level_fruit_sprite = getSprite(Fruits::sprite(fruit));

  // Render the current fruit in the maze
  if (Fruits::isVisible(fruit)) {
    const auto & pos = Fruits::position(fruit);
    render(level_fruit_sprite, pos);
  }

  auto render_fruit = [this](uint16_t horizontal_position, Sprite fruit_sprite) {
    auto vertical_position = static_cast<uint16_t>((TARGET_MAZE_HEIGHT / 3.0) * 2);
    auto panel_pos = calculatePanelSpritePosition({ horizontal_position, vertical_position });
    fruit_sprite.setPosition(panel_pos.x, panel_pos.y);
    window.draw(fruit_sprite);
  };

  uint16_t horizontal_position = 0;

  // Render the already eaten fruits in the list in the panel
  for (const auto & eatenFruit : eatenFruits) {
    GridPosition sprite_position = Fruits::sprite(eatenFruit);
    Sprite eaten_sprite = getSprite(sprite_position);
    render_fruit(horizontal_position, eaten_sprite);
    horizontal_position++;
  }

  // Render the current fruit at the end of the list in the panel
  render_fruit(horizontal_position, level_fruit_sprite);
}

void Canvas::render(const Score & score) {
  renderScore(score.points);
  renderLives(score.lives);

  if (score.lives == 0) {
    renderGameOver();
  }
}

void Canvas::renderScore(int score) {
  const auto x = panelLeft();
  const auto y = (TOP_MARGIN * 2);

  sf::Text text;
  text.setPosition(x, y);
  text.setFont(game_font);
  text.setString(fmt::format("SCORE\n{}", score));
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::White);
  window.draw(text);
}

void Canvas::renderHighScore(std::optional<player> highScore) {
  if (!highScore)
    return;

  const auto x = panelLeft();
  const auto y = (TOP_MARGIN * 2) + 150;

  sf::Text text;
  text.setPosition(x, y);
  text.setFont(game_font);
  text.setString(fmt::format("HIGH SCORE\n{}\n{}", highScore->score, highScore->name));
  text.setCharacterSize(30);
  text.setFillColor(sf::Color::White);
  window.draw(text);
}

void Canvas::renderLives(uint16_t lives) {
  constexpr GridPosition liveSprite = Atlas::pacman_left_narrow;
  Sprite pacmanSprite = getSprite(liveSprite);
  for (uint16_t horizontal_position = 0; horizontal_position < lives - 1; horizontal_position++) {
    auto panel_pos = calculatePanelSpritePosition({ horizontal_position, TARGET_MAZE_HEIGHT });
    pacmanSprite.setPosition(panel_pos.x, panel_pos.y);
    window.draw(pacmanSprite);
  }
}

Rect Canvas::viewDimensions() {
  const double width = (LEFT_MARGIN + TARGET_MAZE_WIDTH + SCORE_WIDTH);
  const double height = (TOP_MARGIN + TARGET_MAZE_HEIGHT + BOTTOM_MARGIN);
  return { 0, 0, int(width), int(height) };
}

Sprite Canvas::getSprite(GridPosition coordinate) const {
  sf::Sprite sprite;
  sprite.setTexture(sprites_texture);
  sprite.setTextureRect(sf::IntRect{ int(coordinate.x * SPRITE_WIDTH),
                                     int(coordinate.y * SPRITE_HEIGHT),
                                     SPRITE_WIDTH,
                                     SPRITE_HEIGHT });
  return sprite;
}

static void exitFailure(std::string_view message) {
  fmt::print("{}\n", message);
  exit(1);
}

sf::Texture Canvas::loadTexture(std::string_view path) {
  sf::Texture texture;
  if (!texture.loadFromFile(std::string{ path })) {
    exitFailure(fmt::format("Failed to load image {}", path));
  }
  return texture;
}

sf::Font Canvas::loadFont(std::string_view path) {
  sf::Font font;
  if (!font.loadFromFile(std::string{ path })) {
    exitFailure(fmt::format("Failed to load font {}", path));
  }
  return font;
}

} // namespace ms_pacman
