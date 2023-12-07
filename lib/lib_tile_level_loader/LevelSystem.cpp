#include "LevelSystem.h"
#include "json.hpp"
#include <fstream>

using namespace std;
using namespace sf;


std::map<LevelSystem::Tile, sf::Color> LevelSystem::_colours{
	{WALL, Color::White}, {END, Color::Red}, {FLOOR, Color::Magenta}, {START, Color::Green } };

sf::Color LevelSystem::getColor(LevelSystem::Tile t) {
	auto it = _colours.find(t);
	if (it == _colours.end()) {
		_colours[t] = Color::Transparent;
	}
	return _colours[t];
}

void LevelSystem::setColor(LevelSystem::Tile t, sf::Color c) {
	_colours[t] = c;
}

std::unique_ptr<LevelSystem::Tile[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;
std::vector<int> LevelSystem::_map;
int LevelSystem::_columns;

float LevelSystem::_tileSize(100.f);
Vector2f LevelSystem::_offset(0.0f, 0.0f);
// Vector2f LevelSystem::_offset(0,0);
vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;

sf::Texture LevelSystem::tilesTexture;

void LevelSystem::setTextureMap(string path) {
	tilesTexture.loadFromFile(path);
}

void LevelSystem::loadLevelFile(const std::string& path, float tileSize) {
	_tileSize = 70;
	size_t w = 0, h = 0;
	string buffer;

//	// Load in file to buffer
//	ifstream f(path);
//	if (f.good()) {
//		f.seekg(0, std::ios::end);
//		buffer.resize(f.tellg());
//		f.seekg(0);
//		f.read(&buffer[0], buffer.size());
//		f.close();
//	}
//	else {
//		throw string("Couldn't open level file: ") + path;
//	}
//
//	std::vector<Tile> temp_tiles;
//	int widthCheck = 0;
//	for (int i = 0; i < buffer.size(); ++i) {
//		const char c = buffer[i];
//		if (c == '\0') { break; }
//		if (c == '\n') { // newline
//			if (w == 0) {  // if we haven't written width yet
//				w = i;       // set width
//			}
//			else if (w != (widthCheck - 1)) {
//				throw string("non uniform width:" + to_string(h) + " ") + path;
//			}
//			widthCheck = 0;
//			h++; // increment height
//		}
//		else {
//			temp_tiles.push_back((Tile)c);
//		}
//		++widthCheck;
//	}
//
//	if (temp_tiles.size() != (w * h)) {
//		throw string("Can't parse level file") + path;
//	}
    std::ifstream json("res/levels/levelOne.json");
    nlohmann::json file = nlohmann::json::parse(json);

    _map = file.at("layers")[0].at("data").get<vector<int>>();


	_width = file.at("layers")[0].at("width"); // set static class vars
	_height = file.at("layers")[0].at("height");
    _columns = file.at("tilesets")[0].at("columns");
    _tiles = std::make_unique<Tile[]>(_width * _height);
//    _columns--;
//	std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
	cout << "Level " << path << " Loaded. " << _width << "x" << _height << std::endl;
//    json.close();
	buildSprites();
}

void LevelSystem::buildSprites(bool optimise) {
	_sprites.clear();

    tilesTexture.loadFromFile("res/assets/Base pack/Tiles/tiles_spritesheet.png");

    for (int i = 0; i < _width*_height; ++i) {
        auto sprite = make_unique<sf::RectangleShape>();
        int id = _map[i] - 1;
        if (id < 0){
            continue;
        }
        int x = (id % _columns);
        int y = (id / _columns);

        auto r = sf::IntRect {
                static_cast<int>(x*(_tileSize+2)),
                static_cast<int>(y*(_tileSize+2)),
                static_cast<int>(_tileSize),
                static_cast<int>(_tileSize)};

        sprite->setTexture(&tilesTexture);
        sprite->setTextureRect(r);
        sprite->setSize({70,70});

        auto pos = getTilePosition(Vector2ul {i%_width,i/_width});
        sprite->setPosition(pos);

        _sprites.push_back(std::move(sprite));
    }
}

void LevelSystem::render(RenderWindow& window) {
	for (auto& t : _sprites) {
		window.draw(*t);
	}
}

void LevelSystem::renderFloor(RenderWindow& window) {
	// Renders tiles from the level file only if they are on the screen.
	View view = window.getView();
	auto res = view.getSize();
	auto center = view.getCenter();

	for (auto& t : _sprites) {
		if (t->getPosition().x < center.x - (res.x * 0.6) || t->getPosition().x >= center.x + (res.x * 0.6)) {
			continue;
		}
		if (t->getPosition().y < center.y - (res.y * 0.65) || t->getPosition().y >= center.y + (res.y * 0.5)) {
			continue;
		}
		else {
			window.draw(*t);
		}
	}
}

LevelSystem::Tile LevelSystem::getTile(sf::Vector2ul p) {
	if (p.x > _width || p.y > _height) {
		throw string("Tile out of range: ") + to_string(p.x) + "," +
			to_string(p.y) + ")";
	}
	return _tiles[(p.y * _width) + p.x];
}

size_t LevelSystem::getWidth() { return _width; }

size_t LevelSystem::getHeight() { return _height; }

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul p) {
	return (Vector2f(p.x, p.y) * _tileSize) + _offset;
}

std::vector<sf::Vector2ul> LevelSystem::findTiles(LevelSystem::Tile type) {
	auto v = vector<sf::Vector2ul>();
	for (size_t i = 0; i < _width * _height; ++i) {
		if (_tiles[i] == type) {
			v.push_back({ i % _width, i / _width });
		}
	}

	return v;
}

LevelSystem::Tile LevelSystem::getTileAt(Vector2f v) {
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0) {
		throw string("Tile out of range ");
	}
	return getTile(Vector2ul((v - _offset) / (_tileSize)));
}

bool LevelSystem::isOnGrid(sf::Vector2f v) {
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0) {
		return false;
	}
	auto p = Vector2ul((v - _offset) / (_tileSize));
	if (p.x > _width || p.y > _height) {
		return false;
	}
	return true;
}

void LevelSystem::setOffset(const Vector2f& offset) {
	LevelSystem::_offset = offset;
	buildSprites();
}

void LevelSystem::unload() {
	cout << "LevelSystem unloading\n";
	_sprites.clear();
	_tiles.reset();
	_width = 0;
	_height = 0;
	_offset = { 0, 0 };
}

const Vector2f& LevelSystem::getOffset() { return _offset; }

float LevelSystem::getTileSize() { return _tileSize; }