#include "reader.hpp"

#include <sstream>

namespace babyxml {

Reader::Reader(BabyXML& xml_, const std::string& text_) :
  m_xml(xml_),
  m_text(text_),
  m_cursor(0),
  m_line_no(0),
  m_column_no(0)
{
  std::string content;

  while(!eof())
  {
    char c = look_ahead();
    switch(c)
    {
      case '<':
        if (!content.empty())
        {
          m_xml.add_node(Node{NodeType::TEXT, content});
          content = "";
        }
        read_element();
        break;

      case '&':
        content += read_entity();
        break;

      default:
        content += c;
        incr_cursor();
        break;
    }
  }

  if (!content.empty())
    m_xml.add_node(Node{NodeType::TEXT, content});
}

void
Reader::skip_space()
{
  while(true)
  {
    char c = look_ahead();
    if (c != ' ' && c != '\t') {
      break;
    } else {
      incr_cursor();
    }
  }
}

void
Reader::read_char(char expect)
{
  char c = look_ahead();
  if (c != expect)
  {
    std::ostringstream str;
    str << "Syntax Error:" << m_line_no << ":" << m_column_no
        << ": Syntax error: read_char(): expected '" << expect << "' got '" << c << "'";
    throw std::runtime_error(str.str());
  }
  else
  {
    incr_cursor();
  }
}

void
Reader::read_element()
{
  Node node;

  read_char('<');
  if (look_ahead() == '/')
  {
    node.type = NodeType::END_TAG;
    incr_cursor();
    node.content = read_identifer();
  }
  else
  {
    node.type = NodeType::START_TAG;
    node.content    = read_identifer();
    node.attributes = read_attributes();
  }

  skip_space();
  read_char('>');

  m_xml.add_node(node);
}

/** Read a string of the form: '"your string"' */
std::string
Reader::read_string()
{
  char start = look_ahead();
  if (start != '\'' && start != '"')
  {
    std::ostringstream str;
    str << "Syntax Error:" << m_line_no << ":" << m_column_no
        << ": Syntax error: read_string(): expected ' or \" got '" << start << "'";
    throw std::runtime_error(str.str());
  }
  incr_cursor();

  std::string content;
  while(true)
  {
    char c = look_ahead();
    if (c == '"' || c == '\'')
    {
      if (c != start)
      {
        std::ostringstream str;
        str << "Syntax Error:" << m_line_no << ":" << m_column_no
            << ": Syntax error: read_string(): quote mismatch";
        throw std::runtime_error(str.str());
      }
      incr_cursor();
      break;
    }
    else if (c == '&')
    {
      content += read_entity();
    }
    else
    {
      incr_cursor();
      content += c;
    }
  }
  return content;
}

char
Reader::read_entity()
{
  read_char('&');
  std::string identifer = read_identifer();
  read_char(';');

  if (identifer == "quot")
    return '"';
  else if (identifer == "gt")
    return '>';
  else if (identifer == "lt")
    return '<';
  else
  {
    std::ostringstream str;
    str << "Syntax Error:" << m_line_no << ":" << m_column_no << ": Unknown entity: '&" + identifer + ";'";
    throw std::runtime_error(str.str());
  }
}

std::vector<Attribute>
Reader::read_attributes()
{
  std::vector<Attribute> attributes;
  while(true)
  {
    skip_space();

    char c = look_ahead();
    if (c == '>' || c == '&' || c == '<' || c == ';')
    {
      break;
    }

    attributes.push_back(Attribute{});

    attributes.back().name = read_identifer();
    read_char('=');
    attributes.back().value = read_string();
  }
  return attributes;
}

std::string
Reader::read_identifer()
{
  std::string identifer;
  while(true)
  {
    char c = look_ahead();
    if (c == '<' || c == '>' || c == '&' || c == ';' || c == ' ' || c == '\t' || c == '=') {
      break;
    } else {
      identifer += c;
      incr_cursor();
    }
  }

  if (identifer.empty())
  {
    std::ostringstream str;
    str << "Syntax Error:" << m_line_no << ":" << m_column_no << ": Identifer is empty";
    throw std::runtime_error(str.str());
  }

  return identifer;
}

bool
Reader::eof() const
{
  return m_cursor >= static_cast<int>(m_text.size());
}

char
Reader::look_ahead()
{
  if (m_cursor >= static_cast<int>(m_text.size()))
  {
    std::ostringstream str;
    str << "Syntax Error:" << m_line_no << ":" << m_column_no << ": Premature end of text";
    throw std::runtime_error(str.str());
  }

  return m_text[m_cursor];
}

void
Reader::incr_cursor()
{
  m_cursor += 1;
  if (m_text[m_cursor] == '\n')
  {
    m_line_no += 1;
    m_column_no = 0;
  }
  else
  {
    m_column_no += 1;
  }
}

} // namespace babyxml

/* EOF */
