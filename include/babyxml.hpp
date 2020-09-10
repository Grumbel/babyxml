/*
**  Windstille - A Sci-Fi Action-Adventure Game
**  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmail.com>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HEADER_WINDSTILLE_UTIL_BABY_XML_HPP
#define HEADER_WINDSTILLE_UTIL_BABY_XML_HPP

#include <span>
#include <string>
#include <vector>

namespace babyxml {

struct Attribute
{
  std::string name = {};
  std::string value = {};
};

enum class NodeType
{
  NONE,
  TEXT,
  START_TAG,
  END_TAG,
  ENTITY
};

struct Node
{
  NodeType type = NodeType::NONE;
  std::string content = {};
  std::vector<Attribute> attributes = {};
};

/** Parser for a flat XML-like tag soup, it doesn't support recursive
    structures */
class BabyXML
{
public:
  /** Parse the given \a text and construct the nodes from it */
  BabyXML(const std::string& text);
  ~BabyXML();

  void add_node(const Node& node);

  std::vector<Node> const& get_root() const { return m_nodes; }

private:
  std::vector<Node> m_nodes;

public:
  BabyXML(const BabyXML&) = delete;
  BabyXML& operator=(const BabyXML&) = delete;
};

} // namespace babyxml

#endif

/* EOF */
