#ifndef HEADER_READER_HPP
#define HEADER_READER_HPP

#include <string>
#include <vector>

#include "babyxml.hpp"

class BabyXML;

namespace babyxml {

class Reader
{
public:
  Reader(BabyXML& xml_, const std::string& text_);

private:
  void skip_space();
  void read_char(char expect);
  void read_element();
  std::string read_string();
  char read_entity();
  std::vector<Attribute> read_attributes();
  std::string read_identifer();
  bool eof() const;
  char look_ahead();
  void incr_cursor();

private:
  BabyXML& m_xml;
  std::string m_text;
  int m_cursor;
  int m_line_no;
  int m_column_no;

private:
  Reader(const Reader&) = delete;
  Reader& operator= (const Reader&) = delete;
};

} // namespace babyxml

#endif

/* EOF */
