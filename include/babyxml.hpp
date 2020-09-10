// babyxml - tiny parser for XML-like dialect
// Copyright (C) 2009-2020 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_BABYXML_BABYXML_HPP
#define HEADER_BABYXML_BABYXML_HPP

#include <span>
#include <string>
#include <string_view>
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

std::vector<Node> parse(std::string_view text);

} // namespace babyxml

#endif

/* EOF */
