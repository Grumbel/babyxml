#include <assert.h>
#include <iostream>

#include "babyxml.hpp"

int main(int argc, char** argv)
{
  if (argc == 1) {
    std::cout << "Usage: " << argv[0] << " STRING" << std::endl;
    return 0;
  }

  for(int i = 1; i < argc; ++i)
  {
    // "<strong size='10'>Hello &lt; World&gt; <b>&quot;blabla&quot;</b> Blablub</strong>"
    for(auto const& node : babyxml::parse(argv[i]))
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
