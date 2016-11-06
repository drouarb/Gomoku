//
// Created by celeri_y on 4/13/16.
//

#include "GraphicException.hpp"

const char *GUI::GraphicException::what() const throw()
{
  std::stringstream stringstream;

  stringstream << "Graphical Error: " << this->reason << ". " << this->description;
  return (stringstream.str().c_str());
}

GUI::GraphicException::GraphicException(std::string const &description,
					 std::string const &reason)
	: description(
	description), reason(reason)
{

}