#include <iostream>

#include "babyxml.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " STRING" << std::endl;
  }
  else
  {
    // BabyXML xml("<strong size='10'>Hello &lt; World&gt; <b>&quot;blabla&quot;</b> Blablub</strong>");
    babyxml::BabyXML xml(argv[1]);

    for(auto const& node : xml.get_root())
    {
      if (node.type == babyxml::NodeType::START_TAG) {
        std::cout << "STARTTAG: ";
      } else if (node.type == babyxml::NodeType::END_TAG) {
        std::cout << "ENDTAG: ";
      } else if (node.type == babyxml::NodeType::TEXT) {
        std::cout << "TEXT: ";
      }

      std::cout << "'" << node.content << "'";

      for(auto const& attrib : node.attributes)
      {
        std::cout << " " << attrib.name << "='" << attrib.value << "'";
      }

      std::cout << std::endl;
    }
  }
}

/* EOF */
